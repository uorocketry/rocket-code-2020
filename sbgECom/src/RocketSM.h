#ifndef _MOTOR_H
#define _MOTOR_H

#include "stateMachine/StateMachine.h"
#include "rocketState.h"

class RocketSMData : public EventData
{
public:
	rocketState *data;
};

class RocketSM : public StateMachine
{
public:
	RocketSM();

	// External events taken by this state machine
	// void Apogee(RocketSMData* data);
	void Apogee();
	void Touchdown();

private:
	INT m_currentSpeed; 

	int *get_bits(int n, int bitswanted);
	void showInfo(const RocketSMData* data);
	// State enumeration order must match the order of state method entries
	// in the state map.
	enum States
	{
		ST_FLIGHT,
		ST_DESCENT,
		ST_GROUND,
		ST_MAX_STATES
	};

	// Define the state machine state functions with event data type
	STATE_DECLARE(RocketSM, 	Flight,			RocketSMData)
	EXIT_DECLARE(RocketSM, ExitFlight)
	STATE_DECLARE(RocketSM, 	Descent,		RocketSMData)
	EXIT_DECLARE(RocketSM, 	ExitDescent)
	STATE_DECLARE(RocketSM, 	Ground,			RocketSMData)


	// STATE_DECLARE(RocketSM, 	Ground,			RocketSMData)

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
		STATE_MAP_ENTRY_ALL_EX(&Flight, 0, 0, &ExitFlight)
		STATE_MAP_ENTRY_ALL_EX(&Descent, 0, 0, &ExitDescent)
		STATE_MAP_ENTRY_EX(&Ground)
	END_STATE_MAP_EX		
};

#endif