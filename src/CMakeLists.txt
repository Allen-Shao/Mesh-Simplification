
cmake_minimum_required(VERSION 2.8)

PROJECT(DECIMATION)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(simplification MACOSX_BUNDLE Decimation.cxx vtkSMFReader.cxx vtkSMFWriter.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(qslim ${VTK_LIBRARIES})
else()
  target_link_libraries(qslim vtkHybrid vtkWidgets)
endif()
