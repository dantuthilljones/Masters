#ifndef PEANOCONVERTER_H_
#define PEANOCONVERTER_H_

#include "PeanoPatch.h"
#include "PeanoReader.h"

#include "vtkImageData.h"
#include "vtkSmartPointer.h"
#include "vtkUnstructuredGrid.h"

class PeanoConverter {
	public:
	static vtkSmartPointer<vtkImageData> toImageData(PeanoPatch* patch);
	static vtkSmartPointer<vtkUnstructuredGrid> combineImageData(std::vector<PeanoPatch*>* patches);
	static vtkSmartPointer<vtkUnstructuredGrid> combineImageData(std::vector<PeanoReader*>* readers);
};

#endif /* PEANOCONVERTER_H_ */
