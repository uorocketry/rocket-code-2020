#pragma once

#if TESTING

#include "IO/Interface.h"


class TestingInterface : public Interface
{
public:
	TestingInterface();
	~TestingInterface();

	void initialize();
	
	bool isInitialized();
	void calibrateTelemetry();

	// to get the latest rocket state. return a pointer to latestState
	sensorsData *getLatest();

	bool updateInputs();
	bool updateOutputs(const sensorsData &data);

	bool sendData(const sensorsData &data);

private:
	void initializeSensors();
	void initializeOutputs();

	bool updateSensors();
	bool updateOutputs();

	TestingSensors testingSensors;

};

#endif