#include "../helpers/Types.h"
#include "config/UOStateMachine.h"

#include "helpers/Helper.h"

#define DEFAULT_TARGET_UPDATE_DURATION_NS (1000000000L / 30L) // in nanoseconds = 33 miliseconds = 30Hz

int main()
{
#if TESTING != 1
    InterfaceImpl interfaceImpl;
#else
    TestingInterface interfaceImpl;
#endif

	// create a state machine instance
	UOStateMachine uOttSM(&interfaceImpl);

	time_point start, now;
	duration_ns target_ns, elapsed_ns;
	start = std::chrono::steady_clock::now();
	UOSMData data = UOSMData();

	const uint64_t targetUpdateDuration = 
			helper::getEnvOrDefault("TARGET_UPDATE_DURATION_NS", DEFAULT_TARGET_UPDATE_DURATION_NS);

	uint64_t count = 1;
	while (true)
	{
		// Keep in mind, this is NOT the time since unix epoch (1970), and not the system time
		now = std::chrono::steady_clock::now();

		data.now = now;

		uOttSM.updateStateMachine(&data);

		elapsed_ns = duration_ns(now - start);
		target_ns = duration_ns(targetUpdateDuration * count++);

		if (target_ns > elapsed_ns)
		{
			std::this_thread::sleep_for(target_ns - elapsed_ns);
		}
		else if (targetUpdateDuration != 0)
		{
			std::cout << "Timing Error: Update took too long\n";
		}
	}

	return 0;
}
