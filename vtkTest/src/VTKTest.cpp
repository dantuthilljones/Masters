/*
 * PeanoVTK.cpp
 *
 *  Created on: 17 Oct 2017
 *      Author: dan
 */

#include <iostream>
#include <vector>

#include "vtkUnstructuredGrid.h"
#include "vtkSmartPointer.h"
#include "vtkXMLUnstructuredGridWriter.h"
#include "vtkCellArray.h"
#include "vtkPoints.h"
#include "vtkVoxel.h"
#include "vtkDoubleArray.h"
#include "vtkCellData.h"
#include "vtkPointData.h"

int xyz(int x, int y, int z) {
	return x*9 + y*3 + z;
}

int main(int argc, char* argv[]) {

	std::cout << "Test update!";


	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	points->SetNumberOfPoints(3*3*3);

	int point = 0;
	for(int x = 0; x < 3; x++) {
		for(int y = 0; y < 3; y++) {
			for(int z = 0; z < 3; z++) {
				points->SetPoint(point, x, y, z);
				point++;
			}
		}
	}

	vtkSmartPointer<vtkCellArray> connectivity =  vtkSmartPointer<vtkCellArray>::New();
	connectivity->Allocate(VTK_VOXEL,8);

	int maxIndex = 0;


	int cellIndex = 0;
	for(int x = 0; x < 2; x++) {
		for(int y = 0; y < 2; y++) {
			for(int z = 0; z < 2; z++) {
				vtkSmartPointer<vtkVoxel> voxel = vtkSmartPointer<vtkVoxel>::New();
				vtkIdList* points = voxel->GetPointIds();
				points->SetId(0, xyz(x,y,z));
				points->SetId(1, xyz(x+1,y,z));
				points->SetId(2, xyz(x,y,z+1));
				points->SetId(3, xyz(x+1,y,z+1));
				points->SetId(4, xyz(x,y+1,z));
				points->SetId(5, xyz(x+1,y+1,z));
				points->SetId(6, xyz(x,y+1,z+1));
				points->SetId(7, xyz(x+1,y+1,z+1));
				connectivity->InsertNextCell(voxel);
			}
		}
	}

	vtkSmartPointer<vtkUnstructuredGrid> grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
	grid->SetPoints(points);
	grid->SetCells(VTK_VOXEL, connectivity);

	//allocate cell variables
	vtkSmartPointer<vtkDoubleArray> variableCell = vtkSmartPointer<vtkDoubleArray>::New();
	variableCell->SetNumberOfComponents(1);
	variableCell->SetName("CellData");

	//std:: << "\n " << data->variableName << ": ";
	for(int i = 0; i < 2*2*2; i++) {
		variableCell->InsertNextTuple1(i);
	}
	grid->GetCellData()->AddArray(variableCell);


	//allocate point variables
	vtkSmartPointer<vtkDoubleArray> variablePoint = vtkSmartPointer<vtkDoubleArray>::New();
	variablePoint->SetNumberOfComponents(1);
	variablePoint->SetName("PointData");

	//std:: << "\n " << data->variableName << ": ";
	for(int i = 0; i < 3*3*3; i++) {
		variablePoint->InsertNextTuple1(i);
	}
	grid->GetPointData()->AddArray(variablePoint);


	std::cout << "Writing file TestOut.vtk...\n";
	vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
	writer->SetFileName("TestOut.vtk");
	writer->AddInputDataObject(grid.GetPointer());
	writer->Write();

	std::cout << "Done!\n";
}
