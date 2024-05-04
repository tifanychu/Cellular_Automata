# University of California, Berkeley
# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences 
# December 2023
# 
# Creators: Qi Tifany Chu, Sean Bray and Elizabeth Gilson

# Directory Path: 274B_final_project/Tests 

# This makefile creates object files that are executable 
# They test the functionalities in 274B_Final_Project/Source
# After creating the executable files they are moved to 
# the ../Bin subdirectory


# GNU C++ Compiler
CPP         = g++ -std=c++17     

# other compiler flags -g debug, -c create a library object
CPPFLAGS    = -O3 -o

# The directory where the include files needed to create the library objects are

INC_DIR = ../Include

# The directory where all object files are going to be moved after creation
LIB_DIR = ../Lib
BIN_DIR = ../Bin

# The next line contains the list of object files created by this Makefile.
EXECUTABLES = test_CA

test_CA: $(INC_DIR)/CA.h 
	$(CPP) $(CPPFLAGS) $(EXECUTABLES) CA_tests.cpp \
	-I$(INC_DIR) -L$(LIB_DIR) -lour_CA 
	mv $(EXECUTABLES) $(BIN_DIR)

all: $(EXECUTABLES)

cleanall:
	cd $(BIN_DIR); rm $(EXECUTABLES)
 