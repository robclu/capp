###########################################
#										  #
#	Makefile for vector addition using    #
#	AspectC++ and OpenCL C++ 			  #
#										  #		
###########################################

EXE_NAME 		= VectorAdd
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

EXE 		= $(addprefix $(BUILD_DIR)/,$(EXE_NAME))
WIN_EXE 	= $(addprefix $(BUILD_DIR)/,$(WIN_EXE_NAME))
TEST_EXE 	= $(addprefix $(BUILD_DIR)/,$(TEST_EXE_NAME))

##########################################
# 				SOURCES					 #
##########################################

COM_MODULES := VectorAdd.cpp 
TST_MODULES := tests.cpp
TGT_MODULES := main.cpp
ASP_MODULES := clContext.cc
TMP_MODULES := $(COM_MODULES) \
			   $(TGT_MODULES) \
			   $(ASP_MODULES:.cc=.cpp)
TST_MODULES += $(COM_MODULES) \
			   $(ASP_MODULES:.cc=.cpp)

COM_SOURCES := $(addprefix $(SRC_DIR)/,$(COM_MODULES))
TST_SOURCES := $(addprefix $(TST_DIR)/,$(TST_MODULES))
TGT_SOURCES := $(addprefix $(SRC_DIR)/,$(TGT_MODULES))
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

INCLUDES 		= -Isrc -I/usr/include/gtest
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
CXX_FLAGS 	= 

.PHONY: all target tests

all: target

target: $(WEAVE) SETUP $(EXE) FINISH

windows: $(WEAVE) SETUP $(WIN_EXE) FINISH

tests: $(WEAVE) TEST_SETUP $(TEST_EXE) TEST_FINISH

#################################################################################
# 								  WEAVING   									#
#################################################################################
 
$(WEAVE):
	@echo Weavings the aspects . . . 
	@echo ""	
	$(AXX) $(CXX_FLAGS) --weave_only  $(COM_SOURCES) 			\
		$(TGT_SOURCES) $(ASP_SOURCES) $(LIBS)
	@echo ""
	@echo Finished weaving the aspects!

#################################################################################
# 								MAIN EXE BUILDING								#
#################################################################################

SETUP:
	@echo Moving temp files ...
	@echo ""
	@bash -c "mv main.acc main.cpp && mv main.cpp temp/"	
	@bash -c "mv clContext.acc clContext.cpp && mv clContext.cpp temp/"
	@bash -c "mv VectorAdd.acc VectorAdd.cpp && mv VectorAdd.cpp temp/"
	@echo ""
	@echo Finished moving the temp files!

$(EXE): 
	@echo Building the executable . . .
	@echo ""
	$(CXX) -o $(EXE) $(TMP_SOURCES) $(LIBS)
	@echo ""
	@echo Finished building the executable!

FINISH:
	@echo Cleaning the temporary files ...
	@echo ""
	@bash -c "rm -rf tmp/*"
	@echo""
	@echo Finished cleaning the temporary files!

#################################################################################
# 							   WINDOWS BUILDING								#
#################################################################################

$(WIN_EXE):
	@echo Building for windows . . .
	@echo ""
	$(WXX) $(WIN_INCLUDES) -o $(WIN_EXE) $(TMP_SOURCES) $(LIBS)
	@echo ""
	@echo Finished cleaning the temp files!

#################################################################################
# 								TEST BUILDING									#
#################################################################################

TEST_SETUP:
	@echo Moving the temp files . . . 
	@echo 	
	@bash -c "mv clContext.acc clContext.cpp && mv clContext.cpp tests/"
	@bash -c "mv VectorAdd.acc VectorAdd.cpp && mv VectorAdd.cpp tests/"
	@bash -c "cp src/VectorAdd.h tests/VectorAdd.h"
	@echo Finished moving the temp files!

$(TEST_EXE):
	@echo Compiling the woven files into the test executable . . .
	@echo
	$(CXX) -o $(TEST_EXE) $(TST_SOURCES) $(LIBS)	\
		$(TEST_LIBS) $(INCLUDES)
	@echo
	@echo Finished compiling woven files!

TEST_FINISH:
	@bash -c "rm -rf tests/clContext.cpp tests/VectorAdd.* main.acc"

#################################################################################
# 								  CLEANING	     								#
#################################################################################

clean:
	@echo Cleaning the project . . .
	rm -rf $(EXE) $(TEST_EXE)
	@echo Finished cleaning the project.
