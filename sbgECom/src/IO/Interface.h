#pragma once

#include "data/sensorsData.h"
#include "data/SMData.h"
#include "data/SBGData.h"
#include "IO/SBGSensor.h"
#include "IO/Logger.h"
#include "IO/Input.h"
#include "IO/SocketClient.h"
#include "IO/IO.h"
#include <queue>

#ifdef TESTING
#include "IO/TestingSensors.h"
#endif // TESTING

template <class SMData>
class Interface
{
public:
	Interface();
	~Interface();

	void initializeSensors();
	bool sensorsInitialized();

	// to get the latest rocket state. return a pointer to latestState
	sensorsData *getLatest();

	// loop over each sensor and update the latestState
	void update(const SMData *SMData);

private:
	sensorsData latestState;

#ifdef TESTING
	TestingSensors testingSensors;
#else
	SBGSensor mySbgSensor;
	Input input;

#ifndef NO_SOCKET_CONTROL
	SocketClient client;
#endif

#endif

#ifndef NO_LOGS
	Logger logger;
#endif
};
