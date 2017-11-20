/*
 * PeanoReader.h
 *
 *  Created on: 16 Oct 2017
 *      Author: dan
 */

#ifndef PEANOPATCHREADER_H_
#define PEANOPATCHREADER_H_

#include <string>
#include <vector>

#include "PeanoVariable.h"
#include "PeanoPatch.h"

class PeanoPatchReader {
public:
	PeanoPatchReader(std::string file);
	virtual ~PeanoPatchReader();

	//declare variables
	int dimensions = -1;
	std::vector<PeanoVariable> variables;
	std::vector<int> patchSize;
	std::vector<PeanoPatch*> patches;
};

#endif /* PEANOPATCHREADER_H_ */
