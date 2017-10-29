/*
 * PeanoVariableData.cpp
 *
 *  Created on: 26 Oct 2017
 *      Author: dan
 */

#include "PeanoPatchData.h"

PeanoPatchData::PeanoPatchData(PeanoVariable variable, int cells) {
	variableName = variable.variableName;
	unknowns = variable.unknowns;
	totalValues = cells*unknowns;
	values = (double*) malloc(sizeof(double) * totalValues);
}

PeanoPatchData::~PeanoPatchData() {
	delete values;
}
