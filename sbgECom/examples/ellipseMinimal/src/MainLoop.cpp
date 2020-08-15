#include "Rocket.h"
#include "helpers/Types.h"

#include <stdio.h>
#include "chrono"
#include "iostream"
#include <thread>

#define TARGET_DELAY_NS 1000000000L/200L // in nanoseconds = 5 miliseconds = 200Hz

int main() {
	// create a rocket instance
	Rocket uOttRocket;

	time_point start, now; 
	duration_ns target_ns, elapsed_ns;
	start = std::chrono::steady_clock::now();

	uint64_t count = 1;
	while (true) {
		now = std::chrono::steady_clock::now();

		RocketSMData data;
		data.now = now;

		uOttRocket.updateRocket(&data);

		elapsed_ns = duration_ns(now - start);
		target_ns = duration_ns(TARGET_DELAY_NS * count++);		
		
		if (target_ns > elapsed_ns) {
			std::this_thread::sleep_for(target_ns - elapsed_ns);
		} else {
			std::cout << "Timing Error: Update took too long\n";
		}

		// std::cout.flush();
	}


	return 0;
}
