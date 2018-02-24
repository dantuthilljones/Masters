/*
 * PeanoDataSet.h
 *
 *  Created on: 29 Jan 2018
 *      Author: dan
 */

#ifndef PEANODATASET_H_
#define PEANODATASET_H_

#include "PeanoPatch.h"
#include "PeanoReader.h"

#include <string>

class PeanoDataSet {
public:
	PeanoDataSet(std::vector<std::string> &lines, std::string directory);
	std::vector<PeanoReader*>* createReadersFull();
	std::vector<PeanoReader*>* createReadersResolution(int res);
	std::string getDirectory();
	std::vector<std::string>* getFullData();
	std::vector<std::vector<int>>* getResolutions();
	std::string getResolution(int index);
	std::vector<std::string> toString();
	std::string getSimpleName();
	PeanoPatch* createSubSample(int x, int y, int z, bool saveToFile);
	virtual ~PeanoDataSet();
private:
	std::vector<std::string>* fullData;
	std::vector<std::string>* resolutionData;
	std::vector<std::vector<int>>* resolutions;
	std::string directory;
};

#endif /* PEANODATASET_H_ */
