EXE 		:= BlackScholes

CXX  		:= g++
CXXFLAGS 	:= -O4 -std=c++11

SOURCES 	:= BlackScholes.cpp main.cpp

INCLUDES 	:= -I/usr/local/cuda-7.0/include

LIBS 		:= -lOpenCL -lrt


.PHONY: all blackscholes clean

all : $(EXE)

$(EXE):
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(EXE) $(SOURCES) $(LIBS)

clean:
	rm -rf $(EXE)
