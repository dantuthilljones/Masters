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
#include "PeanoMetaFile.h"

#include "vtkSmartPointer.h"
#include "vtkXMLUnstructuredGridWriter.h"

int main(int argc, char* argv[]) {
	if(argc != 5) {
		std::cout << "Four parameters expected, instead we had " << (argc-1) << ":\n";
		for(int i = 1; i < argc; i++) {
			std::cout << "\t" << argv[i] << "\n";
		}
		std::cout << "Program should be ran like so:\n";
		std::cout << "\t./peanoSubSampler INPUT_FILE X_SIZE Y_SIZE Z_SIZE\n";
		return -1;
	}
	std::string input = argv[1];

	int xSize = std::stoi(argv[2]);
	int ySize = std::stoi(argv[3]);
	int zSize = std::stoi(argv[4]);


	std::cout << "Reading initial file " << input << "...\n";
	PeanoMetaFile metaFile = PeanoMetaFile(input);

	#pragma omp parallel for
	for(int i = 0; i < metaFile.numberOfDataSets(); i++) {
	//for(uint i = 0; i < 1; i++) {
		PeanoDataSet* dataset = metaFile.getDataSet(i);
		PeanoPatch* sample = dataset->createSubSample(xSize, ySize, zSize, true);
		delete sample;
	}

	//Write the metadatafile
	metaFile.save();

	std::cout << "Done!\n";
}
