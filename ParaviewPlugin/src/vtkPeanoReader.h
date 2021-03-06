#ifndef vtkDanReader_h
#define vtkDanReader_h

#include <vector>
#include <string>

#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSmartPointer.h>
#include <vtkStringArray.h>
#include <vtkImplicitFunction.h>

#include "PeanoMetaFile.h"

class vtkPeanoReader : public vtkUnstructuredGridReader {
public:
  vtkTypeMacro(vtkPeanoReader, vtkUnstructuredGridReader);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkPeanoReader *New();

  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  void SetOnTheFly(int preview);
  void SetOnTheFlySize(int x, int y, int z);


  //Methods for selecting the resolution
  void SetResolution(const char* status);
  vtkStringArray *GetResolutions();

  //3D widget selection
  void SetBoxFunction(vtkImplicitFunction*);

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

  PeanoMetaFile*  metaFile;
  vtkStringArray* resolutionsArray;
  std::string selectedResolution;

  int flyX = 0, flyY = 0, flyZ = 0, fly = 0;

  vtkImplicitFunction* exploreFunction = nullptr;

  //variables for caching
  //std::vector<vtkSmartPointer<vtkUnstructuredGrid>>  gridCache;
  //std::vector<bool> gridCacheExists;
};

#endif
