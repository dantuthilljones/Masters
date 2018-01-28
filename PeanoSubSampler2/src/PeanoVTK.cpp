/*
 * PeanoVTK.cpp
 *
 *  Created on: 17 Oct 2017
 *      Author: dan
 */

#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "PeanoReader.h"
#include "PeanoConverter.h"
#include "PeanoMetaReader.h"

#include "vtkUnstructuredGrid.h"
#include "vtkSmartPointer.h"
#include "vtkXMLUnstructuredGridWriter.h"

int main(int argc, char* argv[]) {
	if(argc != 6) {
		std::cout << "Five parameters expected, instead we had " << (argc-1) << ":\n";
		for(int i = 0; i < argc; i++) {
			std::cout << "\t" << argv[i] << "\n";
		}
		std::cout << "Program should be ran like so:\n";
		std::cout << "\t./peanoSubSampler INPUT_FILE OUTPUT_FILE X_SIZE Y_SIZE Z_SIZE\n";
		return -1;
	}
	std::string input = argv[1];
	std::string output = argv[2];

	int xSize = std::stoi(argv[3]);
	int ySize = std::stoi(argv[4]);
	int zSize = std::stoi(argv[5]);


	std::cout << "Reading initial file " << input << "...\n";
	PeanoMetaReader* metaReader = new PeanoMetaReader(input);
	std::vector<std::vector<std::string>> datasets = metaReader->getDataSets();

	//#pragma omp parallel for
	for(uint i = 0; i < datasets.size(); i++) {
	//for(uint i = 0; i < 1; i++) {
		std::vector<std::string> dataset = datasets[i];
		std::vector<PeanoReader*> readers;
		for(uint j = 0; j < dataset.size(); j++) {
			std::string file = dataset[j];
			std::cout << "Reading data from " << file << "...\n";
			PeanoReader* reader = new PeanoReader(file);
			readers.push_back(reader);
		}

		PeanoPatch* grid = PeanoConverter::subSample(&readers, xSize, ySize, zSize);

		grid->saveToFile(output);

		delete grid;
		for(PeanoReader* reader: readers) {
			delete reader;
		}
	}

	std::cout << "Done!\n";
}
