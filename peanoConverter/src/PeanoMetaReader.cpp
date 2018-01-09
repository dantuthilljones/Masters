/*
 * PeanoMetaReader.cpp
 *
 *  Created on: 26 Nov 2017
 *      Author: dan
 */

#include "PeanoMetaReader.h"

#include "boost/algorithm/string/predicate.hpp"
#include "boost/algorithm/string/erase.hpp"
#include "boost/algorithm/string/trim.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

PeanoMetaReader::PeanoMetaReader(std::string fileName) {
	this->fileName = fileName;
}

std::vector<std::vector<std::string>> PeanoMetaReader::getDataSets() {
	std::vector<std::vector<std::string>> dataSets;

	std::string directory = getDirectory(fileName);

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
			std::vector<std::string> dataSet;
			for(i++; i < lines.size(); i++) {
				std::string line2 = lines[i];
				boost::trim(line2);
				if(boost::starts_with(line2, "end dataset")) {
					break;
				} else {
					std::string fileName = line2.substr(9, line2.length()-10);
					std::string location = directory + fileName;
					dataSet.push_back(location);
				}
			}
			dataSets.push_back(dataSet);
		}
	}

	//if the input was not a dataset then it was a peano file
	if(!metadataFile) {
		std::cout << "Initial file is a patch file and not a metadata file...\n";
		std::vector<std::string> dataset;
		dataset.push_back(this->fileName);
		dataSets.push_back(dataset);
	} else {
		std::cout << "Initial file is a metadata file...:\n";
	}

	return dataSets;
}

std::string PeanoMetaReader::getDirectory(const std::string &fileName) {
	return fileName.substr(0, fileName.find_last_of("/\\") +1);
}

PeanoMetaReader::~PeanoMetaReader() {
	// TODO Auto-generated destructor stub
}

