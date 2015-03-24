###########################################
#										  #
#	Makefile for vector addition using    #
#	AspectC++ and OpenCL C++ 			  #
#										  #		
###########################################

EXE_NAME 	  = VectorAdd
TEST_EXE_NAME = TestsVectorAdd

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
TST_DIR 	= tests

###########################################
#			Executable					  #
###########################################

EXE 		= $(addprefix $(BUILD_DIR)/,$(EXE_NAME))
TEST_EXE 	= $(addprefix $(BUILD_DIR)/,$(TEST_EXE_NAME))

##########################################
# 				SOURCES					 #
##########################################

COM_MODULES := VectorAdd.cpp main.cpp
TST_MODULES := tests.cpp
TGT_MODULES := main.cpp
ASP_MODULES := clContext.cc

COM_SOURCES := $(addprefix $(SRC_DIR)/,$(COM_MODULES))
TST_SOURCES := $(addprefix $(TST_DIR)/,$(TST_MODULES))
TGT_SOURCES := $(addprefix $(SRC_DIR)/,$(TGT_MODULES))
ASP_SOURCES := $(addprefix $(ASP_DIR)/,$(ASP_MODULES))

##########################################
#				DIRECTORIES 			 #
#########################################


##########################################
#				LIBRARIES 				 #
##########################################

LIBS 		= -lOpenCL
TEST_LIBS 	= -lgtest -lgtest_main \
			  -lpthread 

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

AXX 		= ag++
CXX			= g++
CXX_FLAGS 	= -O3

.PHONY: all target tests

all: target tests

target: $(EXE)

tests: $(TEST_EXE)

$(EXE):
	$(AXX) $(CXX_FLAGS) -o $(EXE) $(COM_SOURCES) $(TGT_SOURCES)  \
		$(ASP_SOURCES) $(LIBS)

$(TEST_EXE):
	$(CXX) $(CXX_FLAGS) -o $(TEST_EXE) $(TST_SOURCES) \
		$(TEST_LIBS) $(LIBS)

clean:
	rm -rf $(EXE) $(TEST_EXE)
