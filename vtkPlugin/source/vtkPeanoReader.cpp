#include "vtkPeanoReader.h"

#include "PeanoReader.h"
#include "PeanoConverter.h"
#include "PeanoMetaReader.h"

#include <fstream>

#include "vtkUnstructuredGrid.h"
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
}

//----------------------------------------------------------------------------
vtkPeanoReader::~vtkPeanoReader() {
  std::cout << "Peano Reader has loaded!/n";
  this->SetFileName(NULL);
}

//----------------------------------------------------------------------------
int vtkPeanoReader::RequestData(vtkInformation *vtkNotUsed(request), vtkInformationVector **inputVector, vtkInformationVector *outputVector) {
    if (!this->GetFileName()) {
        vtkErrorMacro("Filename is not set");
        return 0;
    }

    std::cout << "Reading initial file " << this->GetFileName() << "...\n";
    PeanoMetaReader* metaReader = new PeanoMetaReader(this->GetFileName());
    std::vector<std::vector<std::string>> datasets = metaReader->getDataSets();

    //set the number of outputs
    this->SetNumberOfOutputPorts(datasets.size());

    //#pragma omp parallel for
    for(uint i = 0; i < datasets.size(); i++) {
    //for(uint i = 0; i < 1; i++) {

        std::vector<std::string> dataset = datasets[i];
        std::vector<PeanoReader*> readers;
        for(uint j = 0; j < dataset.size(); j++) {
            std::string file = dataset[j];
            std::cout << "Reading data from " << file << "...\n";
            PeanoReader* reader = new PeanoReader(file);
            readers.push_back(reader);
        }

        std::cout << "Setting output grid...\n";
        vtkSmartPointer<vtkUnstructuredGrid> output = PeanoConverter::combineImageData(&readers);
        this->GetExecutive()->SetOutputData(i, output);
        std::cout << "Output grid set!\n";

        for(PeanoReader* reader: readers) {
            std::cout << "Deleting reader...\n";
            delete reader;
        }


    }
  return 1;
}


int vtkPeanoReader::FillOutputPortInformation(int port, vtkInformation* info) {
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPeanoObject-" + std::to_string(port);
    return 1;
}

//----------------------------------------------------------------------------
void vtkPeanoReader::PrintSelf(ostream& os, vtkIndent indent) {
  this->Superclass::PrintSelf(os,indent);
}
