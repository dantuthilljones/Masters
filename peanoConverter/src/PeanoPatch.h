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
#include <vector>

#include "boost/algorithm/string/predicate.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/trim.hpp"
#include "boost/lexical_cast.hpp"


class PeanoPatch {
public:
	PeanoPatch(std::vector<std::string> &text, int dimensions, std::vector<int> &patchSize, std::vector<PeanoVariable*> &variables) ;
	virtual ~PeanoPatch();
	int dimensions;
	std::vector<int> patchSize;
	double* offsets;
	double* sizes;
	std::unordered_map<std::string, PeanoPatchData*> patchData;
	bool hasMappings();
	PeanoVariable* getStructure();
};

#endif /* PEANOPATCH_H_ */
