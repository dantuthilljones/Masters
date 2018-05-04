#ifndef PEANOEXPLORER_H_
#define PEANOEXPLORER_H_

#include "vtkUnstructuredGridAlgorithm.h"
#include "vtkFiltersGeneralModule.h"
#include "vtkImplicitFunction.h"

class vtkPeanoExplorer : public vtkUnstructuredGridAlgorithm {
public:
    vtkTypeMacro(vtkPeanoExplorer, vtkUnstructuredGridAlgorithm);
    void PrintSelf(ostream& os, vtkIndent indent) override;

    static vtkPeanoExplorer *New();

    //@{
    /**
     * Specify the implicit function with which to perform the area selection. If you
     * do not define an implicit function, then the input scalar data will be
     * used for clipping.
     */
    virtual void SetBoxFunction(vtkImplicitFunction*);
    //@}

    vtkImplicitFunction *BoxFunction;


};

#endif /* PEANOEXPLORER_H_ */
