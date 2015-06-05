EXE 		:= VectAddSequentialNoAspects

CXX  		:= g++
CXXFLAGS 	:= -O3 -std=c++11

SOURCES 	:= VectorAddSequentialNoAspects.cpp

INCLUDES 	:=

LIBS 		:= -lrt


.PHONY: all vectadd clean

all : $(EXE)

$(EXE):
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(EXE) $(SOURCES) $(LIBS)

clean:
	rm -rf $(EXE)
