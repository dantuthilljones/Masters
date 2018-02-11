#ifndef vtkDanReader_h
#define vtkDanReader_h

#include <vector>
#include <string>

#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSmartPointer.h>
#include <vtkStringArray.h>

#include "PeanoMetaFile.h"

class vtkPeanoReader : public vtkUnstructuredGridReader {
public:
  vtkTypeMacro(vtkPeanoReader, vtkUnstructuredGridReader);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkPeanoReader *New();

  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  void SetPreview(int preview);
  void SetPreviewSize(int x, int y, int z);


  //Methods for selecting the resolution
  void SetResolution(const char* status);
  vtkStringArray *GetResolutions();

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

  //variables for caching
  //std::vector<vtkSmartPointer<vtkUnstructuredGrid>>  gridCache;
  //std::vector<bool> gridCacheExists;
};

#endif
