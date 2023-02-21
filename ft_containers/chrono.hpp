#ifndef CHRONO_HPP
#define CHRONO_HPP

#include <iostream>
#include <chrono>

class chrono {

private:
	std::chrono::high_resolution_clock::time_point _start;

public:
	chrono() ;
	void printElapsedTime() ;
	void start();
};

#endif
