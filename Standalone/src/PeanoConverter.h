#ifndef PEANOCONVERTER_H_
#define PEANOCONVERTER_H_

#include "PeanoPatch.h"
#include "PeanoReader.h"

#include "vtkImageData.h"
#include "vtkSmartPointer.h"
#include "vtkUnstructuredGrid.h"

class PeanoConverter {
	public:
	static vtkSmartPointer<vtkImageData> toImageData(PeanoPatch *patch);
	static vtkSmartPointer<vtkUnstructuredGrid> combineImageData(std::vector<PeanoPatch*>* patches);
	static vtkSmartPointer<vtkUnstructuredGrid> combineImageData(std::vector<PeanoReader*>* readers);
	static vtkSmartPointer<vtkUnstructuredGrid> toUnstructuredGrid(PeanoPatch* patch);
	static int xyzToIndex(int x, int y, int z, int dimensions[3]);
	static PeanoPatch* subSample(std::vector<PeanoReader*> &readers, int x, int y, int z);
	static std::vector<int> getOverlappingIndexes(PeanoPatch &patch, vtkSmartPointer<vtkImageData> image);
};

#endif /* PEANOCONVERTER_H_ */
