#pragma once

#include "../stateMachineLib/StateMachine.h"
#include "../data/rocketState.h"
#include "../data/RocketSMData.h"
#include "../Interface.h"
#include "../helpers/Types.h"

class Rocket : public StateMachine
{
public:
	Rocket();

	// External events taken by this state machine
	// void Apogee(RocketSMData* data);
	void Apogee();
	void Touchdown();

private:
	void detectExternEvent(const rocketState* data);
	void showInfo(const rocketState* data);

	Interface rocketInterface;
	rocketState* rocketData;

	// State enumeration order must match the order of state method entries
	// in the state map.
	enum States
	{
		ST_FLIGHT,
		ST_DESCENT,
		ST_GROUND,
		ST_MAX_STATES
	};

	void enterNewState(States state);

	// Define the state machine state functions with event data type
	STATE_DECLARE(Rocket, 	Flight,			RocketSMData)
	EXIT_DECLARE(Rocket, ExitFlight)
	STATE_DECLARE(Rocket, 	Descent,		RocketSMData)
	ENTRY_DECLARE(Rocket, EnterDescent, RocketSMData)
	EXIT_DECLARE(Rocket, 	ExitDescent)
	STATE_DECLARE(Rocket, 	Ground,			RocketSMData)
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
		STATE_MAP_ENTRY_ALL_EX(&Flight, 0, 0, &ExitFlight)
		STATE_MAP_ENTRY_ALL_EX(&Descent, 0, &EnterDescent, &ExitDescent)
		STATE_MAP_ENTRY_ALL_EX(&Ground, 0, &EnterGround, 0)
	END_STATE_MAP_EX
};