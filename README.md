# mesh-simplification
An alternative to qslim algorithm using vtk

## Input and Output Remarks
The current version implements a custom reader and writer of [smf file format](http://people.sc.fsu.edu/~jburkardt/data/smf/smf.txt).  
Other format such as OFF can be easily implemented.

## Dependency
### OpenGL
* Ubuntu
```bash
$ sudo apt-get install freeglut3-dev
```
* CentOS
```bash
$ sudo yum install freeglut-devel
```

### The Visualization Toolkit(VTK)
* [Introduction](https://en.wikipedia.org/wiki/VTK)
* [Website](http://www.vtk.org/)
* [Download](http://www.vtk.org/download/)
* [Installation Guide](http://www.vtk.org/Wiki/VTK/Configure_and_Build)


## Build
* if you have all dependencies already installed:
```bash
$ mkdir build
$ cd build
$ cmake ../src
$ make
```
* if you have not installed any dependencies:
```bash
$ ./compile_<Your OS>.sh
```
After finished, go into build/ folder.

## Run
This is a dummy running command temporarily for pipeline testing.  
```bash
$ ./simplification -n <target no. of polygons> -o <output filename> <input filename>
```

## Wiki
If you want to learn more, I also created a simple wiki page to briefly introduce vtk and the algorithms. Check out [here](https://github.com/Allen-Shao/Mesh-Simplification/wiki/Mesh-Decimation-Using-VTK).


