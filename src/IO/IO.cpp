#include "IO.h"
#include "iostream"

IO::IO() = default;

IO::~IO() {
	// destroy thread
	std::cout << "destroy thread" << std::endl;
	thisThread.~thread(); // thread not killed
	std::cout << "Thread " << "testSensorThread" << " killed:" << std::endl;
}

void IO::initialize() {
	if (createThread) {
		// create thread
		std::cout << "create thread" << std::endl;

		thisThread = std::thread(&IO::run, this);
		thisThread.detach();
	}
}


