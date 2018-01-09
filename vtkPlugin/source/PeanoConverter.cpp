/*
 * PeanoPatch.cpp
 *
 *  Created on: 16 Oct 2017
 *      Author: dan
 */

#include "PeanoPatch.h"
#include "PeanoConverter.h"
#include "PeanoPatchData.h"
#include "PeanoVariable.h"

#include <string>
#include <unordered_map>
#include <vector>

#include "vtkImageData.h"
#include "vtkSmartPointer.h"
#include "vtkDoubleArray.h"
#include "vtkCellData.h"
#include "vtkPointData.h"
#include "vtkAppendFilter.h"
#include "vtkUnstructuredGrid.h"


vtkSmartPointer<vtkImageData> PeanoConverter::toImageData(PeanoPatch* patch) {
	vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();


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
	std::vector<vtkSmartPointer<vtkDoubleArray>> variables;
	for(auto kv : patch->patchData) {
		PeanoPatchData* data = kv.second;
		vtkSmartPointer<vtkDoubleArray> variableArray = vtkSmartPointer<vtkDoubleArray>::New();
		variableArray->SetNumberOfComponents(data->structure->unknowns);
		variableArray->SetName(data->structure->name.c_str());
		//std:: << "\n " << data->variableName << ": ";
		for(int i = 0; i < data->structure->totalValues; i += data->structure->unknowns) {
			variableArray->InsertNextTuple(&data->values[i]);
		}

		if(data->structure->type == Cell_Values) {
			imageData->GetCellData()->AddArray(variableArray);
		} else if(data->structure->type == Vertex_Values) {
			imageData->GetPointData()->AddArray(variableArray);
		}
	}
	return imageData;
}

vtkSmartPointer<vtkUnstructuredGrid> PeanoConverter::combineImageData(std::vector<PeanoPatch*>* patches){
	vtkSmartPointer<vtkAppendFilter> appendFilter = vtkSmartPointer<vtkAppendFilter>::New();
	for(uint i = 0; i < patches->size(); i++) {
		appendFilter->AddInputData(toImageData(patches->at(i)));
	}

	appendFilter->Update();
	vtkSmartPointer<vtkUnstructuredGrid> combined = vtkSmartPointer<vtkUnstructuredGrid>::New();
	combined->ShallowCopy(appendFilter->GetOutput());

	return combined;
}

vtkSmartPointer<vtkUnstructuredGrid> PeanoConverter::combineImageData(std::vector<PeanoReader*>* readers) {
	vtkSmartPointer<vtkAppendFilter> appendFilter = vtkSmartPointer<vtkAppendFilter>::New();

	for(uint i = 0; i < readers->size(); i++) {
		std::vector<PeanoPatch*> patches = readers->at(i)->patches;
		for(uint j = 0; j < patches.size(); j++) {
			vtkSmartPointer<vtkImageData> data = toImageData(patches[j]);
			appendFilter->AddInputData(data);
		}
	}

	appendFilter->Update();
	vtkSmartPointer<vtkUnstructuredGrid> combined = vtkSmartPointer<vtkUnstructuredGrid>::New();
	combined->ShallowCopy(appendFilter->GetOutput());

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
