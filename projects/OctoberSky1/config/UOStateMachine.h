#pragma once

#include "config/config.h"
#include "stateMachineLib/StateMachine.h"
#include "data/sensorsData.h"
#include "data/UOSMData.h"
#include "IO/Interface.h"
#include "helpers/Types.h"

class UOStateMachine : public StateMachine
{
public:
	UOStateMachine();

	// External events taken by this state machine
	// void Apogee(UOSMData* data);
	void Start();
	void Apogee();
	void Touchdown();

private:
	void detectExternEvent(const sensorsData *data);
	void detectApogee(const sensorsData *data);
	void showInfo(const sensorsData *data);

	//number of consecutive readings needed to trigger apogee
	uint8_t ApogeeThreshold = 5;

	Interface rocketInterface;
	sensorsData *rocketData;

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
	STATE_DECLARE(UOStateMachine, Init, UOSMData)
	EXIT_DECLARE(UOStateMachine, ExitInit)
	ENTRY_DECLARE(UOStateMachine, EnterWaitForInit, UOSMData)
	STATE_DECLARE(UOStateMachine, WaitForInit, UOSMData)
	EXIT_DECLARE(UOStateMachine, ExitWaitForInit)
	ENTRY_DECLARE(UOStateMachine, EnterFlight, UOSMData)
	STATE_DECLARE(UOStateMachine, Flight, UOSMData)
	EXIT_DECLARE(UOStateMachine, ExitFlight)
	STATE_DECLARE(UOStateMachine, Descent, UOSMData)
	ENTRY_DECLARE(UOStateMachine, EnterDescent, UOSMData)
	EXIT_DECLARE(UOStateMachine, ExitDescent)
	STATE_DECLARE(UOStateMachine, Ground, UOSMData)
	ENTRY_DECLARE(UOStateMachine, EnterGround, UOSMData)

	// STATE_DECLARE(UOStateMachine, 	Ground,			UOSMData)

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
};