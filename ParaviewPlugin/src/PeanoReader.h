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

#include "vtkImplicitFunction.h"

class PeanoReader {
public:
	PeanoReader(const std::string &file);
	PeanoReader(const std::string &file, vtkImplicitFunction*);
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
