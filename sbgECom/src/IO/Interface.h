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
};
