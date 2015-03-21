###########################################
#										  #
#	Makefile for vector addition using    #
#	AspectC++ and OpenCL C++ 			  #
#										  #		
###########################################

EXE 		= VectorAdd

##########################################
# 				SOURCES					 #
##########################################

CPP_MODULES := VectorAdd.cpp main.cpp
ASP_MODULES := clContext.cc
CPP_SOURCES := $(addprefix src/,$(CPP_MODULES))
ASP_SOURCES := $(addprefix aspects/,$(ASP_MODULES))

##########################################
#				DIRECTORIES 			 #
#########################################


##########################################
#				LIBRARIES 				 #
##########################################

LIBS 		= -lOpenCL

#########################################
# 		INCLUDE DIRECTORIES				#
#########################################

INCLUDES 	= src

#########################################
#		LIBRARY DIRECTORIES 			#
#########################################

LIB_DIRS 	= 

#########################################
#			COMPILE ARGS 				#
#########################################

CXX 		= ag++
CXX_FLAGS 	= -O3

all: $(EXE)

$(EXE):
	$(CXX) $(CXX_FLAGS) -o $(EXE) $(CPP_SOURCES)  \
		$(ASP_SOURCES) $(LIBS)

clean:
	rm -rf $(EXE)
