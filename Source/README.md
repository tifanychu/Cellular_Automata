# University of California, Berkeley
# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences 
# December 2023
# 
# Creators: Qi Tifany Chu, Sean Bray and Elizabeth Gilson

# Date Created: December, 2023
# Directory Path: 274B_final_project/Source
This directory contains the source code for our library and application.


LIST OF SUBDIRECTORIES IN THIS DIRECTORY:
None

LIST OF FILES IN THIS DIRECTORY:
- README (this file)
- cellular_automata.cpp: This file contains our C++ Object-Oriented implementation of a Cellular Automata 
                        for the various conditions neccessary for this project.
- Makefile: Creates object files and creates a library object file to archive all the object files.


# cellular_automata.cpp source file: 

Cellular_automata: base class 

CA_1D: derived class for the 1 dimension grid dimensions:(1,height_)
CA_2D: derived class for the 1 dimension grid dimensions: (width_, height_)

For the other required conditions we used integer representations to define the different conditions: 

boundary conditions: 
    - 0 : periodic
    - 1 : cut off 
    - 2 : walled 

neighborhood conditions: 
    - 0 : Von Neumann (4 squares)
    - 1 : Moore (8 sqaures)

rules: 
    - 0 : Straight conditional transition rule
    - 1 : Conditional transition rule on a neighbor
    - 2 : Majority rule

# Makefile Targets:

all :
This will compile a "libour_CA.a" file and move it to the ../Lib/ folder.