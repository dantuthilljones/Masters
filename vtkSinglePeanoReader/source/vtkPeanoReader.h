#ifndef vtkDanReader_h
#define vtkDanReader_h

#include <vector>
#include <string>

#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSmartPointer.h>

#include "PeanoMetaReader.h"

class vtkPeanoReader : public vtkUnstructuredGridReader {
public:
  vtkTypeMacro(vtkPeanoReader, vtkUnstructuredGridReader);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkPeanoReader *New();

  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

protected:

  char* FileName;

  virtual int RequestData(vtkInformation *request,
                          vtkInformationVector **inputVector,
                          vtkInformationVector *outputVector);

  virtual int RequestInformation(vtkInformation*,
                         vtkInformationVector**,
                         vtkInformationVector*);

  vtkPeanoReader();
  virtual ~vtkPeanoReader();

private:
  vtkPeanoReader(const vtkPeanoReader&);  // Not implemented.
  void operator=(const vtkPeanoReader&);  // Not implemented.

  std::vector<std::vector<std::string>>  datasets;

  std::vector<vtkSmartPointer<vtkUnstructuredGrid>>  gridCache;
  std::vector<bool> gridCacheExists;
};

#endif
