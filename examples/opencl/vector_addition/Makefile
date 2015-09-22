EXE 		:= vector_addition_opencl

CXX  		:= g++
CXXFLAGS 	:= -O4 -std=c++11

SOURCES 	:= vector_addition_opencl.cpp

INCLUDES 	:= -I/usr/local/cuda-7.0/include

LIBS 		:= -lOpenCL -lrt


.PHONY: all vectadd clean

all : $(EXE)

$(EXE):
	$(CXX) -g $(CXXFLAGS) $(INCLUDES) -o $(EXE) $(SOURCES) $(LIBS)

clean:
	rm -rf $(EXE)
