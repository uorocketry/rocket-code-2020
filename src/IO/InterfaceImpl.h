#pragma once

#include "config/config.h"
#if !TESTING

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
	
	bool isInitialized();
	void calibrateTelemetry();

	// to get the latest rocket state. return a pointer to latestState
	std::shared_ptr<sensorsData> getLatest();

	// loop over each sensor and update the latestState
	bool updateInputs();
	bool updateOutputs(std::shared_ptr<sensorsData> data);

	#ifdef USE_GPIO
	void createNewGpioPwmOutput(std::string name, int pinNbr);
	#endif

	time_point getCurrentTime();

private:
	void initializeInputs();
	void initializeOutputs();

	std::shared_ptr<sensorsData> latestState;
	EventQueue eventQueue;

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

#if USE_GPIO
	Gpio gpio;
#endif
};

#endif