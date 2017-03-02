#ifndef __vtkSMFWriter_h
#define __vtkSMFWriter_h

#include "vtkPolyDataAlgorithm.h"

class vtkSMFWriter : public vtkPolyDataAlgorithm
{
public:
  static vtkSMFWriter *New();
  vtkTypeMacro(vtkSMFWriter,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);


  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

protected:
  vtkSMFWriter();
  ~vtkSMFWriter();

private:
  vtkSMFWriter(const vtkSMFWriter&);  // Not implemented.
  void operator=(const vtkSMFWriter&);  // Not implemented.

  char *FileName;

};

#endif