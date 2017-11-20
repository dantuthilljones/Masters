/*
 * PeanoVTK.cpp
 *
 *  Created on: 17 Oct 2017
 *      Author: dan
 */

#include <boost/version.hpp>
#include <iostream>

#include "PeanoPatchReader.h"
#include "PeanoConverter.h"

#include "vtkSmartPointer.h"
#include "vtkImageData.h"
#include "vtkXMLImageDataWriter.h"
#include "vtkXMLUnstructuredGridWriter.h"

int main() {
	std::cout << "My first boost program with version: " << BOOST_LIB_VERSION << std::endl;

	PeanoPatchReader* reader = new PeanoPatchReader("/home/dan/Documents/Masters/ExampleFiles/FromPhysics/peano-ascii-conserved-0.peano-patch-file");
	vtkSmartPointer<vtkUnstructuredGrid> grid = PeanoConverter::combineImageData(&reader->patches);

	vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
	writer->SetFileName("outputGridPhysics.vtu");
	writer->AddInputDataObject(0, grid);
	writer->Write();

	std::cout << "Finished!";

}
