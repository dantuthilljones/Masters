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

#include "vtkImplicitFunction.h"


class PeanoPatch {
public:
	PeanoPatch(std::vector<std::string> &text, int dimensions, int* patchSize, std::vector<PeanoVariable*> &variables);
	PeanoPatch(std::vector<std::string> &text, int dimensions,
		int* patchSize, std::vector<PeanoVariable*> &variables,
	 	vtkImplicitFunction*) ;
	PeanoPatch();
	virtual ~PeanoPatch();
	int dimensions;//number of dimensions, probably 3

	/*
	 * number of points in each dimension
	 */
	int* resolution;

	/*
	 * offset of the patch in each dimension
	 */
	double* offsets;

	/*
	 * size of the patch in each dimension
	 */
	double* sizes;

	std::unordered_map<std::string, PeanoPatchData*> patchData;
	bool hasMappings();
	PeanoVariable* getStructure();
	double* getPositionMap(int x, int y, int z);
	double* getPositionVertex(int x, int y, int z);
	double* getPositionCellCenter(int x, int y, int z);
	int getIndexCellData(int x, int y, int z);
	int getIndexVertexData(int x, int y, int z);
	bool saveToFile(std::string filename);

	/*
	 * used to flag that this patch is inside or outside the selected area
	 */
	bool loaded = true;
};

#endif /* PEANOPATCH_H_ */
