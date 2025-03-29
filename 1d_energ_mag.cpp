#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cmath>

const int N = 3; // Number of atoms (to test if produced energy values output 0,-2,2)
const int steps = 10000; // Number of Monte Carlo steps
const int J = 1; // Coupling constant (as instructed)
const double kT = 2.5; // Temperature factor (k_B * T)
const int output_interval = 1; // Save every step

int main() {
    std::vector<int> spins(N);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> spin_dist(0, 1);

    // Initialise spins randomly
    for (int i = 0; i < N; ++i) {
        spins[i] = spin_dist(gen) ? 1 : -1;
    }
    std::uniform_real_distribution<double> prob_dist(0.0, 1.0); // unif dist generator
    std::vector<std::tuple<int, int, int>> results; // Stores spin values as vectors

    // After defnining how the spins are stored, we're going to use the each Monte Carlo step to calculate energy values for 
    // all possible configurations (E = 0,-2,2 out of 8 possible configs)

    for (int step = 0; step < steps; ++step) { 
        int i = std::uniform_int_distribution<int>(0, N - 1)(gen); // This will pick a random spin for each atom
        
        // Calculate neighbors with open boundary conditions (1D chain)
        int left = (i > 0) ? spins[i - 1] : 0; 
        int right = (i < N - 1) ? spins[i + 1] : 0; // checks that terminal atoms only with 1 other atom
        int dE = 2 * J * spins[i] * (left + right); // Ising model interacting with 2 neighbours 

        // the system will find the lower energy states that can be occupied. 
        // This is represented by the spin state flip below

        if (dE <= 0 || prob_dist(gen) < exp(-dE / kT)) { // testing if it is probable for spins to flip at temperature T
            spins[i] *= -1;
        }

        if (step % output_interval == 0) {
            int total_energy = 0;
            int magnetization = 0; // initial parameters
            
            // Calculate magnetization
            for (int s : spins) {
                magnetization += s;
            }
            
            // Calculate energy for open chain (N-1 bonds)
            for (int j = 0; j < N - 1; ++j) {
                total_energy += -J * spins[j] * spins[j + 1]; // total energy 
            }
            
            results.emplace_back(step, total_energy, magnetization);
        }
    }

    // Write results to a csv file.
    std::ofstream file("ising_results.csv");
    file << "Step,Energy,Magnetization\n";
    for (const auto& [step, energy, magnetization] : results) {
        file << step << "," << energy << "," << magnetization << "\n";
    }
    file.close();

    std::cout << "Simulation complete. Results saved to ising_results.csv\n";
    
}
