#pragma once

#include "config/config.h"
#include "data/sensorsData.h"
#include "data/SBGData.h"
#include "IO/SBGSensor.h"
#include "IO/Logger.h"
#include "IO/Radio.h"
#include "IO/Input.h"
#include "IO/SocketClient.h"
#include "IO/IO.h"
#include "data/UOSMData.h"
#include <queue>
#include "IO/TestingSensors.h"
#include "IO/Interface.h"


class InterfaceImpl: public Interface
{
public:
	InterfaceImpl();
	~InterfaceImpl();

	void initialize();
	
	bool isInitialized();
	void calibrateTelemetry();

	// to get the latest rocket state. return a pointer to latestState
	std::shared_ptr<sensorsData> getLatest();

	// loop over each sensor and update the latestState
	bool updateInputs();
	bool updateOutputs(const sensorsData &data);

private:
	void initializeInputs();
	void initializeOutputs();

	std::shared_ptr<sensorsData> latestState;

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

#if USE_RADIO
	Radio radio;
#endif
};
