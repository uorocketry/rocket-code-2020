#include "Rocket.h"
#include "chrono"
#include "iostream"
#include <thread>

#define DELAYMS 1000000000 //5000 microseconds = 0.005s = 200 Hz


int main()
{
	// create a rocket instance
	//Rocket uOttRocket;
	
	std::cout << "ok";
	std::chrono::time_point<std::chrono::high_resolution_clock> start, now; 
	start = std::chrono::high_resolution_clock::now();
	
	unsigned long int count = 1;
	while (true) {
		// uOttRocket.updateRocket();
		
		now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<int64_t, std::nano> elapsed_seconds = now - start;
		
		std::chrono::microseconds elapsed_seconds_ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed_seconds);
		std::chrono::duration<int64_t, std::nano> target_ms(DELAYMS * count++);
		//https://www.geeksforgeeks.org/chrono-in-c/
		
		
		std::cout << elapsed_seconds.count() << " : ";
		// std::cout << ms.count() << "\n";

		std::this_thread::sleep_for(target_ms - elapsed_seconds_ms);

		// std::this_thread::sleep( boost::posix_time::milliseconds(1000) );
		
		
	}


	return 0;
}
