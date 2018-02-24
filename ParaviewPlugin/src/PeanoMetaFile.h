/*
 * PeanoMetaReader.h
 *
 *  Created on: 26 Nov 2017
 *      Author: dan
 */

#ifndef PEANOMETAFILE_H_
#define PEANOMETAFILE_H_

#include <string>
#include <vector>

#include "PeanoDataSet.h"
#include "PeanoReader.h"

class PeanoMetaFile {
public:
	PeanoMetaFile();
	PeanoMetaFile(std::string file);
	std::vector<PeanoDataSet*>* getDataSets();
	std::vector<PeanoReader*>* createReadersFull(int index);
	std::vector<PeanoReader*>* createReadersResolution(int index, int resolution);
	PeanoDataSet* getDataSet(int index);
	int numberOfDataSets();
	void save();
	virtual ~PeanoMetaFile();
private:
	static std::string getDirectory(const std::string &fileName);
	std::string fileName;
	std::vector<PeanoDataSet*>* dataSets;
	std::string directory;
};

#endif /* PEANOMETAFILE_H_ */
