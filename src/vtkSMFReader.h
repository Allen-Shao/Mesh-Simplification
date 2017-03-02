#ifndef __vtkSMFReader_h
#define __vtkSMFReader_h

#include "vtkPolyDataAlgorithm.h"

class vtkSMFReader : public vtkPolyDataAlgorithm
{
public:
  static vtkSMFReader *New();
  vtkTypeMacro(vtkSMFReader,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Specify file name of .off file.
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

protected:
  vtkSMFReader();
  ~vtkSMFReader();

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

  char *FileName;
private:
  vtkSMFReader(const vtkSMFReader&);  // Not implemented.
  void operator=(const vtkSMFReader&);  // Not implemented.
};

#endif
