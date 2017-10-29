/*
 * PeanoVTK.cpp
 *
 *  Created on: 17 Oct 2017
 *      Author: dan
 */

#include <boost/version.hpp>
#include <iostream>

#include "PeanoPatchReader.h"

using namespace std;

int main() {
	cout << "My first boost program with version: " << BOOST_LIB_VERSION << endl;

	PeanoPatchReader* reader = new PeanoPatchReader("/home/dan/Documents/exahype/exahype/Demonstrators/EulerFV/variables-0.peano-patch-file");
	delete reader;

}
