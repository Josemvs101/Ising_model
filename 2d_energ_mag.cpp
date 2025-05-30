#include "common_parameters.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

// defining spins 

int main() {
    const int A = 100; // Defines 100x100 array of atoms
    std::uniform_real_distribution<double> prob_dist(0.0, 1.0); // defining probability distribution

    std::vector<std::vector<int>> spins(A, std::vector<int>(A)); // 2D vector storage
    std::vector<std::tuple<int, int, int>> results; //vectors stored under 'results' so that data can be recorded into a csv file

    // Defining defect probability distribution.
    std::uniform_real_distribution<double> defect_dist(0.0,1.0);
    for (int i=0; i<A ; ++i) {
        for (int j = 0; j <A; ++j) {
            if (defect_dist(gen) < defect_probability) { // checks if a site is vacant 
                spins[i][j] = 0; // If no atom present => site has no spin 
            }
            else {
                spins[i][j] = prob_dist(gen) ? 1: -1; // spin can be ±1, (studied previously)
            }
        }
    }

    for (int step =0; step < steps; ++step) {
        int i = std::uniform_int_distribution<int>(0, A - 1)(gen);
        int j = std::uniform_int_distribution<int>(0, A - 1)(gen);

        int left = (j > 0 && spins[i][j-1] !=0) ? spins[i][j-1] :0; // simple if else statement to check if spin = 0
        int right = (j < A-1 && spins[i][j+1] !=0) ? spins[i][j+1] :0; // Makes sure there is an atom to the right (j != A-1)
        int up = (i > 0 && spins[i-1][j] !=0) ? spins[i-1][j] :0; 
        int down = (i < A-1 && spins[i+1][j] != 0) ? spins[i+1][j] :0;
        
        if (spins[i][j] != 0) { // calculating energy for particles that exist! (ie spin != 0)
            int dE = 2*J*spins[i][j]*(left + right + up + down); // Ising model with 4 neighbours
            if (dE <= 0 || prob_dist(gen) < exp(-dE / kT)) { // testing if it is probable for spins to flip at temperature T
                spins[i][j] *= -1;
            }
        }

        if (step % output_interval == 0) {
            int magnetisation = 0; // initial parameters
            
            // Calculate magnetisation (changed to account for 2D array)
            for (const auto& row : spins) {
                for (int s: row) {
                    if (s != 0) {
                        magnetisation += s; // Again, only calculating magnetisation for real atoms.
                    }
                }
            }
            
            // Calculate total energy for array A
            int total_energy = 0;
            for (int i = 0; i < A; ++i) {
                for (int j=0; j<A; ++j) {
                    int right = (j < A-1) ? spins[i][j+1] : 0;
                    int down = (i < A-1) ? spins[i+1][j] : 0;
                    total_energy += -J*spins[i][j]*(right + down); // algorithm to sum energies starting from the bottom left
                    // of the grid going right and up (avoids double counting). 
                }
            }
            results.emplace_back(step, total_energy, magnetisation); // tuple
        }
    }

    auto [step, final_energy, final_magnetisation] = results.back();  // unpacks tuple and stores values as variables
    std::cout<< "\n<======================SUMMARY DATA (2D) ======================>" // prints out values in a neat way 
             << "\nTotal Energy: " << final_energy 
             << "\nTotal Magnetism: "<< final_magnetisation 
             << "\n<=========================================================>" 
             << std::endl;
    
    // Write results to a csv file.
    std::ofstream file("ising_results_2D.csv");
    file << "Step,Energy,Magnetisation\n";
    for (const auto&[step, energy, magnetisation] : results) {
        file << step << "," << energy << "," << magnetisation << "\n";
    }
    file.close();

    std::cout << "Simulation complete. Results saved to ising_results_2D.csv\n";
    
}