/*
 * PeanoVariable.h
 *
 *  Created on: 26 Oct 2017
 *      Author: dan
 */

#ifndef PEANOVARIABLE_H_
#define PEANOVARIABLE_H_

#include <string>

class PeanoVariable {
public:
	PeanoVariable(std::string variableName, int unknowns);
	virtual ~PeanoVariable();
	std::string variableName;
	int unknowns;
};

#endif /* PEANOVARIABLE_H_ */
