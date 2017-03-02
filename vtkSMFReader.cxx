#include "vtkSMFReader.h"

#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkTriangle.h"

#include <sstream>
#include <fstream>

vtkStandardNewMacro(vtkSMFReader);

// Description:
// Instantiate object with NULL filename.
vtkSMFReader::vtkSMFReader()
{
  this->FileName = NULL;

  this->SetNumberOfInputPorts(0);
}

vtkSMFReader::~vtkSMFReader()
{
  if (this->FileName)
  {
    delete [] this->FileName;
    this->FileName = NULL;
  }
}

/*--------------------------------------------------------

This is only partial support for the OFF format, which is 
quite complicated. To find a full specification,
search the net for "OFF format", eg.:

http://people.sc.fsu.edu/~burkardt/data/off/off.html

We support only vertices and faces composed of 3 vertices.

---------------------------------------------------------*/

// a replacement for isspace()
int is_whitespace(char c)
{
  if ( c==' ' || c=='\t' || c=='\n' || c=='\r' || c=='\v' || c=='\f')
    return 1;
  else
    return 0;
}

int vtkSMFReader::RequestData(
                              vtkInformation *vtkNotUsed(request),
    vtkInformationVector **vtkNotUsed(inputVector),
                                      vtkInformationVector *outputVector)
{
  // get the info object
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  // get the ouptut
  vtkPolyData *output = vtkPolyData::SafeDownCast(
      outInfo->Get(vtkDataObject::DATA_OBJECT()));

  if (!this->FileName) 
  {
    vtkErrorMacro(<< "A FileName must be specified.");
    return 0;
  }

  std::ifstream in(this->FileName);

  if (!in) 
  {
    vtkErrorMacro(<< "File " << this->FileName << " not found");
    return 0;
  }

  vtkDebugMacro(<<"Reading file");

  // intialise some structures to store the file contents in
  vtkPoints *points = vtkPoints::New(); 
  vtkCellArray *polys = vtkCellArray::New();

  // -- work through the file line by line, assigning into the above structures as appropriate --

  float xyz[3];
  std::string line;

  //Read until we get to the first line that is not a comment or a blank line.
  //This line second states the number of vertices, faces, and edges. 
  while(getline(in, line))
  {
    //std::cout << line << std::endl;
    if(line.size() == 0)
      continue;
    if(line[0] == '#')
      continue;

    //if we get to here, this is the info line
    break;
  }
  //std::cout << "Found info line." << std::endl;

  //At this point, the line were are interested in is stored in 'line'
  //We are only interested in vertices and faces.
  //std::cout << "Vertices: " << NumberOfVertices << " Faces: " << NumberOfFaces << std::endl;
  //Now we can start to read the vertices
  unsigned int VertexCounter = 0;

  do
  {
    if(line.size() == 0) //skip blank lines (they should only occur before the vertices start)
      continue;

    if (line[0] == 'v'){
    	std::stringstream ssVertex;
    	ssVertex << line.substr(2, line.size());


    	double x, y, z;
    	ssVertex >> x >> y >> z;
    	points->InsertNextPoint(x, y, z);
    	continue;
    }

    if (line[0] == 'f'){
    	std::stringstream ssFace;
    	ssFace << line.substr(2, line.size());
    	unsigned int Vert0, Vert1, Vert2;
    	ssFace >> Vert0 >> Vert1 >> Vert2;
    	Vert0--; Vert1--; Vert2--;
    	vtkTriangle* triangle = vtkTriangle::New();

    	triangle->GetPointIds()->SetId(0, Vert0);
    	triangle->GetPointIds()->SetId(1, Vert1);
    	triangle->GetPointIds()->SetId(2, Vert2);

    	polys->InsertNextCell(triangle);
    	triangle->Delete();
      continue;
    }

  } while(getline(in, line)); // (end of while loop)


  // we have finished with the file
  in.close(); 

  output->SetPoints(points);
  output->SetPolys(polys);

  points->Delete();
  polys->Delete();

  // //output testing
  // vtkSmartPointer<vtkPoints> point = 
  //   output->GetPoints();
  // vtkSmartPointer<vtkCellArray> poly = 
  //   output->GetPolys();

  // //Printout vertex
  // for (vtkIdType i = 0; i < point->GetNumberOfPoints(); i++){
  //   double* x;
  //   x = point->GetPoint(i);
  //   for (unsigned j = 0; j < 3; j++){
  //     std::cout << x[j] << ' ';
  //   }
  //   std::cout << std::endl;
  // }

  // //Printout faces
  // poly->InitTraversal();
  // vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();
  // while(polys->GetNextCell(idList)){
  //   std::cout << 'f' << ' ';
  //   for(vtkIdType pointId = 0; pointId < idList->GetNumberOfIds(); pointId++){
  //     std::cout << idList->GetId(pointId) << ' ';
  //   }
  //   std::cout << std::endl;
  // }



  return 1;
}

void vtkSMFReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "File Name: " 
      << (this->FileName ? this->FileName : "(none)") << "\n";
}
