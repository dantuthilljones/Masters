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

void vtkPeanoExplorer::SetClipFunction(vtkImplicitFunction* function) {
    std::cout << "SetClipFunction called!\n";

    vtkBoxWidget2* widge = vtkBoxWidget2::New();
    widge->CreateDefaultRepresentation();
}
