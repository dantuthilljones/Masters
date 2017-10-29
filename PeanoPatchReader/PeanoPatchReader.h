/*
 * PeanoReader.h
 *
 *  Created on: 16 Oct 2017
 *      Author: dan
 */

#ifndef PEANOPATCHREADER_H_
#define PEANOPATCHREADER_H_

#include <string>

class PeanoPatchReader {
public:
	PeanoPatchReader(std::string file);
	virtual ~PeanoPatchReader();
};

#endif /* PEANOPATCHREADER_H_ */
