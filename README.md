# __capp__ (C++ Aspect-Oriented Parallel Programming)

__capp__ -- C++ Aspect-Oriented Parallel Programming -- uses aspects in c++ to simplify parallel programming with OpenCL. AspectC++ is used to encapsulate  most of the overhead of setting up the parallel programming context into an aspect, allowing users to focus on writing the kernels, rather than setting up context and transferring memory.

## Setup 

### Prerequisits

Currently there is only support for linux and OSX, but Windows support is intended. I have managed to
cross-compile this from Linux to Windows 8, so it should working with Windows if the pre-requists are all
installed.

#### Linux

To install AspectC++ on Ubuntu simply type ```sudo apt-get install aspectc++```. Alternatively constult [AspecC++](http://www.aspectc.org/Download.php).

To install OpenCL you need to download the SDK relevant to the device you have. For any CPU or AMD GPU, the AMD SDK will work, for NVIDIA GPU's the NVIDIA OpenCL SDK and cuda development tools are required.

##### AMD

First get the AMD SDK from [AMD](http://developer.amd.com/tools-and-sdks/opencl-zone/amd-accelerated-parallel-processing-app-sdk/). 

Extract the file and run ```sudo sh Install-AMD-APP.sh```. 

Then install the opencl headers. On Ubuntu this is done by ```sudo apt-get install opencl-headers```. Alternatively they can be downloaded from [OpenCL-Headers](https://www.khronos.org/registry/cl/). Whichever way you get the headers __make sure__ that they are version 1.1 or lower if you are going to be using an NVIDIA GPU at some point. Check the cl.hpp file (usually at ```/usr/local/CL/cl.hpp``` or ```/usr/local/include/OpenCL/cl.hpp```) and make sure that it is version 1.1.

##### NVIDIA

Download and install the latest CUDA development kit from [CUDA](https://developer.nvidia.com/cuda-downloads) and follow their instructions. Again make sure that cl.hpp is version 1.1 (__this is very important for NVIDIA__).

## Usage

Two examples are provided for using __capp__, one for vector addition and the other for option pricing using
the Black-Scholes option pricing model.

The examples can be found under ```examples/capp``` in the relevant folder. A Makefile is included to build
the files. You will need to specify the number of elements for computation as a command line argument to the
executable.

Examples are also included for sequential implementations at ```examples/sequential``` and for opencl
implementation at ```examples/opencl``` (the opencl examples are the Nvidia samples implementation).

The intention of including the additional examples is to illustrate how simple the __capp__ c++ files are for
parallel programming (in the ```/src``` directories in the relevant example), as most of the overhead is
perofrmed by the aspect before compilation.

## Notes

* Please do not change the name, move or delete the ```temp``` directory in the __capp__ example folder as it is used by the makefile to remove messy object and aspect files from the aspect compiler.

## Makefile

The Makefile must be in the project root directory (see the __capp__ examples folder). The directory names can be changed appropriately in the Makefile by editing the *_DIR variables in the Makefile.

Additionally, make sure that the environment variables in the Makefile you wish to use are appropriate for
your environment.

## Compiling

To compile any program make sure that the files are in correct directories as illustrated by the examples provided in the ```examples/capp``` directory (the provided Makefile will not work if the structure is changed but not updated in the Makefile).

Once in the example root directory, issue the

```
make
```

command and the executable will reside in the ```builds``` directory.
