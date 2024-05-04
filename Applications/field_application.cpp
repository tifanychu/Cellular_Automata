// University of California, Berkeley
// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences 
// December 2023
 
// Creators: Qi Tifany Chu, Sean Bray and Elizabeth Gilson

// This file contains our C+ of our cellular_automata application field to simulate pest spread. 
// We initialized an instance of the CA_2D (two d version of the cellular automata)
// The resulting grids will be saved as a txt file in the Plots/Data subfolder. 



#include <iostream>
#include <cstdlib>
#include <random>
#include <fstream>

#include "CA.h" 


int main() {
   
    /*
    boundary: 
    - 0 : periodic
    - 1 : cut off 
    - 2 : walled 

    neighborhood: 
    - 0 : Von Neumann (4 squares)
    - 1 : Moore (8 sqaures)

    rules: 
    - 0 : Straight conditional transition rule
    - 1 : Conditional transition rule on a neighbor
    - 2 : Majority rule

    Cellular_Automata(int length, int width, int boundary, int neighborhood)
    */

   // First trial
    // make name of output file we are printing to
    std::string file_1 = "../Plots/Data/field_1_data.txt";
    std::ofstream file_1_nums("../Plots/Data/field_1_nums.txt");


   // Von Neumann + step rule 1
    CA_2D field_1(20, 20, 1, 0);
    
    // initialize to have 90% crops
    field_1.initialize(0.95);
    field_1.print();
    field_1.write_output_file(file_1);

   
    // loop through 20 days and see what happens
    for(int i =0; i <40; i++){
        // first let pests spread
        field_1.step(1);
        // then a proportion of them die
        field_1.step(0, 0.5);
        // print out
        //field_1.print();
        // print output to our file
        field_1.write_output_file(file_1);
        std::vector<int> count = field_1.count_states();
        for (const auto& num : count) {
            file_1_nums << num << std::endl; // Write each number followed by a newline
        }
        // file_1_nums << count << std::endl;
    }
    file_1_nums.close();

    

    // intialize field 2 to have 75% crops
    std::string file_2 = "../Plots/Data/field_2_data.txt";
    std::ofstream file_2_nums("../Plots/Data/field_2_nums.txt");

    CA_2D field_2(20, 20, 1, 0);
    
    field_2.initialize(0.9);
    field_2.print();
    field_2.write_output_file(file_2);

   
    // loop through 20 days and see what happens
    for(int i =0; i <40; i++){
        // first let pests spread
        field_2.step(1);
        // then a proportion of them die
        field_2.step(0, 0.5);
        // print out
        //field_2.print();
        // print output to our file
        field_2.write_output_file(file_2);
        std::vector<int> count = field_2.count_states();
        for (const auto& num : count) {
            file_2_nums << num << std::endl; // Write each number followed by a newline
        }
        //file_2_nums << count << std::endl;
    }
    file_2_nums.close();

    


    // intialize field 3 to have 60% crops
    std::string file_3 = "../Plots/Data/field_3_data.txt";
    std::ofstream file_3_nums("../Plots/Data/field_3_nums.txt");

    CA_2D field_3(20, 20, 1, 0);
    
  
    field_3.initialize(0.85);
    field_3.print();
    field_3.write_output_file(file_3);

   
    // loop through 20 days and see what happens
    for(int i =0; i <40; i++){
        // first let pests spread
        field_3.step(1);
        // then a proportion of them die
        field_3.step(0, 0.5);
        // print out
        //field_3.print();
        // print output to our file
        field_3.write_output_file(file_3);
        std::vector<int> count = field_3.count_states();
        //file_3_nums << count << std::endl;
        for (const auto& num : count) {
            file_3_nums << num << std::endl; // Write each number followed by a newline
        }
    }
    file_3_nums.close();


   
    return 0;
}