#include <spdlog/spdlog.h>
#include "IO.h"
#include "iostream"

IO::IO() {
    logger = spdlog::default_logger();
}

IO::~IO() {
	// destroy thread
	logger->debug("Destroy Thread");
	thisThread.~thread(); // thread not killed
	logger->debug("Thread testSensorThread killed:");
}

void IO::initialize() {
	if (createThread) {
		// create thread
		logger->debug("Create Thread");

		thisThread = std::thread(&IO::run, this);
		thisThread.detach();
	}
}


