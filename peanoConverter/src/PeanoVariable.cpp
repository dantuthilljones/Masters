/*
 * PeanoVariable.cpp
 *
 *  Created on: 26 Oct 2017
 *      Author: dan
 */

#include "PeanoVariable.h"

PeanoVariable::PeanoVariable(std::string variableName, int unknowns) {
	this->variableName = variableName;
	this->unknowns = unknowns;
}

PeanoVariable::~PeanoVariable() {
	// TODO Auto-generated destructor stub
}

