/*
 * PeanoVariableData.h
 *
 *  Created on: 26 Oct 2017
 *      Author: dan
 */

#ifndef PEANOPATCHDATA_H_
#define PEANOPATCHDATA_H_

#include "PeanoVariable.h"

class PeanoPatchData {
public:
	PeanoPatchData(PeanoVariable variable, int cells);
	virtual ~PeanoPatchData();
	double* values;
	std::string variableName;
	int unknowns;
	int totalValues;
};

#endif /* PEANOPATCHDATA_H_ */
