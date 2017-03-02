#include "vtkSMFWriter.h"

#include "vtkPolyData.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"

#include <sstream>
#include <fstream>

vtkStandardNewMacro(vtkSMFWriter);

vtkSMFWriter::vtkSMFWriter(){
	this->FileName = NULL;

	this->SetNumberOfInputPorts(1);
	this->SetNumberOfOutputPorts(0);
}

vtkSMFWriter::~vtkSMFWriter(){
	if (this->FileName){
		delete [] this->FileName;
		this->FileName = NULL;
	}
}

int vtkSMFWriter::RequestData(vtkInformation *vtkNotUsed(request),
                               vtkInformationVector **inputVector,
                               vtkInformationVector *vtkNotUsed(outputVector))
{
	vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  	vtkPolyData *input = vtkPolyData::SafeDownCast(
    	inInfo->Get(vtkDataObject::DATA_OBJECT()));

	ofstream smfFile;
	smfFile.open(this->FileName);

	vtkSmartPointer<vtkPoints> points = 
	input->GetPoints();
	vtkSmartPointer<vtkCellArray> polys = 
	input->GetPolys();




	smfFile << "begin" << std::endl;

	//Writing vertex
	for (vtkIdType i = 0; i < points->GetNumberOfPoints(); i++){
		smfFile << 'v' << ' ';
		double* x;
		x = points->GetPoint(i);
		for (unsigned j = 0; j <3; j++){
		  smfFile << x[j] << ' ';
		}
		smfFile << std::endl;
	}
	//Writing faces
	polys->InitTraversal();
	vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();
	while(polys->GetNextCell(idList)){
		smfFile << 'f' << ' ';
		for(vtkIdType pointId = 0; pointId < idList->GetNumberOfIds(); pointId++){
			smfFile << idList->GetId(pointId)+1 << ' ';
		}
		smfFile << std::endl;
	}

	smfFile << "end" << std::endl;

	smfFile.close();

	return 1;
}

void vtkSMFWriter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
 
  if (this->FileName)
    {
    os << indent << "FileName: " << this->FileName << "\n";
    }
  else
    {
    os << indent << "FileName: (null)\n";      
    }
}
