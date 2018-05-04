#include "vtkPeanoReader.h"

#include "PeanoReader.h"
#include "PeanoConverter.h"
#include "PeanoMetaFile.h"

#include <fstream>
#include <string>

#include "vtkUnstructuredGrid.h"
#include "vtkStructuredGridAlgorithm.h"
#include "vtkStructuredGrid.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPolyData.h"
#include "vtkSmartPointer.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkStringArray.h"
#include "vtkPVBox.h"
#include "vtkImplicitFunction.h"

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

int vtkPeanoReader::RequestInformation( vtkInformation* reqInfo,
            vtkInformationVector** inVector, vtkInformationVector* outVector) {
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
    metaFile = new PeanoMetaFile(this->GetFileName());

    //tell paraview that I can provide time varying data
    std::cout << "Telling paraview can handle time varying data\n";
    info->Set(CAN_HANDLE_PIECE_REQUEST(), 1);

    //tell the caller what range of times I can deal with
    std::cout << "Telling paraview we have a time range of 0 to " << metaFile->numberOfDataSets() << "\n";
    double timeRange[2] = {0, metaFile->numberOfDataSets() -1};
    info->Set(vtkStreamingDemandDrivenPipeline::TIME_RANGE(), timeRange, 2);

    //tell the caller the actual steps that I can deal with
    double timeSteps[metaFile->numberOfDataSets()];
    std::cout << "Telling paraview our time steps are: ";
    for(int i = 0; i < metaFile->numberOfDataSets(); i++) {
        timeSteps[i] = i;
        std::cout << i << " ";
    }
    std::cout << "\n";
    info->Set(vtkStreamingDemandDrivenPipeline::TIME_STEPS(), timeSteps, metaFile->numberOfDataSets());

    //resize the cache, not currently used
    //gridCache.resize(numDatasets, vtkSmartPointer<vtkUnstructuredGrid>::New());
    //gridCacheExists.resize(numDatasets, false);


    //create the values for the dresolution drop down box
    std::vector<std::vector<int>>* resolutions = metaFile->getDataSet(0)->getResolutions();
    int newResolutions = resolutions->size();

    resolutionsArray = vtkStringArray::New();
    resolutionsArray->SetNumberOfValues(newResolutions +1);
    resolutionsArray->SetValue(0, "Full");

    for(int i = 0; i < newResolutions; i++) {
        std::vector<int> xyz = resolutions->at(i);
        resolutionsArray->SetValue(i+1, "(" + std::to_string(xyz[0]) + "," + std::to_string(xyz[1])
         + "," + std::to_string(xyz[2]) + ")");
    }

    return 1;
}

//----------------------------------------------------------------------------
int vtkPeanoReader::RequestData(vtkInformation *vtkNotUsed(request), vtkInformationVector **inputVector,
        vtkInformationVector *outputVector) {
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
        reqTS = outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_TIME_STEP());
        reqTime = reqTS;
    }


    int datasetIndex = reqTime;
    std::cout << "Paraview has requested time " << reqTime << " (" << datasetIndex << ")...\n";


    //used for caching
    // if(gridCacheExists[datasetIndex]) {
    //     std::cout << "Returning cached object...\n";
    //     output->ShallowCopy(gridCache[datasetIndex]);
    //     return 1;
    // }

    if(fly) {
        std::cout << "Paraview has requested on the fly resolution (" << flyX << "," << flyY << "," << flyZ << ")\n";


        PeanoPatch* patch = nullptr;

        if(exploreFunction == nullptr) {
            std::cout << "Subsampling on to a new PeanoPatch...\n";
            patch = metaFile->getDataSet(datasetIndex)->createSubSample(flyX, flyY, flyZ, false);
            std::cout << "Done subsampling!\n";
        } else {
            vtkPVBox* box = (vtkPVBox*) this->exploreFunction;
            box->SetRotation(0,0,0);

            double* position = new double[3];
            double* scale = new double[3];

            box->GetPosition(position);
            box->GetScale(scale);

            patch = metaFile->getDataSet(datasetIndex)->createSubSample(flyX, flyY, flyZ, position, scale);

        }


        std::vector<PeanoPatch*>* patches = new std::vector<PeanoPatch*>();
        patches->push_back(patch);

        std::cout << "Converting patch to vtkUnstructuredGrid...\n";
        vtkSmartPointer<vtkUnstructuredGrid> outGrid = PeanoConverter::combineImageData(patches);
        std::cout << "Done!\n";

        std::cout << "Setting output grid...\n";
        output->ShallowCopy(outGrid);
        std::cout << "Done!\n";

        std::cout << "Deleting patch...\n";
        delete patch;
        delete patches;
        std::cout << "Done!\n";
    } else {
        std::cout << "Paraview has requested precomputed resolution " << selectedResolution << "\n";

        std::vector<PeanoReader*>* readers = nullptr;

        if(exploreFunction != nullptr) {
            std::cout << "Loading patches inside selection box...\n";
            vtkPVBox* box = (vtkPVBox*) this->exploreFunction;
            box->SetRotation(0,0,0);

            double* position = new double[3];
            double* scale = new double[3];

            box->GetPosition(position);
            box->GetScale(scale);

            readers = metaFile->getDataSet(datasetIndex)->getReadersInside(exploreFunction);

        } else if(selectedResolution.compare("Full") == 0) {
            readers = metaFile->createReadersFull(datasetIndex);
        } else {
            for(int i = 1; i < resolutionsArray->GetNumberOfValues(); i++) {
                std::cout << "Resolution array value = " << resolutionsArray->GetValue(i) << "\n";
                if(selectedResolution.compare(resolutionsArray->GetValue(i)) == 0) {
                    readers = metaFile->createReadersResolution(datasetIndex, i-1);
                    break;
                }
            }
        }

        std::cout << "readers address = " << readers << "\n";

        std::cout << "Generating output grid...\n";
        vtkSmartPointer<vtkUnstructuredGrid> outGrid = PeanoConverter::combineImageData(readers);
        std::cout << "Done!\n";

        std::cout << "Setting output grid...\n";
        output->ShallowCopy(outGrid);
        std::cout << "Done!\n";

        std::cout << "Deleting readers...\n";
        for(uint i = 0; i < readers->size(); i++) {
            delete readers->at(i);
        }
    }

    std::cout << "Returning 1...\n";
    return 1;
}

void vtkPeanoReader::SetResolution(const char* status) {
    selectedResolution = std::string(status);
}

vtkStringArray *vtkPeanoReader::GetResolutions() {
    return resolutionsArray;
}

void vtkPeanoReader::SetOnTheFly(int fly) {
    std::cout << "SetOntheFly called with value " << fly <<"\n";
    this->fly = fly;

}

void vtkPeanoReader::SetOnTheFlySize(int x, int y, int z) {
    std::cout << "SetOntheFlySize called with values (" << x << "," << y << "," << z << ")\n";
    this->flyX = x;
    this->flyY = y;
    this->flyZ = z;
}

void vtkPeanoReader::SetBoxFunction(vtkImplicitFunction* pointer) {
    std::cout << "SetBoxFunction called!\n";

    if(pointer == nullptr) {
        std::cout << "Implicit Function Null!\n";
    }

    this->exploreFunction = pointer;
}

//----------------------------------------------------------------------------
void vtkPeanoReader::PrintSelf(ostream& os, vtkIndent indent) {
  this->Superclass::PrintSelf(os,indent);
}
