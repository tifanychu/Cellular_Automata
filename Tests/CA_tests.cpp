// University of California, Berkeley
// Chem 274B: Software Engineering Fundamentals for
//          Molecular Sciences 
// December 2023
// 
// Creators: Qi Tifany Chu, Sean Bray and Elizabeth Gilson
// 
// This C++ program is a verification test of the Cellular Automata methods in cellular_automata.cpp
// It test the two derived classes CA_1D and CA_2D. 

#include <iostream>
#include <cstdlib>
#include <random>
#include <exception>

#include "CA.h" 

void test_1D_automata(){
    // Create a 1D cellular automaton with length 7, periodic boundaries, von Neumann neighborhood, and rule 1
    CA_1D one(7, 0);
    one.print();
    
    // Initialize the automaton with a 30% density of live cells
    one.initialize(0.3);

    // Print the initial state of the automaton
    one.print();


    // set state
    std::vector<int> test_state_1D = {2, 1, 1, 1, 2, 1, 1};
    one.set_grid(test_state_1D);
    one.print();


    // step with rule 1 --> anything touching a 2 should turn to 2
    one.step(1);
    one.print();
    std::vector<int> expected_next_state = {2, 2, 1, 2, 2, 2, 2};
    if(one.get_grid() != expected_next_state){
        std::cout << "Test case 1D array step with rule 1: FAILED" << "\n" <<std::endl;
    } else{
        std::cout << "Test case 1D array step with rule 1: PASSED" << "\n" << std::endl;
    }
    // step with rule 0 --> everything that is 2 should turn to 3
    one.step(0);
    one.print();

    expected_next_state = {3, 3, 1, 3, 3, 3, 3};
    if(one.get_grid() != expected_next_state){
        std::cout << "Test case 1D array step with rule 0: FAILED" << "\n" << std::endl;
    } else{
        std::cout << "Test case 1D array step with rule 0: PASSED" << "\n" << std::endl;
    }

}

void test_2D_automata()
{
    // Testing 2D CA
    // creating the object
    // length = 3, width = 3, boundary = 1 (normal), neighborhood = Von Neuman (0), int rule = 0
    CA_2D two(3, 3, 1, 0);
    two.print();

    // initializing
    two.initialize(0.3);
    two.print();

    // testing step methods

    std::vector<std::vector<int>> test_state_2D = {
        {1, 2, 1},
        {1, 1, 2},
        {2, 1, 1}
    };
    two.set_grid(test_state_2D);
    two.print();
   
    two.step(2); // test majority rule step

    std::vector<std::vector<int>> expected_state_2D = {
        {2, 2, 2},
        {1, 2, 2},
        {2, 1, 2}
    };

    two.print();
    if (two.get_grid() != expected_state_2D){
        std::cout << "Test case 2D array step with rule 2: FAILED" << std::endl;
    } else{
        std::cout << "Test case 2D array step with rule 2: PASSED" << std::endl;
    }


    // test step type 0
    two.step(0);
    // all 2s should be updated to 3s
    std::vector<std::vector<int>> expected_state_2D_2 = {
        {3, 3, 3},
        {1, 3, 3},
        {3, 1, 3}
    };

    if (two.get_grid() != expected_state_2D_2){
        std::cout << "Test case 2D array step with rule 0: FAILED" << std::endl;
    } else {
        std::cout << "Test case 2D array step with rule 0: PASSED" << std::endl;
    }

}

void test_invalid_automata()
{
    try{
        CA_1D one(1, 0);
        // Alert users if invalid input not caught
        std::cout << "No exception thrown for invalid input." << std::endl;
    }
    catch (const std::exception & e) {
        std::cout << "Successfully caught error for invalid 1d automata creation: " 
        << e.what() << std::endl;
    }

    try{
        CA_2D two(1, 1, 0, 0);
        // Alert users if invalid input not caught
        std::cout << "No exception thrown for invalid input to 2D automata." << std::endl;
    }
    catch (const std::exception & e) {
        std::cout << "Successfully caught error for invalid 2d automata creation: " 
        << e.what() << std::endl;
    }

}

void test_invalid_set_grid()
{
    std::cout << std::endl << "1D automata: " << std::endl; 
    CA_1D walled_1d_grid(5, 2);
    walled_1d_grid.initialize(0.5);
    try {
        walled_1d_grid.set_grid({0, 2, 2, 2, 2, 2, 2, 2, 0});
        std::cout << "No exception thrown for set_grid with wrong length" 
        << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Successfully caught invalid set_grid size."
        << std::endl; 
    }
}

void test_walled_boundary()
{
    bool passed = true;
    CA_1D walled_1d_grid(5, 2);
    walled_1d_grid.initialize(0.5);
    std::cout << std::endl << "1D walled automata: " << std::endl; 
    walled_1d_grid.print();
    try {
        walled_1d_grid.set_grid({2, 2, 2, 2, 2});
        passed = false;
        std::cout << "No exception thrown for overwriting walled boundaries" 
        << std::endl << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Successfully caught invalid walled boundary overwrite."
        << std::endl; 
    }
    walled_1d_grid.set_grid({0, 1, 2, 0, 0});
    walled_1d_grid.step(1);
    std::vector<int> expected_new_grid = {0, 2, 2, 0, 0};
    if (walled_1d_grid.get_grid() != expected_new_grid)
    {
        std::cout << "Walled 1d grid update failed vacinity rule update" << std::endl;
        passed = false;
    }
    // After another neighbor step there is nothing left to infect
    // expected_new_grid doesn't change
    walled_1d_grid.step(1);
    if (walled_1d_grid.get_grid() != expected_new_grid)
    {
        std::cout << "Walled 1d grid update failed second vacinity rule update" << std::endl;
        passed = false;
    }
    walled_1d_grid.step(0);
    expected_new_grid = {0, 3, 3, 0, 0};
    if (walled_1d_grid.get_grid() != expected_new_grid)
    {
        std::cout << "Walled 1d grid update failed time rule update" << std::endl;
        passed = false;
    }
    if (passed == true)
    {
        std::cout << "Walled 1d automata updates passed" << std::endl;
    }
}

void test_cutoff_boundary()
{
    CA_1D one(3, 1);
    one.set_grid({1, 1, 1});
    one.cutoff_boundary();
    std::vector<int> output_grid = one.get_grid();
    if (output_grid[0] != 0 || output_grid[2] != 0)
    {
        std::cout << "Setting cutoff boundary failed." << std::endl;
    }
    else
    {
        std::cout << "Successfully set cutoff boundary" << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    // Test 1D CA
    test_1D_automata();
    
    // Test 2D CA
    test_2D_automata();

    // Test that invalid input for automata creation is caught
    test_invalid_automata();

    // Test that trying to set the grid to the wrong length raises error
    test_invalid_set_grid();

    // Test that an automata generated with walled boundaries
    test_walled_boundary();

    // Test that cutoff_boundary correctly sets boundary values to 0
    test_cutoff_boundary();

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


    int length = 10; 
    int width = 10; 
    int boundary = 1; // no boundaries 
    int neighborhood = 1;// Moore 
    int rule = 1; 

    CA_2D field (length, width ,boundary, neighborhood); 
    field.initialize(0.9);

    std::cout << "Test two updates with the neighbors rule, moore neighborhoods, "
    << "and no boundaries:" << std::endl;
    for(int i = 0; i < 2; i++){ 
        std::cout<< "time: "<< field.get_time()<< "\n"; 
        field.print(); 
        field.step(rule); 
        }
}
