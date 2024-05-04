# University of California, Berkeley
# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences 
# December 2023
# 
# Creators: Qi Tifany Chu, Sean Bray and Elizabeth Gilson

# Date Created: December, 2023
# Directory Path: 274B_final_project/Application


This directory contains our Cellular Automata application where we are modeling pest spread among crops in a field in the field_application.cpp 

LIST OF SUBDIRECTORIES IN THIS DIRECTORY:
None


List of files in this directory: 
- field_applications.cpp : C++ implementation of a field to simulate pest spread with various conditions. It will then print the field grids from each time step into a txt file. 
- Makefile: uses our cellular automata general purpose library to run field_application.cpp. The txt files representing the field_grid will be saved in the Plots/Data subfolder. 
- README (this file)


## field_application.cpp 

Conditions used in simulation (see readme in source subdirectory for more information about integer representations.)
- boundary : 1 cutofff boundaries 
- neighborhood: 0 Von Neumann 
- grid size: length = 20, width =20 

