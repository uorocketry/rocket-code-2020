#pragma once

#if TESTING

#include "IO/Interface.h"
#include "IO/TestingSensors.h"

class TestingInterface : public Interface
{
public:
	TestingInterface();
	~TestingInterface();

	void initialize();
	
	bool isInitialized();
	void calibrateTelemetry();

	// to get the latest rocket state. return a pointer to latestState
	std::shared_ptr<sensorsData> getLatest();

	bool updateInputs();
	bool updateOutputs(std::shared_ptr<sensorsData> data);

private:
	void initializeOutputs();

	std::shared_ptr<sensorsData> latestState;

	TestingSensors testingSensors;

#if USE_LOGGER
	Logger logger;
#endif

#if USE_RADIO
	Radio radio;
#endif
};

#endif