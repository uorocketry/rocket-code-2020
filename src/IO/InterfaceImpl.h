#pragma once

#include "config/config.h"
#if TESTING != 1

#include "IO/Interface.h"
#include "IO/SBGSensor.h"
#include "IO/Input.h"
#include "IO/SocketClient.h"
#include "IO/Logger.h"
#include "IO/Radio.h"
#include "IO/Gpio.h"
#include "EventQueue.h"
#include <memory>
#include <string>

class InterfaceImpl: public Interface
{
public:
	InterfaceImpl();
	~InterfaceImpl();

	void initialize();
	
	void calibrateTelemetry();

	// to get the latest rocket state. return a pointer to latestState
	std::shared_ptr<sensorsData> getLatest();

	// loop over each sensor and update the latestState
	bool updateInputs();
	bool updateOutputs(std::shared_ptr<sensorsData> data);

	#if USE_GPIO == 1
	void createNewGpioOutput(std::string name, int pinNbr);
	void createNewGpioPwmOutput(std::string name, int pinNbr);
	#endif

	time_point getCurrentTime();

private:
	void initializeInputs();
	void initializeOutputs();

	std::shared_ptr<sensorsData> latestState;
	EventQueue eventQueue;

#if USE_SBG == 1
	SBGSensor mySbgSensor;
#endif

#if USE_INPUT == 1
	Input input;
#endif

#if USE_SOCKET_CLIENT == 1
	SocketClient client;
#endif

#if USE_RADIO == 1
	Radio radio;
#endif

#if USE_LOGGER == 1
	Logger logger;
#endif

#if USE_GPIO == 1
	Gpio gpio;
#endif
};

#endif