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

#include "boost/algorithm/string/predicate.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/trim.hpp"

PeanoPatch::PeanoPatch(std::vector<std::string>& text, int dimensions, int* patchSize, std::vector<PeanoVariable>& variables) {
	std::cout << "Starting PeanoPatch\n";
	this->dimensions = dimensions;
	this->patchSize = patchSize;
	offsets = nullptr;
	sizes = nullptr;

	//calculate the number of cells in the patch
	int cells = 1;
	for(int i = 0; i < dimensions; i++) {
		cells *= patchSize[i];
	}

	//initialize the data objects for each variable
	for(int i = 0; i < variables.size(); i++) {
		PeanoPatchData* data = new PeanoPatchData(variables[i], cells);
		patchData[data->variableName] = data;
	}



	std::cout << "text size: " << text.size() << "\n";

	for(uint i = 0; i < text.size(); i++) {
		//std::cout << "Patch line " << i << "\n";
		std::string line = text[i];
		boost::trim(line);

		if(boost::starts_with(line, "offset")) {

			//split the line which will be in the form "offset 0 0"
			std::vector<std::string> split;
			boost::split(split, line, boost::is_any_of(" "));

			//create an array to hold the number  of offsets
			offsets = (double*) malloc(sizeof(double)*dimensions);
			for(int j = 0; j < dimensions; j++) {
				offsets[j] = std::stod(split[j+1]);//the 0th element of split is "offset" so skip it
			}
		} else if(boost::starts_with(line, "size")) {
			//split the line which will be in the form "size 0 0"
			std::vector<std::string> split;
			boost::split(split, line, boost::is_any_of(" "));

			//create an array to hold the number  of offsets
			sizes = (double*) malloc(sizeof(double)*dimensions);
			for(int j = 0; j < dimensions; j++) {
				sizes[j] = std::stod(split[j+1]);//the 0th element of split is "offset" so skip it
			}
		} else if(boost::starts_with(line,"begin cell-values")) {

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
			for(int j = 0; j < data->totalValues; j++) {
				data->values[j] = std::stod(splitValues[j]);
			}
		}
	}

	std::cout << "Read Patch:\n";
	std::cout << " Dimensions = " << dimensions << "\n";
	std::cout << " Offsets =";
	for(int i = 0; i < dimensions; i++) {
		std::cout << " " << offsets[i];
	}
	std::cout << "\n Sizes =";
	for(int i = 0; i < dimensions; i++) {
		std::cout << " " << sizes[i];
	}

	for(auto kv :patchData) {
		std::cout << "\n " << kv.second->variableName << ": ";
		for(int i = 0; i < kv.second->totalValues; i++) {
			std::cout << kv.second->values[i] << " ";
		}
	}

	std::cout << "\n\n";

}


PeanoPatch::~PeanoPatch() {
	delete offsets;
	delete sizes;
}

