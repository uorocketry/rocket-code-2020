#include "Rocket.h"
#include <stdio.h>
#include "chrono"
#include "iostream"
#include <thread>

#define TARGET_DELAY_NS 1000000000/200 // in nanoseconds = 5 miliseconds = 200Hz

int main()
{
	// create a rocket instance
	Rocket uOttRocket;

	std::chrono::time_point<std::chrono::high_resolution_clock> start, now; 
	std::chrono::duration<int64_t, std::nano> target_ns, elapsed_ns;
	start = std::chrono::high_resolution_clock::now();

	unsigned long int count = 1;
	while (true) {
		now = std::chrono::high_resolution_clock::now();

		uOttRocket.updateRocket();

		elapsed_ns = std::chrono::duration<int64_t, std::nano>(now - start);
		target_ns = std::chrono::duration<int64_t, std::nano>(TARGET_DELAY_NS * count++);		
		

		if (target_ns > elapsed_ns) {
			std::this_thread::sleep_for(target_ns - elapsed_ns);
		} else {
			std::cout << "ERROR\n";
		}

		// std::cout.flush();
	}


	return 0;
}
