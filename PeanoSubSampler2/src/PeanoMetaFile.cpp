/*
 * PeanoMetaReader.cpp
 *
 *  Created on: 26 Nov 2017
 *      Author: dan
 */

#include "PeanoMetaFile.h"

#include "boost/algorithm/string/predicate.hpp"
#include "boost/algorithm/string/erase.hpp"
#include "boost/algorithm/string/trim.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

PeanoMetaFile::PeanoMetaFile(std::string fileName) {
	this->fileName = fileName;

	directory = getDirectory(fileName);

	// read the file in to a vector of strings
	std::ifstream ifs(fileName);
	std::vector<std::string> lines;
	for (std::string line; std::getline(ifs, line); /**/ )
		lines.push_back(line);
	ifs.close();

	bool metadataFile = false;

	for(uint i = 0; i < lines.size(); i++) {
		std::string line = lines[i];

		if(boost::starts_with(line, "#")) {
			continue;
		} else if(boost::starts_with(line, "begin dataset")) {
			metadataFile = true;
			std::vector<std::string> dataSetLines;
			for(i++; i < lines.size(); i++) {
				std::string line2 = lines[i];
				boost::trim(line2);
				if(boost::starts_with(line2, "end dataset")) {
					break;
				} else {
					dataSetLines.push_back(line2);
				}
			}
			PeanoDataSet* dataSet = new PeanoDataSet(dataSetLines, directory);
			dataSets.push_back(dataSet);
		}
	}

	//if the input was not a dataset then it was a peano file
	if(!metadataFile) {
		std::cout << "Initial file is a patch file and not a metadata file...\n";
		std::vector<std::string> dataLine;
		dataLine.push_back(this->fileName);
		dataSets.push_back(new PeanoDataSet(dataLine, directory));
	} else {
		std::cout << "Initial file is a metadata file...:\n";
	}
}

void PeanoMetaFile::save() {
	std::cout << "\nSaving metadeta file " << fileName << "\n";
	std::ofstream file;
	file.open(fileName.c_str(), std::ofstream::out | std::ofstream::trunc);


	file << "#\n";
	file << "# Peano metadata output file\n";
	file << "# Version 0.2\n";
	file << "#\n";
	file << "format ASCII\n\n";

	for(PeanoDataSet* dataset: this->dataSets) {
		std::vector<std::string> lines = dataset->toString();
		for(std::string line: lines)
			file << line << "\n";
		file << "\n";
	}

	file << "end patch\n";
	file.close();
}

std::vector<PeanoReader*> PeanoMetaFile::createReadersFull(int index) {
	return getDataSet(index)->createReadersFull();
}

std::vector<PeanoDataSet*> PeanoMetaFile::getDataSets() {
	return this->dataSets;
}

PeanoDataSet* PeanoMetaFile::getDataSet(int index) {
	return this->dataSets[index];
}

int PeanoMetaFile::numberOfDataSets() {
	return dataSets.size();
}

std::string PeanoMetaFile::getDirectory(const std::string &fileName) {
	return fileName.substr(0, fileName.find_last_of("/\\") +1);
}

PeanoMetaFile::~PeanoMetaFile() {
	for(PeanoDataSet* dataSet: dataSets) delete dataSet;
}

