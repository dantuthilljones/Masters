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
#include "vtkStreamingDemandDrivenPipeline.h"

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkPeanoReader);

//----------------------------------------------------------------------------
vtkPeanoReader::vtkPeanoReader() {
  this->FileName = 0;

  //no inputs
  this->SetNumberOfInputPorts(0);

  //1 output
  this->SetNumberOfOutputPorts(1);
}

//----------------------------------------------------------------------------
vtkPeanoReader::~vtkPeanoReader() {
  std::cout << "Peano Reader has loaded!\n";
  this->SetFileName(NULL);
}

int vtkPeanoReader::RequestInformation( vtkInformation* reqInfo, vtkInformationVector** inVector, vtkInformationVector* outVector) {
    if(!this->Superclass::RequestInformation(reqInfo,inVector,outVector)) {
        return 0;
    }

    vtkInformation *info=outVector->GetInformationObject(0);

    //read the input file and calculate the number of time Steps
    if (!this->GetFileName()) {
        vtkErrorMacro("Filename is not set");
        return 0;
    }

    std::cout << "Reading initial file " << this->GetFileName() << "...\n";
    PeanoMetaReader metaReader = PeanoMetaReader(this->GetFileName());
    datasets = metaReader.getDataSets();
    int numDatasets = datasets.size();



    //tell the caller what range of times I can deal with
    std::cout << "Telling paraview we have a time range of 0 to " << numDatasets << "\n";
    double timeRange[2] = {0, numDatasets -1};
    info->Set(vtkStreamingDemandDrivenPipeline::TIME_RANGE(), timeRange, 2);

    //tell the caller the actual steps that I can deal with
    double timeSteps[numDatasets];
    std::cout << "Telling paraview our time steps are: ";
    for(int i = 0; i < numDatasets; i++) {
        timeSteps[i] = i;
        std::cout << i << " ";
    }
    std::cout << "\n";
    info->Set(vtkStreamingDemandDrivenPipeline::TIME_STEPS(), timeSteps, numDatasets);

    //tell it that I can provide time varying data
    std::cout << "Telling paraview can handle time varying data\n";
    info->Set(CAN_HANDLE_PIECE_REQUEST(), 1);

    //resize the cache
    gridCache.resize(numDatasets, vtkSmartPointer<vtkUnstructuredGrid>::New());
    gridCacheExists.resize(numDatasets, false);

    return 1;
}

//----------------------------------------------------------------------------
int vtkPeanoReader::RequestData(vtkInformation *vtkNotUsed(request), vtkInformationVector **inputVector, vtkInformationVector *outputVector) {
    if (!this->GetFileName()) {
        vtkErrorMacro("Filename is not set");
        return 0;
    }

    vtkInformation *outInfo = outputVector->GetInformationObject(0);
    vtkUnstructuredGrid *output = vtkUnstructuredGrid::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));
    if (!output) {
        return 0;
    }

    //determine what time is being asked for
    double reqTime = 0.0;
    //int reqNTS = 0;
    double reqTS(0);
    if (outInfo->Has(vtkStreamingDemandDrivenPipeline::UPDATE_TIME_STEP())) {
        //reqNTS = outInfo->Length
        //  (vtkStreamingDemandDrivenPipeline::UPDATE_TIME_STEP());
        reqTS = outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_TIME_STEP());

        //TODO: produce multiblock output when multiple time steps are asked for
        //for now just answer the first one
        reqTime = reqTS;
    }


    int datasetIndex = reqTime;
    std::cout << "Paraview has requested time " << reqTime << " (" << datasetIndex << ")...\n";


    if(gridCacheExists[datasetIndex]) {
        std::cout << "Returning cached object...\n";
        output->ShallowCopy(gridCache[datasetIndex]);
        return 1;
    }

    std::vector<std::string> dataset = datasets[datasetIndex];
    std::vector<PeanoReader*> readers;

    for(uint j = 0; j < dataset.size(); j++) {
        std::string file = dataset[j];
        std::cout << "Reading data from " << file << "...\n";
        PeanoReader* reader = new PeanoReader(file);
        readers.push_back(reader);
    }

    std::cout << "Generating output grid...\n";
    vtkSmartPointer<vtkUnstructuredGrid> outGrid = PeanoConverter::combineImageData(&readers);
    std::cout << "Done!...\n";

    std::cout << "Storing output grid incase it is requested again...\n";
    gridCache[datasetIndex] = outGrid;
    std::cout << "Done!...\n";

    std::cout << "Setting output grid...\n";
    output->ShallowCopy(outGrid);
    std::cout << "Done!...\n";

    for(PeanoReader* reader: readers) {
        std::cout << "Deleting reader...\n";
        delete reader;
    }

    //add new grid to cache
    gridCache[datasetIndex] = outGrid;
    gridCacheExists[datasetIndex] = true;

    return 1;
}

void vtkPeanoReader::SetPreview(int preview) {
    std::cout << "SetPreview called with value " << preview <<"\n";
}

void vtkPeanoReader::SetPreviewSize(int x, int y, int z) {
    std::cout << "SetPreviewSize called with values (" << x << "," << y << "," << z << ")\n";
}

//----------------------------------------------------------------------------
void vtkPeanoReader::PrintSelf(ostream& os, vtkIndent indent) {
  this->Superclass::PrintSelf(os,indent);
}
