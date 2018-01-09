/*
 * PeanoMetaReader.h
 *
 *  Created on: 26 Nov 2017
 *      Author: dan
 */

#ifndef PEANOMETAREADER_H_
#define PEANOMETAREADER_H_

#include <string>
#include <vector>

class PeanoMetaReader {
public:
	PeanoMetaReader(std::string file);
	std::vector<std::vector<std::string>> getDataSets();
	virtual ~PeanoMetaReader();
private:
	std::string fileName;
	static std::string getDirectory(const std::string &fileName);
};

#endif /* PEANOMETAREADER_H_ */
