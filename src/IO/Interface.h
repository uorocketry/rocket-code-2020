#pragma once

#include "config/config.h"
#include "data/sensorsData.h"
#include "helpers/Types.h"
#include <memory>
#include <string>

class Interface
{
public:
	virtual void initialize() = 0;
	
	virtual void calibrateTelemetry()  = 0;

	// to get the latest rocket state. return a pointer to latestState
	virtual std::shared_ptr<sensorsData> getLatest() = 0;

	// loop over each sensor and update the latestState
	virtual bool updateInputs() = 0;
	virtual bool updateOutputs(std::shared_ptr<sensorsData> data) = 0;

	#if USE_GPIO
	virtual void createNewGpioOutput(std::string name, int pinNbr) = 0;
	virtual void createNewGpioPwmOutput(std::string name, int pinNbr) = 0;
	#endif

	virtual time_point getCurrentTime() = 0;
};
