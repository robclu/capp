###########################################
#										  #
#	Makefile for vector addition using    #
#	AspectC++ and OpenCL C++ 			  #
#										  #		
###########################################

WIN_EXE_NAME 	= WindowsTests.exe
TEST_EXE_NAME 	= LinuxTests

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

COM_MODULES := black_scholes.cpp 
HED_MODULES := black_scholes.h
WIN_MODULES := wintests.cpp
TST_MODULES := tests.cpp
ASP_MODULES := clContext.cc
TMP_MODULES := black_scholes.h  \
			   $(TST_MODULES) \
			   $(ASP_MODULES:.cc=.cpp)
WIN_TMP_MODULES := black_scholes.h \
				$(WIN_MODULES) 	 \
				$(ASP_MODULES:.cc=.cpp)

COM_SOURCES := $(addprefix $(SRC_DIR)/,$(COM_MODULES))
COM_SOURCES += $(addprefix $(SRC_DIR)/,$(HED_MODULES))

ASP_SOURCES := $(addprefix $(ASP_DIR)/,$(ASP_MODULES))
TMP_SOURCES := $(addprefix $(TMP_DIR)/,$(TMP_MODULES))
WIN_TMP_SOURCES := $(addprefix $(TMP_DIR)/,$(WIN_TMP_MODULES))

##########################################
#				DIRECTORIES  			 #
##########################################


##########################################
#				LIBRARIES 				 #
##########################################

LIBS 		= -lOpenCL -lrt
TEST_LIBS 	= -lgtest -lgtest_main -lpthread 
WIN_LIBS 	= -static-libgcc -static-libstdc++ \
			  -static -lwinpthread

#########################################
# 		INCLUDE DIRECTORIES				#
#########################################

INCLUDES 		= -Isrc -I/usr/include/gtest \
				  -I/usr/local/cuda-7.0/include
WIN_INCLUDES 	= 

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
CXXFLAGS 	= -O2 -std=c++11 

.PHONY: all tests windows

all: tests 

windows: WIN_WEAVE $(WIN_EXE) FINISH

tests: $(WEAVE) TEST_SETUP $(TEST_EXE) TEST_FINISH

#################################################################################
# 								  WEAVING   									#
#################################################################################
 
$(WEAVE):
	@echo Weavings the aspects . . . 	
	$(AXX) --weave_only  $(COM_SOURCES) $(ASP_SOURCES) $(LIB_DIRS) $(LIBS)

WIN_WEAVE:
	@echo Weavings the aspects . . . 	
	sudo $(AXX)  --weave_only --c_compiler $(WXX)  $(COM_SOURCES) $(ASP_SOURCES)  

#################################################################################
# 							   WINDOWS BUILDING								#
#################################################################################

$(WIN_EXE):
	echo Moving the temp files . . . 
	echo 	
	bash -c "mv clContext.acc clContext.cpp && mv clContext.cpp temp/"
	bash -c "mv VectorAdd.acc VectorAdd.hpp && mv VectorAdd.hpp temp/"
	bash -c "cp src/wintests.cpp temp/"
	@echo Building for windows . . .
	@echo ""
	sudo $(WXX) $(CXXFLAGS) $(WIN_INCLUDES) -o $(WIN_EXE) $(WIN_TMP_SOURCES) \
		 $(LIBS) $(WIN_LIBS)
	@echo ""
	@echo Finished cleaning the temp files!

FINISH:
	rm -rf temp/*

#################################################################################
# 								TEST BUILDING									#
#################################################################################

TEST_SETUP:
	echo Moving the temp files . . . 
	echo 	
	bash -c "mv clContext.acc clContext.cpp && mv clContext.cpp temp/"
	bash -c "mv black_scholes.acc black_scholes.h && mv black_scholes.h temp/"
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
	rm -rf $(TEST_EXE) $(WIN_EXE) temp/*
