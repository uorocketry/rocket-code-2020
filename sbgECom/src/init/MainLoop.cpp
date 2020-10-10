#include "../stateMachine/Rocket.h"
#include "../helpers/Types.h"

#ifdef HOTFIRE_TEST
#include "../stateMachine/HotFire.h"
#else
#include "../stateMachine/Rocket.h"
#endif

#include <stdio.h>
#include "chrono"
#include "iostream"
#include <thread>

#define TARGET_DELAY_NS 1000000000L/200L // in nanoseconds = 5 miliseconds = 200Hz

int main() {
	// create a state machine instance
#ifdef HOTFIRE_TEST
	HotFire uOttSM;
#else
	Rocket uOttSM;
#endif

	time_point start, now; 
	duration_ns target_ns, elapsed_ns;
	start = std::chrono::steady_clock::now();

	uint64_t count = 1;
	while (true) {
		// Keep in mind, this is NOT the time since unix epoch (1970), and not the system time
		now = std::chrono::steady_clock::now();

#ifdef HOTFIRE_TEST
		UOSMData data = HotFireSMData();
#else
		UOSMData data = RocketSMData();
#endif
		data.now = now;

		uOttSM.updateStateMachine(&data);

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
