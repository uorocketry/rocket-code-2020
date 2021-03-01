#include "config/config.h"
#if TESTING

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

void TestingInterface::initialize()
{
	std::cout << "Initializing TESTING...\n";
	testingSensors.initialize();

	initializeOutputs();
}

void TestingInterface::initializeOutputs() 
{
#if USE_LOGGER
	std::cout << "Initializing LOGGER...\n";
	logger.initialize();
#endif
#if USE_RADIO
	std::cout << "Initializing RADIO...\n";
	radio.initialize();
#endif
}


bool TestingInterface::isInitialized()
{
	return testingSensors.isInitialized();
}

bool TestingInterface::updateInputs()
{
	latestState = std::make_shared<sensorsData>(testingSensors.getLatest());

	return true;
}

bool TestingInterface::updateOutputs(std::shared_ptr<sensorsData> data) 
{
#if USE_LOGGER
	if (latestState->outOfData) {
		if (!logger.queueEmpty()) {
			// Wait for logger to finish
			return false;
		}

		exit(EXIT_SUCCESS);
	}

	logger.enqueueSensorData(*data);
#endif

#if USE_RADIO
	radio.enqueueSensorData(*data);
#endif

	return true;
}

void TestingInterface::calibrateTelemetry() 
{

}


std::shared_ptr<sensorsData> TestingInterface::getLatest()
{
	return latestState;
}

#endif