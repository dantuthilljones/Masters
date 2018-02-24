#include "vtkPeanoExplorer.h"
#include "vtkObjectFactory.h" //for the ::New() macro
#include "vtkImplicitFunction.h"

// Macro for the ::New() method
vtkStandardNewMacro(vtkPeanoExplorer);

//----------------------------------------------------------------------------
void vtkPeanoExplorer::PrintSelf(ostream& os, vtkIndent indent) {
  this->Superclass::PrintSelf(os,indent);
}

void vtkPeanoExplorer::SetClipFunction(vtkImplicitFunction* function) {

}
