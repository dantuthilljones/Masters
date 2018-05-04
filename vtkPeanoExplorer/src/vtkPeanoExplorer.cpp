#include "vtkPeanoExplorer.h"
#include "vtkObjectFactory.h" //for the ::New() macro
#include "vtkImplicitFunction.h"
#include "vtkBoxWidget2.h"
#include "vtkBoxRepresentation.h"

// Macro for the ::New() method
vtkStandardNewMacro(vtkPeanoExplorer);

//----------------------------------------------------------------------------
void vtkPeanoExplorer::PrintSelf(ostream& os, vtkIndent indent) {
  this->Superclass::PrintSelf(os,indent);
}

void vtkPeanoExplorer::SetBoxFunction(vtkImplicitFunction* function) {
    std::cout << "SetBoxFunction called!\n";

    for(double i = -2; i < 4.1; i += 0.3) {
        for(double j = -2; j < 4.1; j += 0.3) {
            for(double k = -2; k < 4.1; k += 0.3) {
                if(function->FunctionValue(i,j,k) > 0) {
                    std::cout << "Outside: (" << i << "," << j << "," << k << ")\n";
                } else {
                    std::cout << "inside: (" << i << "," << j << "," << k << ")\n";
                }
            }
        }
    }

    // vtkBoxWidget2* widge = vtkBoxWidget2::New();
    // widge->CreateDefaultRepresentation();
    // widge->SetRotationEnabled(0);
}
