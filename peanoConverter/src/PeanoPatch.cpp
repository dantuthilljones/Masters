/*
 * PeanoPatch.cpp
 *
 *  Created on: 16 Oct 2017
 *      Author: dan
 */

#include "PeanoPatch.h"
#include "PeanoVariable.h"
#include "PeanoPatchData.h"

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string/predicate.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/trim.hpp"

PeanoPatch::PeanoPatch(std::vector<std::string> &text, int dimensions, std::vector<int> &patchSize, std::vector<PeanoVariable*> &variables) {
	//std::cout << "Starting PeanoPatch\n";
	this->dimensions = dimensions;
	this->patchSize = patchSize;

	//calculate the number of cells in the patch
	int cells = 1;
	for(int i = 0; i < dimensions; i++) {
		cells *= patchSize[i];
	}

	//initialize the data objects for each variable
	for(uint i = 0; i < variables.size(); i++) {
		PeanoPatchData* data = new PeanoPatchData(variables[i]);
		patchData[data->structure->name] = data;
	}

	//std::cout << "text size: " << text.size() << "\n";

	for(uint i = 0; i < text.size(); i++) {
		//std::cout << "Patch line " << i << "\n";
		std::string line = text[i];
		boost::trim(line);

		if(boost::starts_with(line, "offset")) {

			//split the line which will be in the form "offset 0 0"
			std::vector<std::string> split;
			boost::split(split, line, boost::is_any_of(" "));

			//create an array to hold the number  of offsets
			offsets = new double[dimensions];
			for(int j = 0; j < dimensions; j++) {
				offsets[j] = std::stod(split[j+1]);//the 0th element of split is "offset" so skip it
			}
		} else if(boost::starts_with(line, "size")) {
			//split the line which will be in the form "size 0 0"
			std::vector<std::string> split;
			boost::split(split, line, boost::is_any_of(" "));

			//create an array to hold the number  of offsets
			sizes = new double[dimensions];
			for(int j = 0; j < dimensions; j++) {
				sizes[j] = std::stod(split[j+1]);//the 0th element of split is "offset" so skip it
			}
		} else if(boost::starts_with(line,"begin cell-values") || boost::starts_with(line,"begin vertex-values")) {

			//get the variable we are looking for
			std::vector<std::string> split;
			boost::split(split, line, boost::is_any_of(" "));
			std::string variableName = split[2];
			variableName = variableName.substr(1, variableName.size() -2);

			//get the data object for this variable
			PeanoPatchData* data = patchData[variableName];

			//get the line of text containing the values and trim whitespace
			std::string vals = text[i+1];
			boost::trim(vals);

			//split the line of text to get a vector of string values
			std::vector<std::string> splitValues;
			boost::split(splitValues, vals, boost::is_any_of(" "));

			//convert the strings to doubles and add to the array
			for(int j = 0; j < data->structure->totalValues; j++) {
				data->values[j] = std::stod(splitValues[j]);
			}
		}
	}
}

PeanoVariable* PeanoPatch::getStructure() {
	for (auto it : this->patchData) {
		return it.second->structure;
	}
	return nullptr;
}

bool PeanoPatch::hasMappings(){
	for (auto it : this->patchData) {
		return it.second->structure->mappings != -1;
	}
	return false;
}


PeanoPatch::~PeanoPatch() {
	delete [] offsets;
	delete [] sizes;
	for (auto it : patchData) {
		delete it.second;
	}
}

