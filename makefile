results: 1d_energ_mag.o
	g++ -std=c++11 1d_energ_mag.o -o results

1d_energ_mag.o: 1d_energ_mag.cpp
	g++ -std=c++11 -c 1d_energ_mag.cpp #compiling

clean:
	rm -f *.o results
