EXE 		:= vector_addition_sequential

CXX  		:= g++
CXXFLAGS 	:= -std=c++11

SOURCES 	:= vector_addition_sequential.cpp

INCLUDES 	:=

LIBS 		:= -lrt


.PHONY: all vectadd clean

all : $(EXE)

$(EXE):
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(EXE) $(SOURCES) $(LIBS)

clean:
	rm -rf $(EXE)
