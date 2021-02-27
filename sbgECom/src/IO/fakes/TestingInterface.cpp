#if TESTING

#include "config/config.h"
#include "TestingInterface.h"
#include "IO/IO.h"
#include "data/UOSMData.h"
#include <iostream>
#include "IO/TestingSensors.h"


TestingInterface::TestingInterface()
{
}

TestingInterface::~TestingInterface()
{
}

void TestingInterface::initializeSensors()
{
	std::cout << "Initializing TESTING...\n";
	testingSensors.initialize();
}


bool TestingInterface::isInitialized()
{
	return true;
}

bool TestingInterface::updateInputs()
{
	latestState = testingSensors.getLatest();

	if (latestState.outOfData) {
		#if USE_LOGGER
		if (!logger.queueEmpty()) {
			// Wait for logger to finish
			return false;
		}
		#endif

		exit(EXIT_SUCCESS);
	}

	return true;
}

bool TestingInterface::updateOutputs(sensorsData data) 
{
#if USE_LOGGER
	logger.enqueueSensorData(data);
#endif

#if USE_RADIO
	radio.enqueueSensorData(data);
#endif

	return true;
}

void TestingInterface::calibrateTelemetry() 
{

}


sensorsData *TestingInterface::getLatest()
{
	return &latestState;
}

#endif