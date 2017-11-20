/*
 * PeanoReader.cpp
 *
 *  Created on: 16 Oct 2017
 *      Author: dan
 */

#include "PeanoPatchReader.h"
#include "PeanoPatch.h"
#include "PeanoVariable.h"

#include "boost/algorithm/string/predicate.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

PeanoPatchReader::PeanoPatchReader(std::string location) {
	std::cout << "Created PeanoReader for file " << location << std::endl;

	// read the file in to a vector of strings
	std::ifstream ifs(location);
	std::vector<std::string> lines;
	for (std::string line; std::getline(ifs, line); /**/ )
		lines.push_back(line);

	for(int i = 0; i < lines.size(); i++) {
		std::string line = lines[i];

		if(boost::starts_with(line, "#")) {
			continue;
		} else if(boost::starts_with(line, "begin cell-values")) {
			std::vector<std::string> split;
			boost::split(split, line, boost::is_any_of(" "));

			std::string variableName = split[2];
			variableName = variableName.substr(1, variableName.size() -2);

			if(variableName.compare("time") != 0) {//ignore time variable
				std::string nextLine = lines[i+1];
				boost::trim(nextLine);
				std::vector<std::string> splitUnknowns;
				boost::split(splitUnknowns, nextLine, boost::is_any_of(" "));

				int unknowns = std::stoi(splitUnknowns[1]);
				PeanoVariable* variable = new PeanoVariable(variableName, unknowns);

				variables.push_back(*variable);
			}

		} else if(boost::starts_with(line, "dimensions")) {
			std::vector<std::string> split;
			boost::split(split, line, boost::is_any_of(" "));
			dimensions = std::stoi(split[1]);
		} else if(boost::starts_with(line, "patch-size")) {
			std::vector<std::string> split;
			boost::split(split, line, boost::is_any_of(" "));
			for(int j = 1; j <= dimensions; j++) {
				patchSize.push_back(std::stoi(split[j]));
			}
		} else if(boost::starts_with(line, "begin patch")) {
			//build a list of lines for this patch
			std::vector<std::string>* patchLines = new std::vector<std::string>;
			for(i++; i < lines.size(); i++) {
				std::string patchLine = lines[i];
				if(boost::starts_with(patchLine, "end patch")) {
					patches.push_back(new PeanoPatch(*patchLines, dimensions, &patchSize[0], variables));
					break;
				} else {
					patchLines->push_back(patchLine);
				}
			}
		}
	}
	int a = 0;
}

PeanoPatchReader::~PeanoPatchReader() {

}
