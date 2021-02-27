#include "config/config.h"
#include "InterfaceImpl.h"
#include "IO/IO.h"
#include "data/UOSMData.h"
#include <iostream>
#include "IO/TestingSensors.h"


InterfaceImpl::InterfaceImpl()
{
}

InterfaceImpl::~InterfaceImpl()
{
}

void InterfaceImpl::initialize() 
{
	initializeInputs();
	initializeOutputs();
}

void InterfaceImpl::initializeInputs()
{
	#if USE_SBG
		std::cout << "Initializing SBG...\n";
		mySbgSensor.initialize();
	#endif
	#if USE_INPUT
		std::cout << "Initializing INPUT...\n";
		input.initialize();
	#endif
	#if USE_SOCKET_CLIENT
		std::cout << "Initializing SOCKET_CLIENT...\n";
		client.initialize();
	#endif
}

void InterfaceImpl::initializeOutputs() 
{
#if USE_LOGGER
	std::cout << "Initializing LOGGER...\n";
	logger.initialize();
#endif
#if USE_RADIO
	std::cout << "Initializing RADIO...\n";
	radio.initialize();
#endif
}


bool InterfaceImpl::isInitialized()
{
#if SKIP_INIT
	std::cout << "Skipping init\n";
	return true;
#endif

	bool result = 1;

#if USE_LOGGER
	result &= logger.isInitialized();
#endif

#if USE_SOCKET_CLIENT
	result &= client.isInitialized();
#endif

#if USE_SBG
	result &= mySbgSensor.isInitialized();
#endif

#if USE_INPUT
	result &= input.isInitialized();
#endif

#if USE_RADIO
	result &= radio.isInitialized();
#endif

	return result;
}

/*void InterfaceImpl::update(const UOSMData *smdata, int currentStateNo)
{
	latestState.timeStamp = smdata->now.time_since_epoch().count();

	if (!updateSensors()) {
		return;
	}

	// Save current state no matter what
	latestState.currentStateNo = currentStateNo;

	if (!updateOutputs()) {
		return;
	}
}*/

bool InterfaceImpl::updateInputs()
{
	latestState = std::make_shared<sensorsData>();
	// latestState = sensorsData();

#if USE_SBG
	latestState->sbg = mySbgSensor.getData();
#endif

#if USE_INPUT
	latestState->inputEventNumber = input.getData();
#endif

#if USE_SOCKET_CLIENT
	latestState->clientEventNumber = client.getData();
#endif

	return true;
}

bool InterfaceImpl::updateOutputs(const sensorsData &data) 
{
#if USE_LOGGER
	logger.enqueueSensorData(data);
#endif

#if USE_RADIO
	radio.enqueueSensorData(data);
#endif

	return true;
}


void InterfaceImpl::calibrateTelemetry() 
{
#if USE_SBG
	mySbgSensor.setZeroBarometricAltitude();
#endif
}


std::shared_ptr<sensorsData> InterfaceImpl::getLatest()
{
	return latestState;
}
