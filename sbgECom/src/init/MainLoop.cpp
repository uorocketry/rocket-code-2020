#include "../helpers/Types.h"
#include "config/UOStateMachine.h"

#include <stdio.h>
#include "chrono"
#include "iostream"
#include <thread>

#define TARGET_DELAY_NS 1000000000L / 30L // in nanoseconds = 33 miliseconds = 30Hz

int main()
{
	// create a state machine instance
	UOStateMachine uOttSM;

	time_point start, now;
	duration_ns target_ns, elapsed_ns;
	start = std::chrono::steady_clock::now();
	UOSMData data = UOSMData();

	uint64_t count = 1;
	while (true)
	{
		// Keep in mind, this is NOT the time since unix epoch (1970), and not the system time
		now = std::chrono::steady_clock::now();

		data.now = now;

		uOttSM.updateStateMachine(&data);

		elapsed_ns = duration_ns(now - start);
		target_ns = duration_ns(TARGET_DELAY_NS * count++);

		if (target_ns > elapsed_ns)
		{
			std::this_thread::sleep_for(target_ns - elapsed_ns);
		}
		else
		{
			std::cout << "Timing Error: Update took too long\n";
		}

		// std::cout.flush();
	}

	return 0;
}
