#ifndef vtkDanReader_h
#define vtkDanReader_h

#include <vtkAlgorithm.h>

class vtkPeanoReader : public vtkAlgorithm {
public:
  vtkTypeMacro(vtkPeanoReader, vtkStructuredGridAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkPeanoReader *New();

  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

protected:

  char* FileName;

  virtual int RequestData(vtkInformation *request,
                          vtkInformationVector **inputVector,
                          vtkInformationVector *outputVector);

  vtkPeanoReader();
  virtual ~vtkPeanoReader();

private:
  vtkPeanoReader(const vtkPeanoReader&);  // Not implemented.
  void operator=(const vtkPeanoReader&);  // Not implemented.
};

#endif
