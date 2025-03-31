
# Ising Model Simulation

## Note

For python visualisation, please use the code provided in the last commit (1b81e993b2509e7d33a5f8e2ac37b7d807042e25).

## Overview

This project implements the **Ising Model** in both **1D** and **2D** dimensions. These simulation to model the magnetic behavior of a lattice of spins, considering interactions between neighboring spins. The results are saved to CSV files and can be visualized for further analysis.

## Introduction

The Ising model simulates spins arranged in a grid, where each spin interacts with its neighbors. The model is used to study the behavior of ferromagnetic materials, especially to understand phase transitions like magnetisation and energy. The program simulates random configurations of spins using the Metropolis algorithm, allowing the exploration of the system's properties.

## Getting Started

To get started with this project, follow the instructions below.

### Clone the repository

I have provided a link to my github within my report and here if you would like to use it. This might make things easier to keep track of changes

link: https://github.com/Josemvs101/Ising_model
If there are any issues with this link then use:
repo name: Ising_model
username: Josemvs101

### Install Dependencies

This project requires a **C++ compiler** that supports C++17.

## Dependencies

- **C++17** compatible compiler (`g++` recommended)
- **Standard libraries** such as `<vector>`, `<random>`, and `<fstream>`
  
## Running the Simulation

### 1D Simulation

To compile and run the **1D Ising model** simulation:

```bash
make run_1d
```

This will execute the 1D simulation, and the results will be saved to `ising_results.csv`.

### 2D Simulation

To compile and run the **2D Ising model** simulation:

```bash
make run_2d
```

This will execute the 2D simulation, and the results will be saved to `ising_results_2D.csv`.

### Clean Up

To remove the compiled object files and results (for all simulations):

```bash
make clean
```

## Makefile

The following `Makefile` handles the compilation and execution of both 1D and 2D simulations.

```makefile
## Updated makefile to now handle compiling the Ising model in either 1 or 2 dimensions

1d.o: 1d_energ_mag.cpp
	g++ -std=c++17 -c 1d_energ_mag.cpp -o 1d.o

2d.o: 2d_energ_mag.cpp
	g++ -std=c++17 -c 2d_energ_mag.cpp -o 2d.o

1d_results: 1d.o
	g++ -std=c++17 1d.o -o 1d_results
2d_results: 2d.o
	g++ -std=c++17 2d.o -o 2d_results		

run_1d: 1d_results
	./1d_results

run_2d: 2d_results
	./2d_results

clean:
	rm -f *.o 1d_results ising_results.csv ising_results_2D.csv common_parameters.h.gch 2d_results
```

## Results

The simulation outputs the following data at each step:

- **Energy**: The total energy of the system at the current step.
- **Magnetisation**: The total magnetization of the system at the current step.

These results are saved to a CSV file for analysis and can be visualized using tools like **Excel** or **Python** (with libraries such as **pandas** and **matplotlib**).

