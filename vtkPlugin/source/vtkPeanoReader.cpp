#include "vtkPeanoReader.h"

#include <fstream>

#include "vtkStructuredGridAlgorithm.h"
#include "vtkStructuredGrid.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPolyData.h"
#include "vtkSmartPointer.h"
#include "vtkVertexGlyphFilter.h"

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkPeanoReader);

//----------------------------------------------------------------------------
vtkPeanoReader::vtkPeanoReader() {
  this->FileName = 0;

  //no inputs
  this->SetNumberOfInputPorts(0);
  //one output (a single unstructured grid)
  this->SetNumberOfOutputPorts(1);
}

//----------------------------------------------------------------------------
vtkPeanoReader::~vtkPeanoReader() {
  std::cout << "Peano Reader has loaded!/n";
  this->SetFileName(NULL);
}

//----------------------------------------------------------------------------
int vtkPeanoReader::RequestData(vtkInformation *vtkNotUsed(request), vtkInformationVector **inputVector, vtkInformationVector *outputVector) {
  // vtkInformation *outInfo = outputVector->GetInformationObject(0);
  // vtkStructredGrid *output = vtkStructredGrid::SafeDownCast(outInfo->Get(vtkStructredGrid::DATA_OBJECT()));
  //
  // //create the points of the grid
  // vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  // double x, y, z;
  //
  // x = 0.0;
  // y = 0.0;
  // z = 0.0;
  //
  // for(unsigned int k = 0; k < 2; k++) {
  //   z += 2.0;
  //   for(unsigned int j = 0; j < 3; j++) {
  //     y += 1.0;
  //     for(unsigned int i = 0; i < 2; i++) {
  //       x += .5;
  //       points->InsertNextPoint(x, y, z);
  //       }
  //     }
  //   }
  //
  // // Specify the dimensions of the grid
  // output->SetDimensions(2,3,2);
  // output->SetPoints(points);

  return 1;
}

//----------------------------------------------------------------------------
void vtkPeanoReader::PrintSelf(ostream& os, vtkIndent indent) {
  this->Superclass::PrintSelf(os,indent);
}
