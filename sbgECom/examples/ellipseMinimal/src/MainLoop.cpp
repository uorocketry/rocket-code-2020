#include "Rocket.h"
#include "chrono"
#include "iostream"

#define DELAYMS 5000 //5000 microseconds = 0.005s = 200 Hz


int main()
{
	// create a rocket instance
	Rocket uOttRocket;
	
	std::chrono::time_point<std::chrono::high_resolution_clock> start, now; 
	std::chrono::microseconds ms;
	std::chrono::duration<long double> elapsed_seconds;
	start = std::chrono::system_clock::now();

	
	while (true) {
		now = std::chrono::high_resolution_clock::now();
		elapsed_seconds = now - start;
		ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed_seconds);
		std::cout << ms.count() << "\n";



		//uOttRocket.updateRocket();
	}


	return 0;
}
