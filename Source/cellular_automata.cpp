// University of California, Berkeley
// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences 
// December 2023
 
// Creators: Qi Tifany Chu, Sean Bray and Elizabeth Gilson

// This file contains our C++ Object-Oriented implementation of cellular_automata 
// for the various conditions neccessary for this project.

// The API "CA.h" contains the C++ Class definitions for our parent class Cellular Automata 
// and the two derived children classes CA_1D and CA_2D for each grid dimension. 


#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <vector> 
#include <algorithm>
#include <exception>

#include "CA.h"

void CA_1D::print() const {
    for (int x = 0; x < length_; x++) {
        std::cout << grid_[x] << " ";
    }
    std::cout << "\n";
    std::cout << "\n";
}

void CA_2D::print() const{
    for(int y = 0; y < width_; y++){
        for (int x = 0; x < length_; x++){
            std::cout<< grid_[y][x] << " "; 
        }
        std::cout<<"\n";
    } 
    std::cout<<"\n";
}

int Cellular_Automata::get_time() const { 
    return time_; 
}


std::vector<int> CA_1D::get_grid() const {
    return grid_;
}

std::vector<std::vector<int>> CA_2D::get_grid() const {
    return grid_;
}

void CA_1D::set_grid(const std::vector<int>& new_grid){
    if (new_grid.size() != length_)
    {
        throw std::invalid_argument("Can't call set_grid with argument of wrong length");
    }
    if (boundary_ == 2) // Then walled grids should always start and end with zero
    {
        if (new_grid[0] != 0 || new_grid[length_ - 1] != 0)
        {
            throw std::invalid_argument("Can't remove walls for walled automata");
        }
    }

    grid_ = new_grid;
}

void CA_2D::set_grid(const std::vector<std::vector<int>>& new_grid){
    if (new_grid.size() != width_)
    {
        throw std::invalid_argument("Can't call CA_2D::set_grid with argument of wrong width");
    }
    if (new_grid[0].size() != length_)
    {
        throw std::invalid_argument("Can't call CA_2D::set_grid with argument of wrong length");
    }
    cutoff_boundary();

    grid_ = new_grid;
}

void CA_1D::initialize(const double& percent){
    srand(time(nullptr));

    // first intialize everything to 1 (as 1 = healthy)
    for(int y = 0; y < width_; y++){
        for (int x = 0; x < length_; x++){
            grid_[x] = 1; // Initialize everything to 1
        }
    }
    // then randomly change things to 2 (infected)
    for (int x = 0; x < length_; x++){
        double random_number = (double)rand() / RAND_MAX;
        if (random_number<= percent ){
            grid_[x] = 2; 
        }
    }

    // For now it's easiest for me to skip this step
    // We can certainly re-introduce this logic
    // once the simple implementation is working
    // int x_2 = length_/2; 
    // int y_2 = width_/2; 
    // grid_[y_2][x_2] = 2;

    if (boundary_ == 2) {
        cutoff_boundary(); 
    }
}

void CA_2D::initialize(const double& percent){
    srand(time(nullptr));
    // // first intialize everything to 1 (as 1 = healthy)
    // for(int y = 0; y < width_; y++){
    //     for (int x = 0; x < length_; x++){
    //         grid_[y][x] = 1; // Initialize everything to 1
    //     }
    // }
    // then randomly change things to 2 (infected)
    for(int y = 0; y < width_; y++){
        for (int x = 0; x < length_; x++){
            double random_number = (double)rand() / RAND_MAX;
            if (random_number<= percent ){
                grid_[y][x] = 1; 

            }

        }

    // For now it's easiest for me to skip this step
    // We can certainly re-introduce this logic
    // once the simple implementation is working
    // add infected square to middle of CA model
    int x_2 = length_/2; 
    int y_2 = width_/2; 
    grid_[y_2][x_2] = 2;

    }
    if (boundary_ ==2){
        cutoff_boundary(); 
    }
}

void CA_1D::cutoff_boundary()
{
    grid_[0] = 0; 
    grid_[length_ - 1] = 0; 
}



void CA_2D::cutoff_boundary()
{
    for(int y = 0; y < width_; y++)
    {
        for (int x = 0; x < length_; x++)
        {
            if (x == 0 || x == length_-1 || y == 0 || y == width_-1)
            {
                grid_[y][x] = 0; 
            }
        }
    }
}

std::vector<int> CA_1D::get_neighbors(const int& x) const {
    // We'll return the integer indexes of the neighbors of x
    std::vector<int> neighbors;
    
    if (x == 0)
    {
        neighbors.push_back(1);
        // For periodic boundaries, if x == 0, the last element is also a neighbor
        if (boundary_ == 0)
        {
            neighbors.push_back(length_ - 1);
        }
    }
    else if (x == length_ - 1)
    {
        neighbors.push_back(length_ - 2);
        // For periodic boundaries, if x == length - 1, the first element is also a neighbor
        if (boundary_ == 0)
        {
            neighbors.push_back(0);
        }
    }
    else
    {
        neighbors.push_back(x - 1);
        neighbors.push_back(x + 1);
    }

    return neighbors; 
}

std::vector<std::pair<int, int>> CA_2D::get_neighbors(int x, int y){
    // My though is that regardless of neighborhood, 
    std::vector<std::pair<int, int>> neighbors;

    // regardless of boundaries, this is the general coords 
    int x_L = x-1; 
    int x_R = x+1; 
    int y_U = y-1; 
    int y_D = y+1; 
    
    // periodic 
    if (boundary_==0){
        // Left/Right boundaries 
        if (x==0){
            x_L = length_ - 1;
        } else if (x== length_-1) {
            x_R = 0; 
        }
        
        // Top boundary 
        if (y==0) {
            y_U = width_-1;  // last index 
        } else if (y== width_-1) {  
            y_D = 0;
        }
    }
    // Cutoff/no boundaries
    else if (boundary_ ==1){
        if (x==0) x_L =-1; 
        if (x==length_-1) x_R =-1; 
        if (y==0) y_U = -1; 
        if (y== width_-1) y_D =-1; 
    }
    // walled boudnaries 
    else if (boundary_ == 2){
        // if its any edge then forget about it 
        if ((x==0)|| (x==length_-1)|| (y==0)||(y==width_-1)){
            x_L = -1; 
            x_R = -1; 
            y_U = -1;  
            y_D = -1;
        }
        // if its in the inner edge 
        if (x==1) x_L =-1; 
        if (x==length_-2) x_R =-1; 
        if (y==1) y_U = -1; 
        if (y== width_-2) y_D =-1; 
    }

    
    neighbors.push_back({x_L, y}); // Left
    neighbors.push_back({x_R, y}); // right 
    neighbors.push_back({x, y_U}); // up
    neighbors.push_back({x, y_D}); //down
    neighbors.push_back({x_L, y_U}); // up diagonal left
    neighbors.push_back({x_R, y_U}); // up  diagonal right
    neighbors.push_back({x_L, y_D}); // down diagonal left
    neighbors.push_back({x_R, y_D}); // down diagonal right
    
    return neighbors;
}

std::vector<std::pair<int, int>> CA_2D::neighbor_check(int x, int y, int neighborhood){

    std::vector<std::pair<int, int>> neighbors;

    // Von Neuman Neigborhood (only get up/down/left/right)
    if(neighborhood == 0){
        std::vector<std::pair<int, int>> allNeighbors = get_neighbors(x, y);

        for (const auto& coord : allNeighbors) {
            // Only consider up/down/left/right neighbors
            if ((coord.first != -1 && coord.second != -1) && 
                ((coord.first == x && abs(coord.second - y) == 1) || 
                 (coord.second == y && abs(coord.first - x) == 1))) {
                neighbors.push_back(coord);
            }
        }
    }
    // get all surrounding neighbors
    else if (neighborhood == 1) {
        neighbors = get_neighbors(x, y);
        // Filter out coordinates with -1
        neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(),
                                       [](const std::pair<int, int>& coord) {
                                           return coord.first == -1 || coord.second == -1;
                                       }),
                        neighbors.end());
    }

    return neighbors;

}

/*
We have added an optional parameter update_probability. If the step function is called 
with rule 0, and an update probability other than 1, then that percent
of automata will be randomly updated to the next state.
*/
void CA_1D::apply_time_rule(double update_probability)
{
    if (update_probability == 1){
        for (int x = 0; x < length_; x++){
            if (grid_[x] == 2) {
                next_grid_[x] = 3;
            }
        }
    } 
    else {
        srand(time(nullptr));
        // get current state
        std::vector<int> state_counts = count_states();
        // Access the count of infected
        int num_infected = state_counts[2];

        int num_to_change = static_cast<int>(update_probability * num_infected);
        int count = 0;
        while (count < num_to_change) {
            int x = rand() % length_;

            if (grid_[x] == 2) {
                next_grid_[x] = 3;
                count++;
            }
        }
    }
}

void CA_1D::apply_vicinity_rule()
{
    for (int x = 0; x < length_; x++){
        std::vector<int> neighbors_to_check; 
        neighbors_to_check = get_neighbors(x); 
        for (const auto& coord : neighbors_to_check){
            if (grid_[coord] == 2){
                next_grid_[x] = 2; 
            }
        }
    }
}

void CA_1D::apply_majority_rule()
{
    for (int x = 0; x < length_; x++){
        std::vector<int> neighbors_to_check; 
        neighbors_to_check = get_neighbors(x); 
        int num_neighbors = 0;
        double avg=0; 
        for (const auto& coord : neighbors_to_check){
            if (grid_[coord] == 2){
                avg += 1;
            }
            num_neighbors += 1;
        }
        avg = avg/num_neighbors;

        if (avg >= 0.5){
            next_grid_[x] = 2; 
        }
    }
}

/*
The step function moves the CA model foward one time step. It has 
several different rules that can be used to move forward. The first
is rule 0, which can either update all automata of a certain state 
(in our case state 2) to the next state (state 3). We have also added
an optional parameter update_probability. If the step function is called 
with rule 0, and an update probability other than 1, then that percent
of automata will be randomly updated to the next state.
*/
void CA_1D::step(int rule, double update_probability){
    if (update_probability < 0 || update_probability > 1)
    {
        throw std::invalid_argument("Update probability must be between 0 and 1");
    }

    next_grid_ = grid_;
    time_ += 1;
    // Time Rule
    if (rule == 0){ 
        apply_time_rule(update_probability);
    }

    // in vacinity rule 
    if (rule == 1){
        apply_vicinity_rule();
    }

    // majority rule 
    if (rule ==2){
        apply_majority_rule();
    }

    for (int x = 0; x < length_; x++){ 
        // Zero represents our "empty cell" state
        if (grid_[x]==0){ 
            next_grid_[x]=0; 
        }
    }
    grid_ = next_grid_;
}

// A function to return the next grid when rule 0 (time rule) is applied
void CA_2D::apply_time_rule(double update_probability)
{
    if (update_probability < 0 || update_probability > 1)
    {
        throw std::invalid_argument("Update probability must be between 0 and 1");
    }
    if (update_probability == 1){
        for(int y = 0; y < width_; y++){
            for (int x = 0; x < length_; x++){
                if (grid_[y][x] == 2) {
                            
                    next_grid_[y][x] = 3;

                }
            }
        }
    } else {
        srand(time(nullptr));
        // get current state
        std::vector<int> state_counts = count_states();
        // Access the count of infected
        int num_infected = state_counts[2];

        
        int num_to_change = static_cast<int>(update_probability * num_infected);
        int count = 0;
        //std::cout << "num to change" << num_to_change << std::endl;
        while (count < num_to_change) {
            int x = rand() % length_;
            int y = rand() % width_;

            if (grid_[y][x] == 2) {
                //std::cout << "current:" <<std::endl;
                //print();
                //std::cout << "changing " <<x << ", " << y << std::endl;
                next_grid_[y][x] = 3;
                count++;
                
            }
        }
        //std::cout << "count: " << count << std::endl;
    }
    

}

void CA_2D::apply_vicinity_rule()
{
    for(int y = 0; y < width_; y++){
        for (int x = 0; x < length_; x++){
            std::vector<std::pair<int, int>> to_check; 
            to_check = neighbor_check(x,y, neighborhood_); 
            for (const auto& coord : to_check){
                if (grid_[coord.second][coord.first] == 2){
                    next_grid_[y][x] = 2; 
                }
            }
        }
    }
}

void CA_2D::apply_majority_rule(){
    for(int y = 0; y < width_; y++){
        for (int x = 0; x < length_; x++){
            std::vector<std::pair<int, int>> to_check; 
            to_check = neighbor_check(x,y, neighborhood_); 
            double avg=0; 
            double num_neighbors = 0;
            for (const auto& coord : to_check){
                if (grid_[coord.second][coord.first] == 2){
                    avg += 1;
                }
                num_neighbors += 1;
            }
            // ADDED FOR TESTING
            //std::cout << "curr position " << x << ", " << y << " average: " << avg << " num neighbors" << num_neighbors <<std::endl;

            if (neighborhood_ == 0){
                avg = avg/num_neighbors ;
            } else{
                avg = avg/num_neighbors;
            }
            //std::cout << "calc average " << avg << std::endl;
            if (avg >= 0.5){
                next_grid_[y][x] = 2; 
            }
        }
    }
}

// add optional update probability for field application
void CA_2D::step(int rule, double update_probability){
    next_grid_ = grid_;
    time_ += 1;
    // Time Rule
    if (rule == 0){ 

        if (update_probability == 1){
            for(int y = 0; y < width_; y++){
                for (int x = 0; x < length_; x++){
                    if (grid_[y][x] == 2) {
                                
                        next_grid_[y][x] = 3;

                    }
                }
            }
        } else {
            srand(time(nullptr));
            // get current state
            std::vector<int> state_counts = count_states();
            // Access the count of infected
            int num_infected = state_counts[2];

          
            int num_to_change = static_cast<int>(update_probability * num_infected);
            int count = 0;
            // std::cout << "num to change" << num_to_change << std::endl;
            while (count < num_to_change) {
                int x = rand() % length_;
                int y = rand() % width_;

                if (grid_[y][x] == 2) {
                    //std::cout << "current:" <<std::endl;
                    //print();
                    //std::cout << "changing " <<x << ", " << y << std::endl;
                    next_grid_[y][x] = 3;
                    count++;
                    
                }
            }
            //std::cout << "count: " << count << std::endl;
        }

    }

    // vacinity rule 
    if (rule == 1){
        apply_vicinity_rule();
    }

    // majority rule 
    if (rule ==2){
        apply_majority_rule();
    }

    // Maintain blank cells
    for(int y = 0; y < width_; y++){
        for (int x = 0; x < length_; x++){ 
            if (grid_[y][x]==0){ 
                next_grid_[y][x]=0; 
            }
        }
    }
    grid_ = next_grid_;
    // std::cout << "changed " << std::endl;
    // print();
}

// One Dimensional CA class constructor
CA_1D::CA_1D(const int& length, const int& boundary): 
Cellular_Automata(length, boundary) , grid_(length) 
{
    if (length < 3)
    {
        throw std::invalid_argument("Minimum 1d automata length is 3");
    }
}

// 2d is now a stack of 1d grids
// length = x, width =y 
// width = size of the container vector
// length = size of the vectors within. 
// neighborhood = Specify Von Neumann vs Moore
CA_2D::CA_2D(const int& length, 
             const int& width, 
             const int& boundary, 
             const int& neighborhood): 
Cellular_Automata(length, boundary), grid_(width, std::vector<int>(length))
{
    width_ = width;
    neighborhood_ = neighborhood;

    if (length < 3 || width < 3)
    {
        throw std::invalid_argument("Minimum 2d automata length and width is 3");
    }

}

void CA_1D::write_output_file(const std::string& filename) const {
    std::ofstream myfile; 
    myfile.open(filename, std::ios::app); // Open in append mode);
    // int current_time = get_time();
    // myfile<<current_time<<"\n";
    myfile<<"\n";
    for (int x = 0; x < length_; x++){
        myfile<< grid_[x] << " "; 
    }
            myfile<<"\n";
    myfile.close();
}


void CA_2D::write_output_file(const std::string& filename) const {
    std::ofstream myfile; 
    myfile.open(filename, std::ios::app); // Open in append mode);
    // int current_time = get_time();
    // myfile<<current_time<<"\n";
    // I think it would be easier to implement the time in the 
    // python notebook vs here?
    myfile <<"\n";
    for(int y = 0; y < width_; y++){
        for (int x = 0; x < length_; x++){
            myfile<< grid_[y][x] << " "; 
        }
        myfile<<"\n";
    } 
    myfile.close();
}

std::vector<int> CA_1D::count_states() const {

    std::vector<int> counts(4);

    for (const auto& cell : grid_) {
        counts[cell] +=1;
    }

    return counts;
}

std::vector<int> CA_2D::count_states() const {
    std::vector<int> counts(4);

    for (const auto& row : grid_) {
        for (int state : row) {
            counts[state] +=1;
        }
    }

    return counts;
}

Cellular_Automata::~Cellular_Automata() {}
