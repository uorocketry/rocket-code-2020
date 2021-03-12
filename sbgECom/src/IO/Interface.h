#pragma once

#include "config/config.h"
#include "data/sensorsData.h"
#include "IO/IO.h"
#include <queue>


class Interface
{
public:
	virtual void initialize() = 0;
	
	virtual bool isInitialized() = 0;
	virtual void calibrateTelemetry()  = 0;

	// to get the latest rocket state. return a pointer to latestState
	virtual std::shared_ptr<sensorsData> getLatest() = 0;

	// loop over each sensor and update the latestState
	virtual bool updateInputs() = 0;
	virtual bool updateOutputs(std::shared_ptr<sensorsData> data) = 0;

	virtual time_point getCurrentTime() = 0;
};
