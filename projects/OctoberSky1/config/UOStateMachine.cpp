#include "config/config.h"
#include <iostream>
#include <bitset>
#include "data/sensorsData.h"
#include "UOStateMachine.h"
#include <cmath>
#include <spdlog/spdlog.h>

#define PI 3.14159265

UOStateMachine::UOStateMachine(Interface* anInterface) :
	InterfacingStateMachine(anInterface, ST_MAX_STATES)
{
	// There is no state entry function for the first state
	UOStateMachine::enterNewState(States(0));

	logger = spdlog::default_logger();
}

// Launch external event
void UOStateMachine::Launch()
{
	BEGIN_TRANSITION_MAP						// - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY(ST_POWERED_FLIGHT) // ST_WAIT_FOR_LAUNCH
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_POWERED_FLIGHT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_COAST
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_DESCENT_PHASE_1
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_DESCENT_PHASE_2
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_GROUND
		END_TRANSITION_MAP(nullptr)
}

// Launch external event
void UOStateMachine::MotorBurnout()
{
	BEGIN_TRANSITION_MAP						// - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) 	// ST_WAIT_FOR_LAUNCH
		TRANSITION_MAP_ENTRY(ST_COAST)			// ST_POWERED_FLIGHT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_COAST
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_DESCENT_PHASE_1
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_DESCENT_PHASE_2
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_GROUND
		END_TRANSITION_MAP(nullptr)
}

// Apogee external event
// void UOStateMachine::Apogee(UOSMData* data)
void UOStateMachine::Apogee()
{
	BEGIN_TRANSITION_MAP						 // - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		 // ST_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		 // ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		 // ST_WAIT_FOR_LAUNCH
		TRANSITION_MAP_ENTRY(ST_DESCENT_PHASE_1) // ST_POWERED_FLIGHT
		TRANSITION_MAP_ENTRY(ST_DESCENT_PHASE_1) // ST_COAST
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		 // ST_DESCENT_PHASE_1
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		 // ST_DESCENT_PHASE_2
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		 // ST_GROUND
		END_TRANSITION_MAP(nullptr)
}

// Touchdown external event
void UOStateMachine::Touchdown(){
	BEGIN_TRANSITION_MAP					// - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_INIT
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_WAIT_FOR_INIT
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_WAIT_FOR_LAUNCH
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_POWERED_FLIGHT
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_COAST
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_DESCENT_PHASE_1
	TRANSITION_MAP_ENTRY(ST_GROUND)			// ST_DESCENT_PHASE_2
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_GROUND
	END_TRANSITION_MAP(nullptr)}

// Code for each state. Do not put while in them. The right function according to the current state
// will be call in the main loop.

STATE_DEFINE(UOStateMachine, Init, UOSMData)
{
	interface->initialize();

	InternalEvent(ST_WAIT_FOR_INIT);
}

EXIT_DEFINE(UOStateMachine, ExitInit)
{
	logger->info("RocketSM::ExitInit");
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForInit, UOSMData)
{
	logger->info("RocketSM::EnterWaitForInit");
	enterNewState(ST_WAIT_FOR_INIT);
}

STATE_DEFINE(UOStateMachine, WaitForInit, UOSMData)
{
	interfaceData = updateInterface(data, ST_WAIT_FOR_INIT);

	 if (interfaceData->isInitialized())
	 {
	 	interface->calibrateTelemetry();
	 	InternalEvent(ST_WAIT_FOR_LAUNCH);
	 }

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForInit)
{
	logger->info("RocketSM::ExitWaitForInit");
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForLaunch, UOSMData)
{
	logger->info("RocketSM::EnterWaitForLaunch");
	enterNewState(ST_WAIT_FOR_LAUNCH);
}

STATE_DEFINE(UOStateMachine, WaitForLaunch, UOSMData)
{
	interfaceData = updateInterface(data, ST_WAIT_FOR_LAUNCH);

	if (isDelayElapsed(duration_ms(1000))) // wait 1 seconds before attempting external event detection
	{
		detectLaunch(interfaceData);
	}

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForLaunch)
{
	logger->info("RocketSM::ExitWaitForLaunch");
}

ENTRY_DEFINE(UOStateMachine, EnterPoweredFlight, UOSMData)
{
	logger->info("RocketSM::EnterPoweredFlight");
	enterNewState(ST_POWERED_FLIGHT);
}

// code for the flight state
STATE_DEFINE(UOStateMachine, PoweredFlight, UOSMData)
{
	interfaceData = updateInterface(data, ST_POWERED_FLIGHT);

	if (isDelayElapsed(duration_ms(500))) // wait 0.5 seconds before attempting external event detection 
	{
		detectApogee(interfaceData);
		detectMotorBurnout(interfaceData);
	}

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitPoweredFlight)
{
	logger->info("RocketSM::ExitPoweredFlight");
}

ENTRY_DEFINE(UOStateMachine, EnterCoast, UOSMData)
{
	logger->info("RocketSM::EnterCoast");
	enterNewState(ST_COAST);
}

STATE_DEFINE(UOStateMachine, Coast, UOSMData)
{
	interfaceData = updateInterface(data, ST_COAST);

	if (isDelayElapsed(duration_ms(500))) // wait 0.5 seconds before attempting external event detection 
	{
		detectApogee(interfaceData);
	}

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitCoast)
{
	logger->info("RocketSM::ExitCoast");
}

ENTRY_DEFINE(UOStateMachine, EnterDescentPhase1, UOSMData)
{
	logger->info("RocketSM::EnterDescentPhase1");
	enterNewState(ST_DESCENT_PHASE_1);
}

// code for the DescentPhase1 state
STATE_DEFINE(UOStateMachine, DescentPhase1, UOSMData)
{
	interfaceData = updateInterface(data, ST_DESCENT_PHASE_1);

#if USE_SBG == 1
	if (interfaceData->sbg.relativeBarometricAltitude <= 100) { // change descent phase at given relative altitude
		InternalEvent(ST_DESCENT_PHASE_2);
	}
#endif
	// InternalEvent(ST_DESCENT_PHASE_2);

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitDescentPhase1)
{
	logger->info("RocketSM::ExitDescentPhase1");
}

ENTRY_DEFINE(UOStateMachine, EnterDescentPhase2, UOSMData)
{
	logger->info("RocketSM::EnterDescentPhase2");
	enterNewState(ST_DESCENT_PHASE_2);
}

STATE_DEFINE(UOStateMachine, DescentPhase2, UOSMData)
{
	interfaceData = updateInterface(data, ST_DESCENT_PHASE_2);

	detectTouchdown(interfaceData);

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitDescentPhase2)
{
	logger->info("RocketSM::ExitDescentPhase2");
}

ENTRY_DEFINE(UOStateMachine, EnterGround, UOSMData)
{
	logger->info("RocketSM::EnterGround");
	enterNewState(ST_GROUND);
}

// code for the ground state
STATE_DEFINE(UOStateMachine, Ground, UOSMData)
{
	interfaceData = updateInterface(data, ST_GROUND);

	interface->updateOutputs(interfaceData);
}

void UOStateMachine::detectExternEvent(const std::shared_ptr<sensorsData>& data)
{
	eventType eventNbr = data->eventNumber;
	
	switch (eventNbr)
	{
	case 0:
		Launch();
		break;
	case 1:
		Apogee();
		break;
	case 2:
		Touchdown();
		break;
	default:
		break;
	}
}

void UOStateMachine::detectLaunch(const std::shared_ptr<sensorsData>& data)
{
#if USE_SBG == 1

	static uint8_t consecutiveEvents = 0;

	float xAcc = data->sbg.filteredXaccelerometer;
	float yAcc = data->sbg.filteredYaccelerometer;
	float zAcc = data->sbg.filteredZaccelerometer;

	float resultingAcc = sqrt(pow(xAcc, 2) + pow(yAcc, 2) + pow(zAcc, 2));
	if (resultingAcc >= 24.5)
	{
		consecutiveEvents++;
	}
	else
	{
		consecutiveEvents = 0;
	}

	// trigger launch if the sbg detects "LaunchThreshold" number of consecutive times
	// that the rocket launching
	if (consecutiveEvents >= LaunchThreshold)
	{
		logger->info("Launch");
		Launch();
	}
#endif
}

void UOStateMachine::detectMotorBurnout(const std::shared_ptr<sensorsData>& data)
{
#if USE_SBG == 1
	// TODO: only check for apogee x seconds after launch
	// Euler angle
	// pitch is pitch
	static uint8_t consecutiveEvents = 0;

	float xAcc = data->sbg.filteredXaccelerometer;
	float yAcc = data->sbg.filteredYaccelerometer;
	float zAcc = data->sbg.filteredZaccelerometer;

	float resultingAcc = sqrt(pow(xAcc, 2) + pow(yAcc, 2) + pow(zAcc, 2));
	if (resultingAcc <= 4.9)
	{
		consecutiveEvents++;
	}
	else
	{
		consecutiveEvents = 0;
	}

	// trigger motor burn out if the sbg detects "BurnOutThreshold" number of consecutive times
	// that the rocket is in coast
	if (consecutiveEvents >= BurnOutThreshold)
	{
		logger->info("MotorBurnout");
		MotorBurnout();
	}
#endif
}

void UOStateMachine::detectTouchdown(const std::shared_ptr<sensorsData>& data)
{
#if USE_SBG == 1
	// TODO: only check for apogee x seconds after launch
	// Euler angle
	// pitch is pitch
	static uint8_t consecutiveEvents = 0;

	float xAcc = data->sbg.filteredXaccelerometer;
	float yAcc = data->sbg.filteredYaccelerometer;
	float zAcc = data->sbg.filteredZaccelerometer;

	float resultingAcc = sqrt(pow(xAcc, 2) + pow(yAcc, 2) + pow(zAcc, 2));
	if (resultingAcc >= 8.82)
	{
		consecutiveEvents++;
	}
	else
	{
		consecutiveEvents = 0;
	}

	// trigger touchdown if the sbg detects "TouchdownThreshold" number of consecutive times
	// that the rocket is on the ground
	if (consecutiveEvents >= TouchdownThreshold)
	{
		logger->info("Touchdown");
		Touchdown();
	}
#endif
}

void UOStateMachine::detectApogee(const std::shared_ptr<sensorsData>& data)
{
#if USE_SBG == 1
	// TODO: only check for apogee x seconds after launch
	// Euler angle
	// pitch is pitch
	static uint8_t consecutiveEvents = 0;

	//float pitch = (180 / PI) * (acos(cos(data->sbg.roll * (PI / 180)) * cos(data->sbg.pitch * (PI / 180))));
	//std::cout << data->sbg.pitch << "\n";

	if (data->sbg.pitch >= -45)
	{
		consecutiveEvents++;
	}
	else
	{
		consecutiveEvents = 0;
	}

	// trigger appogee if the sbg detects "ApogeeThreshold" number of consecutive times
	// that the rocket is pointing downwards and falling
	if (consecutiveEvents >= ApogeeThreshold)
	{
		logger->info("Apogee");
		Apogee();
	}
#endif
}

void UOStateMachine::showInfo(const std::shared_ptr<sensorsData>& data)
{
#if USE_SBG == 1
	printf("Barometer: %f\tGps: longitude %f\t latitude %f\t altitude %f\t Velocity: N %f\tE %f\tD %f\tSolutionStatus %d\t%d\n",
		   data->sbg.barometricAltitude,
		   data->sbg.gpsLatitude, data->sbg.gpsLongitude, data->sbg.gpsAltitude,
		   data->sbg.velocityN, data->sbg.velocityE, data->sbg.velocityD,
		   data->sbg.solutionStatus,
		   (data->sbg.solutionStatus) & 0b1111);
// std::cout << std::bitset<32>(data->sbg.solutionStatus) << "\n";
#endif
}

std::shared_ptr<sensorsData> UOStateMachine::updateInterface(const UOSMData *smdata, States state)
{
	interface->updateInputs();
	std::shared_ptr<sensorsData> data = interface->getLatest();

	// If statement to prevent overwiring data from TESTING
	if (data->timeStamp == 0) data->timeStamp = smdata->now.time_since_epoch().count();

	data->currentStateNo = state;

	return data;
}