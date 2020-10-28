#include "config/config.h"
#include <iostream>
#include <bitset>
#include "data/sensorsData.h"
#include "UOStateMachine.h"
#include <math.h>

#define PI 3.14159265

UOStateMachine::UOStateMachine() : StateMachine(ST_MAX_STATES)
{
	// There is no state entry function for the first state
	UOStateMachine::enterNewState(States(0));
}

// Start external event
void UOStateMachine::Start()
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
		END_TRANSITION_MAP(NULL)
}

// Apogee external event
// void UOStateMachine::Apogee(UOSMData* data)
void UOStateMachine::Apogee()
{
	BEGIN_TRANSITION_MAP						 // - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		 // ST_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		 // ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		 // ST_WAIT_FOR_LAUNCH
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		 // ST_POWERED_FLIGHT
		TRANSITION_MAP_ENTRY(ST_DESCENT_PHASE_1) // ST_COAST
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		 // ST_DESCENT_PHASE_1
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		 // ST_DESCENT_PHASE_2
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		 // ST_GROUND
		END_TRANSITION_MAP(NULL)
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
	END_TRANSITION_MAP(NULL)}

// Code for each state. Do not put while in them. The right function according to the current state
// will be call in the main loop.

STATE_DEFINE(UOStateMachine, Init, UOSMData)
{
	rocketInterface.initializeSensors();

	InternalEvent(ST_WAIT_FOR_INIT);
}

EXIT_DEFINE(UOStateMachine, ExitInit)
{
	std::cout << "RocketSM::ExitInit\n";
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForInit, UOSMData)
{
	std::cout << "RocketSM::EnterWaitForInit\n";
}

STATE_DEFINE(UOStateMachine, WaitForInit, UOSMData)
{
	rocketInterface.update(data);
	if (rocketInterface.sensorsInitialized())
	{
		InternalEvent(ST_WAIT_FOR_LAUNCH);
	}
}

EXIT_DEFINE(UOStateMachine, ExitWaitForInit)
{
	std::cout << "RocketSM::ExitWaitForInit\n";
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForLaunch, UOSMData)
{
	std::cout << "RocketSM::EnterWaitForLaunch\n";
}

STATE_DEFINE(UOStateMachine, WaitForLaunch, UOSMData)
{
	rocketInterface.update(data);
	rocketData = rocketInterface.getLatest();

	detectExternEvent(rocketData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForLaunch)
{
	std::cout << "RocketSM::ExitWaitForLaunch\n";
}

ENTRY_DEFINE(UOStateMachine, EnterPoweredFlight, UOSMData)
{
	std::cout << "RocketSM::EnterPoweredFlight\n";
}

// code for the flight state
STATE_DEFINE(UOStateMachine, PoweredFlight, UOSMData)
{
	rocketInterface.update(data);
	rocketData = rocketInterface.getLatest();

	InternalEvent(ST_COAST);
	// detectExternEvent(rocketData);
}

EXIT_DEFINE(UOStateMachine, ExitPoweredFlight)
{
	std::cout << "RocketSM::ExitPoweredFlight\n";
}

ENTRY_DEFINE(UOStateMachine, EnterCoast, UOSMData)
{
	std::cout << "RocketSM::EnterCoast\n";
}

STATE_DEFINE(UOStateMachine, Coast, UOSMData)
{
	rocketInterface.update(data);
	rocketData = rocketInterface.getLatest();

	// detectApogee(rocketData);

	detectExternEvent(rocketData);
}

EXIT_DEFINE(UOStateMachine, ExitCoast)
{
	std::cout << "RocketSM::ExitCoast\n";
}

ENTRY_DEFINE(UOStateMachine, EnterDescentPhase1, UOSMData)
{
	std::cout << "RocketSM::EnterDescentPhase1\n";
}

// code for the DescentPhase1 state
STATE_DEFINE(UOStateMachine, DescentPhase1, UOSMData)
{
	rocketInterface.update(data);
	rocketData = rocketInterface.getLatest();

	InternalEvent(ST_DESCENT_PHASE_2);
	// detectExternEvent(rocketData);
}

EXIT_DEFINE(UOStateMachine, ExitDescentPhase1)
{
	std::cout << "RocketSM::ExitDescentPhase1\n";
}

ENTRY_DEFINE(UOStateMachine, EnterDescentPhase2, UOSMData)
{
	std::cout << "RocketSM::EnterDescentPhase2\n";
}

STATE_DEFINE(UOStateMachine, DescentPhase2, UOSMData)
{
	rocketInterface.update(data);
	rocketData = rocketInterface.getLatest();

	detectExternEvent(rocketData);
}

EXIT_DEFINE(UOStateMachine, ExitDescentPhase2)
{
	std::cout << "RocketSM::ExitDescentPhase2\n";
}

ENTRY_DEFINE(UOStateMachine, EnterGround, UOSMData)
{
	std::cout << "RocketSM::EnterGround\n";
}

// code for the ground state
STATE_DEFINE(UOStateMachine, Ground, UOSMData)
{
	rocketInterface.update(data);
	rocketData = rocketInterface.getLatest();

	detectExternEvent(rocketData);
}

void UOStateMachine::detectExternEvent(const sensorsData *data)
{
	int eventNbr = data->inputEventNumber;
	switch (eventNbr)
	{
	case 0:
		Start();
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

void UOStateMachine::detectApogee(const sensorsData *data)
{
#if USE_SBG
	// TODO: only check for apogee x seconds after launch
	// Euler angle
	// pitch is Yangle
	static uint8_t consecutiveEvents = 0;

	float Yangle = (180 / PI) * (acos(cos(data->sbg.Xangle * (PI / 180)) * cos(data->sbg.Yangle * (PI / 180))));

	if (Yangle >= 45)
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
		std::cout << "Apogee \n";
		Apogee();
	}
#endif
}

void UOStateMachine::showInfo(const sensorsData *data)
{
#if USE_SBG
	printf("Barometer: %f\tGps: longitude %f\t latitude %f\t altitude %f\t Velocity: N %f\tE %f\tD %f\tSolutionStatus %d\t%d\n",
		   data->sbg.barometricAltitude,
		   data->sbg.gpsLatitude, data->sbg.gpsLongitude, data->sbg.gpsAltitude,
		   data->sbg.velocityN, data->sbg.velocityE, data->sbg.velocityD,
		   data->sbg.solutionStatus,
		   (data->sbg.solutionStatus) & 0b1111);
// std::cout << std::bitset<32>(data->sbg.solutionStatus) << "\n";
#endif
	return;
}
