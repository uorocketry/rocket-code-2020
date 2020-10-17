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
	BEGIN_TRANSITION_MAP					// - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_INIT
		TRANSITION_MAP_ENTRY(ST_FLIGHT)		// ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FLIGHT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DESCENT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_GROUND
		END_TRANSITION_MAP(NULL)
}

// Apogee external event
// void UOStateMachine::Apogee(UOSMData* data)
void UOStateMachine::Apogee()
{
	BEGIN_TRANSITION_MAP					// - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY(ST_DESCENT)	// ST_FLIGHT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DESCENT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_GROUND
		END_TRANSITION_MAP(NULL)
	// END_TRANSITION_MAP(data)

	// CANNOT_HAPPEN
}

// Touchdown external event
void UOStateMachine::Touchdown(){
	BEGIN_TRANSITION_MAP					// - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_INIT
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_WAIT_FOR_INIT
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_FLIGHT
	TRANSITION_MAP_ENTRY(ST_GROUND)			// ST_DESCENT
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_GROUND
	END_TRANSITION_MAP(NULL)}

// Code for each state. Do not put while in them. The right function according to the current state
// will be call in the main loop.

// code for the initialization state
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
	enterNewState(ST_WAIT_FOR_INIT);

	std::cout << "RocketSM::EnterWaitForInit\n";
}

// code for the wait for initialization state
STATE_DEFINE(UOStateMachine, WaitForInit, UOSMData)
{
	rocketInterface.update(data);
	rocketData = rocketInterface.getLatest();

	if (rocketInterface.sensorsInitialized())
		InternalEvent(ST_FLIGHT);

	// showInfo(rocketData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForInit)
{
	std::cout << "RocketSM::ExitWaitForInit\n";
}

ENTRY_DEFINE(UOStateMachine, EnterFlight, UOSMData)
{
	enterNewState(ST_FLIGHT);

	std::cout << "RocketSM::EnterFlight\n";
}

// code for the flight state
STATE_DEFINE(UOStateMachine, Flight, UOSMData)
{
	rocketInterface.update(data);
	rocketData = rocketInterface.getLatest();

	// TODO: move detect Apogee to coast state when new states are added
	detectApogee(rocketData);

	detectExternEvent(rocketData);

	// showInfo(rocketData);
}

// Exit action when WaitForDeceleration state exits.
EXIT_DEFINE(UOStateMachine, ExitFlight)
{
	std::cout << "RocketSM::ExitFlight\n";
}

ENTRY_DEFINE(UOStateMachine, EnterDescent, UOSMData)
{
	enterNewState(ST_DESCENT);

	std::cout << "RocketSM::EnterDescent\n";
}

// code for the Descent state
STATE_DEFINE(UOStateMachine, Descent, UOSMData)
{
	// InternalEvent(ST_GROUND);

	rocketInterface.update(data);
	rocketData = rocketInterface.getLatest();

	detectExternEvent(rocketData);
	// showInfo(rocketData);

	// perform the descent processing here
	// transition to Flight via an internal event
	// InternalEvent(ST_FLIGHT);
}

// Exit action when ExitDescent state exits.
EXIT_DEFINE(UOStateMachine, ExitDescent)
{
	std::cout << "RocketSM::ExitDescent\n";
}

// Entry action when ExitDescent state exits.
ENTRY_DEFINE(UOStateMachine, EnterGround, UOSMData)
{
	enterNewState(ST_GROUND);

	std::cout << "RocketSM::EnterGround\n";
}

// code for the ground state
STATE_DEFINE(UOStateMachine, Ground, UOSMData)
{
	rocketInterface.update(data);
	rocketData = rocketInterface.getLatest();

	detectExternEvent(rocketData);
	// showInfo(rocketData);
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

#if USE_SOCKET_CLIENT
	eventNbr = data->clientEventNumber;
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
#endif
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

void UOStateMachine::enterNewState(States state)
{
	StateMachine::enterNewState(state);
}

double UOStateMachine::getValueForTime(double minimum, double maximum, duration_ms targetTime)
{
	duration_ns timeSinceEntry = std::chrono::steady_clock::now() - entryTime;
	double progress = ((double)timeSinceEntry.count()) / duration_ns(targetTime).count();
	return std::min(maximum, minimum + progress * (maximum - minimum));
}

bool UOStateMachine::switchStatesAfterTime(States state, duration_ms targetTime)
{
	duration_ns timeSinceEntry = std::chrono::steady_clock::now() - entryTime;
	if (timeSinceEntry >= duration_ns(targetTime))
	{
		InternalEvent(state);

		return true;
	}

	return false;
}