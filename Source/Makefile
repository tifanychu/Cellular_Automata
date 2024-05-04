# University of California, Berkeley
# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences 
# December 2023
# 
# Creators: Qi Tifany Chu, Sean Bray and Elizabeth Gilson

# Directory Path: 274B_final_project/Source 

# This makefile creates objects and a library for our cellular automata implementation



INC_DIR = ../Include


# compile the cellular automata source code in cellular_automata.cpp
# save object file in the include directory. 

cellular_automata.o : $(INC_DIR)/CA.h
	g++ -g -O3 -std=c++17 -c cellular_automata.cpp -I $(INC_DIR)

# Create a static library 
libour_CA.a: cellular_automata.o
	ar ru libour_CA.a cellular_automata.o
	mv libour_CA.a ../Lib 
	rm cellular_automata.o

all : libour_CA.a