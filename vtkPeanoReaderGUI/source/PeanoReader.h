/*
 * PeanoReader.h
 *
 *  Created on: 16 Oct 2017
 *      Author: dan
 */

#ifndef PEANOREADER_H_
#define PEANOREADER_H_

#include <string>
#include <vector>

#include "PeanoVariable.h"
#include "PeanoPatch.h"

class PeanoReader {
public:
	PeanoReader(const std::string &file);
	virtual ~PeanoReader();
	//declare variables
	int dimensions = -1;
	int cells = -1;
	int vertices = -1;
	int* patchSize;
	std::vector<PeanoVariable*> variables;
	std::vector<PeanoPatch*> patches;
};

#endif /* PEANOREADER_H_ */
