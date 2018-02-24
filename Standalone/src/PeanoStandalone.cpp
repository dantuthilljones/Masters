#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "PeanoReader.h"
#include "PeanoConverter.h"
#include "PeanoMetaFile.h"
#include "PeanoDataSet.h"

#include "vtkSmartPointer.h"
#include "vtkXMLUnstructuredGridWriter.h"

int main(int argc, char* argv[]) {
    bool validParams = false;

    if(argc == 6) {
        std::string command = argv[1];
        if(command.compare("subsample") == 0) {
            validParams = true;
            std::string input = argv[2];

        	int xSize = std::stoi(argv[3]);
        	int ySize = std::stoi(argv[4]);
        	int zSize = std::stoi(argv[5]);

            std::cout << "Reading initial file " << input << "...\n";
            PeanoMetaFile metaFile = PeanoMetaFile(input);

            #pragma omp parallel for
            for(int i = 0; i < metaFile.numberOfDataSets(); i++) {
                PeanoDataSet* dataset = metaFile.getDataSet(i);
                PeanoPatch* sample = dataset->createSubSample(xSize, ySize, zSize, true);
                delete sample;
            }

            //save the metadatafile
            metaFile.save();
            return 0;
        }
    } else if(argc == 4) {
        std::string command = argv[1];
        if(command.compare("convert") == 0) {
            validParams = true;
            std::string input = argv[2];
            std::string output = argv[3];

            std::cout << "Reading initial file " << input << "...\n";
            PeanoMetaFile metaFile = PeanoMetaFile(input);

            #pragma omp parallel for
            for(int i = 0; i < metaFile.numberOfDataSets(); i++) {
                PeanoDataSet* dataset = metaFile.getDataSet(i);
                std::vector<PeanoReader*>* readers = dataset->createReadersFull();
                vtkSmartPointer<vtkUnstructuredGrid> vtkGrid = PeanoConverter::combineImageData(readers);

                //save the patch as an XML file
                vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();

                std::string outFile = output + "/" + dataset->getSimpleName() + ".vtk";

                std::cout << "Writing to file " << outFile << "\n";
                writer->SetFileName(outFile.c_str());
                writer->AddInputDataObject(vtkGrid.GetPointer());
                writer->Write();
            }

            return 0;
        }
    }

    std::cout << "Incorrect usage of the standalone Peano tool..." << (argc-1) << ":\n";
    std::cout << "Program should be ran like so:\n";
    std::cout << "\t./PeanoStandalone subsample INPUT_FILE X_SIZE Y_SIZE Z_SIZE\n";
    std::cout << "or:\n";
    std::cout << "\t./PeanoStandalone convert INPUT_FILE OUTPUT_FOLDER\n";
    return -1;
}
