/*
 * PeanoPatch.cpp
 *
 *  Created on: 16 Oct 2017
 *      Author: dan
 */

#include "PeanoPatch.h"
#include "PeanoConverter.h"
#include "PeanoPatchData.h"

#include <string>
#include <unordered_map>
#include <vector>

#include "vtkImageData.h"
#include "vtkSmartPointer.h"
#include "vtkDoubleArray.h"
#include "vtkCellData.h"
#include "vtkAppendFilter.h"
#include "vtkUnstructuredGrid.h"


vtkSmartPointer<vtkImageData> PeanoConverter::toImageData(PeanoPatch* patch) {
	vtkImageData* imageData = vtkImageData::New();


	//get the data from the patch in to arrays
	double spacing[3] = {1, 1, 1};
	double offSets[3] = {0, 0, 0};
	int dimensions[3] = {1, 1, 1};

	for(int i = 0; i < patch->dimensions; i++) {
		dimensions[i] = patch->patchSize[i] +1;
		offSets[i] = patch->offsets[i];
		spacing[i] = patch->sizes[i]/patch->patchSize[i];
	}

	imageData->SetDimensions(dimensions);
	imageData->SetOrigin(offSets);
	imageData->SetSpacing(spacing);


	//allocate any variables
	std::vector<vtkDoubleArray*> variables;
	for(auto kv : patch->patchData) {
		PeanoPatchData* data = kv.second;
		vtkDoubleArray* variableArray = vtkDoubleArray::New();
		variableArray->SetNumberOfComponents(data->unknowns);
		variableArray->SetName(data->variableName.c_str());
		//std:: << "\n " << data->variableName << ": ";
		for(int i = 0; i < kv.second->totalValues; i += data->unknowns) {
			variableArray->InsertNextTuple(&data->values[i]);
		}

		imageData->GetCellData()->AddArray(variableArray);
	}
	return imageData;
}

vtkSmartPointer<vtkUnstructuredGrid> PeanoConverter::combineImageData(std::vector<PeanoPatch*>* patches){
	vtkSmartPointer<vtkAppendFilter> appendFilter = vtkSmartPointer<vtkAppendFilter>::New();
	for(uint i = 0; i < patches->size(); i++) {
		appendFilter->AddInputData(toImageData((*patches)[i]));
	}

	appendFilter->Update();
	vtkSmartPointer<vtkUnstructuredGrid> combined = appendFilter->GetOutput();

	return combined;
}

//PeanoConverter::toStructuredPoints(*PeanoPatch patch) {
// vtkStructredPoints* grid = new vtkStructredPoints::New();
//
// // vtk only uses 3 dimensional grids
// int[3] dimensions = {0, 0, 0};
// for(int i = 0; i < patch->dimensions; i++) {
//   dimensions[i] = patch->patchSize[i];
// }
// grid->setDimensions(dimensions);
//
// //allocate the points in the grid
// vtkPoints *nodes = vtkPoints::New();
// nodes->Allocate(patch->cells);
//
// //allocate any variables
// std::vector<vtkDoubleArray*> variables;
// for(auto kv : patch->patchData) {
//   PeanoPatchData* data = kv.second;
//   vtkDoubleArray* variableArray = vtkDoubleArray::New();
//   variableArray->SetNumberOfComponents(data->unknowns);
//   variableArray->SetName(data->totalValues);
//   std::cout << "\n " << data.variableName << ": ";
//   for(int i = 0; i < kv.second->totalValues; i += data->unknowns) {
//     variableArray->>InsertNextTuple(&data->values[i]);
//   }
// }
//}
