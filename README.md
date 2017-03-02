# mesh-simplification
An alternative to qslim algorithm using vtk

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
$ cmake ..
$ make
```
* if you have not installed any dependencies:
```bash
$ ./compile.sh
```

## Run
This is a dummy running command temporarily for pipeline testing.  
```bash
$ ./simplification -n <target no. of polygons> -o <output filename> <input filename>
```


