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
	rm -f *.o results ising_results.csv ising_results_2D.csv common_parameters.h.gch 
