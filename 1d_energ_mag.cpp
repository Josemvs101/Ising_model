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

    
}