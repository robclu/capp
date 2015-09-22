EXE 		:= black_scholes_opencl

CXX  		:= g++
CXXFLAGS 	:= -O4 -std=c++11

SOURCES 	:= black_scholes_opencl.cpp

INCLUDES 	:= -I/usr/local/cuda-7.0/include

LIBS 		:= -lOpenCL -lrt


.PHONY: all blackscholes clean

all : $(EXE)

$(EXE):
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(EXE) $(SOURCES) $(LIBS)

clean:
	rm -rf $(EXE)
