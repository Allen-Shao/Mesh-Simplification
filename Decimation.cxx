#include <vtkVersion.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkDecimatePro.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkVariantArray.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkLinearSubdivisionFilter.h>

#include "vtkSMFReader.h"
#include "vtkSMFWriter.h"

#include <sstream>
#include <fstream>
#include <string>


vtkSmartPointer<vtkPolyData> Subdivision(vtkSmartPointer<vtkPolyData> input, int targetNumberOfPolygons);


int main(int argc, char *argv[])
{
  if (argc != 6){
    cout << "ExampleCommand: $ ./qslim -t 1 -o <output filename> <input filename>" << endl;
    return EXIT_FAILURE;
  } 
      
  std::cout << "Reading file..." << std::endl;
  int targetNumberOfPolygons = 1000;
  std::string inputFilename = argv[5];
  std::string outputFilename = argv[4];
  vtkSmartPointer<vtkSMFReader> reader = 
    vtkSmartPointer<vtkSMFReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  vtkSmartPointer<vtkPolyData> input = reader->GetOutput();

  
  std::cout << "Before decimation" << std::endl << "------------" << std::endl;
  std::cout << "There are " << input->GetNumberOfPoints() << " points." << std::endl;
  std::cout << "There are " << input->GetNumberOfPolys() << " polygons." << std::endl;
  std::cout << std::endl;

  //Subdivision Process
  if (input->GetNumberOfPolys() < targetNumberOfPolygons){
    std::cout << "Starting subdivision..." << std::endl;
    input = Subdivision(input, targetNumberOfPolygons);
  }


  //Decimation Process
  vtkSmartPointer<vtkDecimatePro> decimate =
    vtkSmartPointer<vtkDecimatePro>::New();
#if VTK_MAJOR_VERSION <= 5
  decimate->SetInputConnection(input->GetProducerPort());
#else  
  decimate->SetInputData(input);
#endif  
  double reduction_percentage = 1.0 - (double)targetNumberOfPolygons/(input->GetNumberOfPolys());
  std::cout << "Reducing " << reduction_percentage*100 << "%" << std::endl;
  decimate->SetTargetReduction(reduction_percentage); //Percentage of reduction 
  decimate->Update();

  vtkSmartPointer<vtkPolyData> decimated =
    vtkSmartPointer<vtkPolyData>::New();
  decimated->ShallowCopy(decimate->GetOutput());

  std::cout << "After decimation" << std::endl << "------------" << std::endl;

  std::cout << "There are " << decimated->GetNumberOfPoints() << " points." << std::endl;
  std::cout << "There are " << decimated->GetNumberOfPolys() << " polygons." << std::endl;

  
  vtkSmartPointer<vtkSMFWriter> writer = 
    vtkSmartPointer<vtkSMFWriter>::New();
  writer->SetFileName(outputFilename.c_str());
  writer->SetInputData(decimated);
  writer->Update();


  return EXIT_SUCCESS;

}


vtkSmartPointer<vtkPolyData> Subdivision(vtkSmartPointer<vtkPolyData> input, int targetNumberOfPolygons){
  //Calculate the number of subdivisions
  int numberOfSubdivisions = 0;
  int originalNumberOfPolys = input->GetNumberOfPolys();
  while (originalNumberOfPolys < targetNumberOfPolygons){
    numberOfSubdivisions++;
    originalNumberOfPolys *= 4;
  }

  vtkSmartPointer<vtkLinearSubdivisionFilter> subdivisionFilter = vtkSmartPointer<vtkLinearSubdivisionFilter>::New();
  subdivisionFilter.GetPointer()->SetNumberOfSubdivisions(numberOfSubdivisions);
  #if VTK_MAJOR_VERSION <= 5
    subdivisionFilter->SetInputConnection(input->GetProducerPort());
  #else
    subdivisionFilter->SetInputData(input);
  #endif
    subdivisionFilter->Update();
  std::cout << "After subdivision" << std::endl << "------------" << std::endl;
  std::cout << "There are " << subdivisionFilter->GetOutput()->GetNumberOfPoints()
            << " points." << std::endl;
  std::cout << "There are " << subdivisionFilter->GetOutput()->GetNumberOfPolys()
            << " triangles." << std::endl;
  std::cout << std::endl;
  return subdivisionFilter->GetOutput();
}






//Visualization
//   vtkSmartPointer<vtkPolyDataMapper> inputMapper =
//     vtkSmartPointer<vtkPolyDataMapper>::New();
// #if VTK_MAJOR_VERSION <= 5
//   inputMapper->SetInputConnection(input->GetProducerPort());
// #else
//   inputMapper->SetInputData(input);
// #endif
//   vtkSmartPointer<vtkActor> inputActor =
//     vtkSmartPointer<vtkActor>::New();
//   inputActor->SetMapper(inputMapper);

//   vtkSmartPointer<vtkPolyDataMapper> decimatedMapper =
//     vtkSmartPointer<vtkPolyDataMapper>::New();
// #if VTK_MAJOR_VERSION <= 5
//   decimatedMapper->SetInputConnection(decimated->GetProducerPort());
// #else
//   decimatedMapper->SetInputData(decimated);
// #endif
//   vtkSmartPointer<vtkActor> decimatedActor =
//     vtkSmartPointer<vtkActor>::New();
//   decimatedActor->SetMapper(decimatedMapper);

//   // There will be one render window
//   vtkSmartPointer<vtkRenderWindow> renderWindow =
//     vtkSmartPointer<vtkRenderWindow>::New();
//   renderWindow->SetSize(600, 300);

//   // And one interactor
//   vtkSmartPointer<vtkRenderWindowInteractor> interactor =
//     vtkSmartPointer<vtkRenderWindowInteractor>::New();
//   interactor->SetRenderWindow(renderWindow);

//   // Define viewport ranges
//   // (xmin, ymin, xmax, ymax)
//   double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
//   double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

//   // Setup both renderers
//   vtkSmartPointer<vtkRenderer> leftRenderer =
//     vtkSmartPointer<vtkRenderer>::New();
//   renderWindow->AddRenderer(leftRenderer);
//   leftRenderer->SetViewport(leftViewport);
//   leftRenderer->SetBackground(.6, .5, .4);

//   vtkSmartPointer<vtkRenderer> rightRenderer =
//     vtkSmartPointer<vtkRenderer>::New();
//   renderWindow->AddRenderer(rightRenderer);
//   rightRenderer->SetViewport(rightViewport);
//   rightRenderer->SetBackground(.4, .5, .6);

//   // Add the sphere to the left and the cube to the right
//   leftRenderer->AddActor(inputActor);
//   rightRenderer->AddActor(decimatedActor);

//   leftRenderer->ResetCamera();

//   rightRenderer->ResetCamera();

//   renderWindow->Render();
//   interactor->Start();
  
//   return EXIT_SUCCESS;

