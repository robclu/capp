###########################################
#										  #
#	Makefile for vector addition using    #
#	AspectC++ and OpenCL C++ 			  #
#										  #		
###########################################

EXE_NAME 	= VectorAdd

###########################################
# 			DIRECTORIES					  #
#										  #
# BUILD_DIR - Name of the directory for   #
# 			  executables				  #
# SRC_DIR	- Name of the directory where # 
# 			  all c, cpp files are		  #
# ASP_DIR   - Name of directory where 	  #
# 		      aspects are				  #
###########################################

BUILD_DIR 	= builds
SRC_DIR		= src
ASP_DIR		= aspects

###########################################
#			Executable					  #
###########################################

EXE 		= $(addprefix $(BUILD_DIR)/,$(EXE_NAME))

##########################################
# 				SOURCES					 #
##########################################

CPP_MODULES := VectorAdd.cpp main.cpp
ASP_MODULES := clContext.cc

CPP_SOURCES := $(addprefix $(SRC_DIR)/,$(CPP_MODULES))
ASP_SOURCES := $(addprefix $(ASP_DIR)/,$(ASP_MODULES))

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
