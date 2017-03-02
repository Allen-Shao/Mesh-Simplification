#!/bin/sh

CUR_PATH=$(pwd)

#Dependency
#openGL
echo Installing OpenGL
sudo yum install -y freeglut-devel

#vtk-7.1
echo Downloading VTK source code
wget http://www.vtk.org/files/release/7.1/VTK-7.1.0.tar.gz

echo Extracting VTK files
tar zxf VTK-7.1.0.tar.gz

echo Building VTK
cd VTK-7.1.0
mkdir build
cd build
cmake ..
make -j8
sudo make install

#Clean up
echo Cleaning up
cd $CUR_PATH
rm -rf VTK-7.1.0
rm VTK-7.1.0.tar.gz

#build mesh decimation
echo Building mesh decimation
cd ..
mkdir build
cd build
cmake ../src
make

