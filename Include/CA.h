// University of California, Berkeley
// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences 
// December 2023
 
// Creators: Qi Tifany Chu, Sean Bray and Elizabeth Gilson

// This file contains the C++ class declarations for Cellular_Automata, 
// and its derived classes CA_1D and CA_2D in the Source/cellular_automata.cpp file. 

#include <vector>
#include <iostream>
#include <cstdlib>
#include <random>

class Cellular_Automata {
    protected:
        int states;
        int boundary_;
        int neighborhood_;
        int length_;
        int width_;
        int time_ = 0;

    public:
        // For the constructor of the 2D derived class, it also sets width_,
        // But for the 1D only this is called.
        Cellular_Automata(int length, int boundary)
        : length_(length), boundary_(boundary) {}

        // Setting these equal to zero here specifies that they are "pure virtual"
        // functions, which makes sure that we override them in the derived classes.
        // This proves to be necessary for compiling (unless we wanted to define
        // default functions for the base class, which I think would be harder).
        virtual void print() const = 0;
        virtual void initialize(const double& percent) = 0;
        virtual void cutoff_boundary() = 0;
        // added update probability
        virtual void step(int rule, double update_probability=1) = 0;
        virtual void apply_time_rule(double update_probability=1) = 0;
        virtual void apply_vicinity_rule() = 0;
        virtual void apply_majority_rule() = 0;
        virtual void write_output_file(const std::string& filename) const = 0;
        virtual std::vector<int> count_states() const = 0;
        int get_time() const;

        std::vector<std::pair<int, int>> neighbor_check(int x, int y, int neighborhood);


        // Virtual destructor, apparently necessary for polymorphism
        virtual ~Cellular_Automata();
};

class CA_1D : public Cellular_Automata {
    private:
        std::vector<int> grid_;
        std::vector<int> next_grid_;

    public:
        CA_1D(const int& length, const int& boundary);
        void initialize(const double& percent) override;

        std::vector<int> get_grid() const;
        void set_grid(const std::vector<int>& new_grid);
        void print() const override;
        std::vector<int> get_neighbors(const int& x) const;
        void cutoff_boundary() override;
        // added update probability
        void step(int rule, double update_probability=1) override;
        void apply_time_rule(double update_probability=1) override;
        void apply_vicinity_rule() override;
        void apply_majority_rule() override;

        void write_output_file(const std::string& filename) const override;
        std::vector<int> count_states() const override;
};

class CA_2D : public Cellular_Automata {
    private:
        std::vector<std::vector<int>> grid_;
        std::vector<std::vector<int>> next_grid_;

    public:
        CA_2D(const int& length, 
              const int& width, 
              const int& boundary, 
              const int& neighborhood);

        void print() const override;
        void initialize(const double& percent) override;

        std::vector<std::vector<int>> get_grid() const;
        void set_grid(const std::vector<std::vector<int>>& grid);
        std::vector<std::pair<int, int>> neighbor_check(int x, int y, int neighborhood);
        std::vector<std::pair<int, int>> get_neighbors(int x, int y);

        void set_grid(std::vector<std::vector<int>>) const;

        void cutoff_boundary() override;
        // added update probability
        //void step(int rule) override;
        void step(int rule, double update_probability=1) override;
        void apply_time_rule(double update_probability=1) override;
        void apply_vicinity_rule() override;
        void apply_majority_rule() override;
        void write_output_file(const std::string& filename) const override;
        std::vector<int> count_states() const override;
        // ~CA_2D();
};