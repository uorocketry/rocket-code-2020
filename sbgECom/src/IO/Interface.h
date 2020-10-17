#pragma once

#include "data/sensorsData.h"
#include "data/SBGData.h"
#include "IO/SBGSensor.h"
#include "IO/Logger.h"
#include "IO/Input.h"
#include "IO/SocketClient.h"
#include "IO/IO.h"
#include "data/UOSMData.h"
#include <queue>

#if TESTING
#include "IO/TestingSensors.h"
#endif // TESTING

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
	void update(const UOSMData *smdata);

private:
	sensorsData latestState;

#if TESTING
	TestingSensors testingSensors;
#endif

#if USE_SBG
	SBGSensor mySbgSensor;
#endif

#if USE_INPUT
	Input input;
#endif

#if USE_SOCKET_CLIENT
	SocketClient client;
#endif

#if USE_LOGGER
	Logger logger;
#endif
};
