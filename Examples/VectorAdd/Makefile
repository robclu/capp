###########################################
#										  #
#	Makefile for vector addition using    #
#	AspectC++ and OpenCL C++ 			  #
#										  #		
###########################################

WIN_EXE_NAME 	= VectorAddWin
TEST_EXE_NAME 	= TestsVectorAdd

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
TMP_DIR		= temp

###########################################
#			Executable					  #
###########################################

WIN_EXE 	= $(addprefix $(BUILD_DIR)/,$(WIN_EXE_NAME))
TEST_EXE 	= $(addprefix $(BUILD_DIR)/,$(TEST_EXE_NAME))

##########################################
# 				SOURCES					 #
##########################################

COM_MODULES := VectorAdd.cpp 
HED_MODULES := VectorAdd.h
TST_MODULES := tests.cpp
ASP_MODULES := clContext.cc
TMP_MODULES := VectorAdd.hpp  \
			   $(TST_MODULES) \
			   $(ASP_MODULES:.cc=.cpp)

COM_SOURCES := $(addprefix $(SRC_DIR)/,$(COM_MODULES))
COM_SOURCES += $(addprefix $(SRC_DIR)/,$(HED_MODULES))

ASP_SOURCES := $(addprefix $(ASP_DIR)/,$(ASP_MODULES))
TMP_SOURCES := $(addprefix $(TMP_DIR)/,$(TMP_MODULES))

##########################################
#				DIRECTORIES  			 #
##########################################


##########################################
#				LIBRARIES 				 #
##########################################

LIBS 		= -lOpenCL
TEST_LIBS 	= -lgtest -lgtest_main -lpthread 

#########################################
# 		INCLUDE DIRECTORIES				#
#########################################

INCLUDES 		= -Isrc -I/usr/include/gtest \
				  -I/usr/local/cuda-7.0/include
WIN_INCLUDES 	= -I/usr/include -I/usr/local \
				  -I/usr/share

#########################################
#		LIBRARY DIRECTORIES 			#
#########################################

LIB_DIRS 	=  

#########################################
#			COMPILE ARGS 				#
#########################################

AXX 		= ag++
CXX			= g++
WXX			= x86_64-w64-mingw32-g++ 
CXXFLAGS 	= -g -std=c++11 

.PHONY: all tests

all: tests

windows: $(WEAVE) SETUP $(WIN_EXE) FINISH

tests: $(WEAVE) TEST_SETUP $(TEST_EXE) TEST_FINISH

#################################################################################
# 								  WEAVING   									#
#################################################################################
 
$(WEAVE):
	@echo Weavings the aspects . . . 	
	$(AXX)  --weave_only  $(COM_SOURCES) $(ASP_SOURCES) $(LIB_DIRS) $(LIBS)

#################################################################################
# 							   WINDOWS BUILDING								#
#################################################################################

$(WIN_EXE):
	@echo Building for windows . . .
	@echo ""
	$(WXX) $(WIN_INCLUDES) -o $(WIN_EXE) $(TMP_SOURCES) i\
		 $(LIBS)
	@echo ""
	@echo Finished cleaning the temp files!

#################################################################################
# 								TEST BUILDING									#
#################################################################################

TEST_SETUP:
	echo Moving the temp files . . . 
	echo 	
	bash -c "mv clContext.acc clContext.cpp && mv clContext.cpp temp/"
	bash -c "mv VectorAdd.acc VectorAdd.hpp && mv VectorAdd.hpp temp/"
	bash -c "cp tests/tests.cpp temp/"

$(TEST_EXE):
	echo Compiling the woven files into the test executable . . .
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TEST_EXE) $(TMP_SOURCES) $(LIB_DIRS) \
		$(LIBS)	$(TEST_LIBS) 

TEST_FINISH:
	bash -c "rm -rf tmp/*"

#################################################################################
# 								  CLEANING	     								#
#################################################################################

clean:
	rm -rf $(TEST_EXE) temp/*
