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
#include "vtkPoints.h"
#include "vtkIdTypeArray.h"
#include "vtkCellArray.h"
#include "vtkVoxel.h"


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

vtkSmartPointer<vtkUnstructuredGrid> PeanoConverter::toUnstructuredGrid(PeanoPatch* patch) {

	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

	PeanoVariable* structure = patch->getStructure();

	double* offsets = patch->offsets;
	double* sizes = patch->sizes;
	double* mapping = structure->mapping;
	int mappings = structure->mappings;
	int dimensions = patch->dimensions;
	int numberOfPoints = mappings/3;
	//std::cout << "Number of points = " << numberOfPoints << "\n";
	points->SetNumberOfPoints(numberOfPoints);

	for(int i = 0; i < numberOfPoints; i++) {
		int index = i*patch->dimensions;

		double position[3] = {0, 0, 0};
		for(int j = 0; j < 3; j++) {
			position[j] = mapping[index + j]*sizes[j] + offsets[j];
		}
		points->SetPoint(i, position);
	}


	int dimensions3D[3] = {1, 1, 1};
	int totalCells = 1;
	for(int i = 0; i < 3; i++) {
		totalCells *= patch->patchSize[i];
		dimensions3D[i] = patch->patchSize[i];
	}

	vtkSmartPointer<vtkCellArray> connectivity = vtkSmartPointer<vtkCellArray>::New();
	connectivity->Allocate(VTK_VOXEL,totalCells);

	for(int x = 0; x < dimensions3D[0]; x++) {
		for(int y = 0; y < dimensions3D[1]; y++) {
			for(int z = 0; z < dimensions3D[2]; z++) {
				vtkSmartPointer<vtkVoxel> voxel = vtkSmartPointer<vtkVoxel>::New();
				vtkIdList* points = voxel->GetPointIds();
				points->SetId(0, xyzToIndex(x,y,z, dimensions3D));
				points->SetId(1, xyzToIndex(x+1,y,z, dimensions3D));
				points->SetId(2, xyzToIndex(x,y+1,z, dimensions3D));
				points->SetId(3, xyzToIndex(x+1,y+1,z, dimensions3D));
				points->SetId(4, xyzToIndex(x,y,z+1, dimensions3D));
				points->SetId(5, xyzToIndex(x+1,y,z+1, dimensions3D));
				points->SetId(6, xyzToIndex(x,y+1,z+1, dimensions3D));
				points->SetId(7, xyzToIndex(x+1,y+1,z+1, dimensions3D));

				connectivity->InsertNextCell(voxel);
			}
		}
	}

	vtkSmartPointer<vtkUnstructuredGrid> grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
	grid->SetPoints(points);
	grid->SetCells(VTK_VOXEL, connectivity);

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
			grid->GetCellData()->AddArray(variableArray);
		} else if(data->structure->type == Vertex_Values) {
			grid->GetPointData()->AddArray(variableArray);
		}
	}



	return grid;
}

int PeanoConverter::xyzToIndex(int x, int y, int z, int dimensions[3]) {
	return x + y*(dimensions[0]+1) + z*(dimensions[0]+1)*(dimensions[1]+1);
}

vtkSmartPointer<vtkUnstructuredGrid> PeanoConverter::combineImageData(std::vector<PeanoPatch*>* patches){
	vtkSmartPointer<vtkAppendFilter> appendFilter = vtkSmartPointer<vtkAppendFilter>::New();
	for(uint i = 0; i < patches->size(); i++) {
		PeanoPatch* patch = patches->at(i);

		if(patch->hasMappings()) {
			appendFilter->AddInputData(toUnstructuredGrid(patches->at(i)));
		} else {
			appendFilter->AddInputData(toImageData(patches->at(i)));
		}
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
			PeanoPatch* patch = patches[j];
			if(patch->hasMappings()) {
				appendFilter->AddInputData(toUnstructuredGrid(patch));
			} else {
				appendFilter->AddInputData(toImageData(patch));
			}
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
