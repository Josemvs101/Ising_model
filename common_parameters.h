// This file allows us to build 2d and 3d models without redifining common parameters
#include <random>

const int J = 1; // coupling constant 
const double kT = 25; // boltzman factor
const int steps = 1000; // Monte Carlo steps
const int output_interval = 10; // saves each 'x' step

// random number generator 
std::random_device rd;
std::mt19937 gen(rd());
extern std::uniform_real_distribution<double> prob_dist;

// Vacancy (defects) probability dist
const double defect_probability = 0.125; // sets chance of vacant site to x%

