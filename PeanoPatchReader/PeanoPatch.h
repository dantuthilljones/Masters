/*
 * PeanoPatch.h
 *
 *  Created on: 17 Oct 2017
 *      Author: dan
 */

#ifndef PEANOPATCH_H_
#define PEANOPATCH_H_

#include "PeanoPatchData.h"
#include "PeanoVariable.h"

#include <string>
#include <iostream>
#include <unordered_map>

#include "boost/algorithm/string/predicate.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/trim.hpp"
#include "boost/lexical_cast.hpp"


class PeanoPatch {
public:
	PeanoPatch(std::vector<std::string>& text, int dimensions, int* patchSize, std::vector<PeanoVariable>& variables);
	virtual ~PeanoPatch();
private:
	int dimensions;
	int* patchSize;
	double* offsets;
	double* sizes;
	std::unordered_map<std::string, PeanoPatchData*> patchData;
};

#endif /* PEANOPATCH_H_ */
