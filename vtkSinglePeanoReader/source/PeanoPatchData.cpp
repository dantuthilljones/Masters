/*
 * PeanoVariableData.cpp
 *
 *  Created on: 26 Oct 2017
 *      Author: dan
 */

#include "PeanoPatchData.h"
#include "PeanoVariable.h"

PeanoPatchData::PeanoPatchData(PeanoVariable* variable) {
	structure = variable;
	values = new double[structure->totalValues];

}

PeanoPatchData::~PeanoPatchData() {
	delete [] values;
}
