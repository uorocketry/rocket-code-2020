#pragma once

#include "../stateMachineLib/StateMachine.h"
#include "../data/rocketState.h"
#include "../data/RocketSMData.h"
#include "../IO/Interface.h"
#include "../helpers/Types.h"

#ifndef USE_SBG
#define USE_SBG 1
#endif

#ifndef USE_SOCKET_CLIENT
#define USE_SOCKET_CLIENT 0
#endif

#ifndef USE_LOGGER
#define USE_LOGGER 1
#endif

#ifndef USE_INPUT
#define USE_INPUT 1
#endif

#ifndef USE_TESTING_SENSORS
#define USE_TESTING_SENSORS 0
#endif

class Rocket : public StateMachine
{
public:
	Rocket();

	// External events taken by this state machine
	// void Apogee(RocketSMData* data);
	void Start();
	void Apogee();
	void Touchdown();

private:
	void detectExternEvent(const rocketState *data);
	void detectApogee(const rocketState *data);
	void showInfo(const rocketState *data);

	//number of consecutive readings needed to trigger apogee
	uint8_t ApogeeThreshold = 5;

	Interface rocketInterface;
	rocketState *rocketData;

	time_point entryTime;

	// State enumeration order must match the order of state method entries
	// in the state map.
	enum States
	{
		ST_INIT,
		ST_WAIT_FOR_INIT,
		ST_FLIGHT,
		ST_DESCENT,
		ST_GROUND,
		ST_MAX_STATES
	};

	// Define the state machine state functions with event data type
	STATE_DECLARE(Rocket, Init, RocketSMData)
	EXIT_DECLARE(Rocket, ExitInit)
	ENTRY_DECLARE(Rocket, EnterWaitForInit, RocketSMData)
	STATE_DECLARE(Rocket, WaitForInit, RocketSMData)
	EXIT_DECLARE(Rocket, ExitWaitForInit)
	ENTRY_DECLARE(Rocket, EnterFlight, RocketSMData)
	STATE_DECLARE(Rocket, Flight, RocketSMData)
	EXIT_DECLARE(Rocket, ExitFlight)
	STATE_DECLARE(Rocket, Descent, RocketSMData)
	ENTRY_DECLARE(Rocket, EnterDescent, RocketSMData)
	EXIT_DECLARE(Rocket, ExitDescent)
	STATE_DECLARE(Rocket, Ground, RocketSMData)
	ENTRY_DECLARE(Rocket, EnterGround, RocketSMData)

	// STATE_DECLARE(Rocket, 	Ground,			RocketSMData)

	// State map to define state object order. Each state map entry defines a
	// state object.
	// BEGIN_STATE_MAP
	// 	STATE_MAP_ENTRY(&Flight)
	// 	STATE_MAP_ENTRY(&Descent)
	// 	STATE_MAP_ENTRY(&Ground)
	// END_STATE_MAP

	// State map to define state object order. Each state map entry defines a
	// state object.
	BEGIN_STATE_MAP_EX
	STATE_MAP_ENTRY_ALL_EX(&Init, 0, 0, &ExitInit)
	STATE_MAP_ENTRY_ALL_EX(&WaitForInit, 0, &EnterWaitForInit, &ExitWaitForInit)
	STATE_MAP_ENTRY_ALL_EX(&Flight, 0, &EnterFlight, &ExitFlight)
	STATE_MAP_ENTRY_ALL_EX(&Descent, 0, &EnterDescent, &ExitDescent)
	STATE_MAP_ENTRY_ALL_EX(&Ground, 0, &EnterGround, 0)
	END_STATE_MAP_EX

	void enterNewState(States state);

	double getValueForTime(double minimum, double maximum, duration_ms targetTime);

	bool switchStatesAfterTime(States state, duration_ms targetTime);
};