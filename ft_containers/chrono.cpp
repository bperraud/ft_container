#include "chrono.hpp"


void chrono::start()
{
	_start = std::chrono::high_resolution_clock::now();
}

void chrono::printElapsedTime() {
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - _start);
	std::cout << "Elapsed time: " << duration.count() << " ms\n";
}
