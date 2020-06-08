#include "Rocket.h"
#include "chrono"
#include "iostream"

#define DELAY 0.005;


int main()
{
	// create a rocket instance
	Rocket uOttRocket;
	
	std::chrono::time_point<std::chrono::high_resolution_clock> start, now; 
	std::chrono::milliseconds ms;

	start = std::chrono::system_clock::now();

	
	while (true) {
		now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed_seconds = now - start;
		ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds);
		std::cout << ms.count() << "\n";

		// uOttRocket.updateRocket();
	}


	return 0;
}
