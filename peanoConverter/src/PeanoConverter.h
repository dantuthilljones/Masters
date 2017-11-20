#ifndef PEANOCONVERTER_H_
#define PEANOCONVERTER_H_

#include "PeanoPatch.h"
#include "vtkImageData.h"
#include "vtkSmartPointer.h"
#include "vtkUnstructuredGrid.h"

class PeanoConverter {
	public:
	static vtkSmartPointer<vtkImageData> toImageData(PeanoPatch* patch);
	static vtkSmartPointer<vtkUnstructuredGrid> combineImageData(std::vector<PeanoPatch*>* patches);
};

#endif /* PEANOCONVERTER_H_ */
