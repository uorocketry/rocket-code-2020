#include "RocketSM.h"
#include <iostream>

using namespace std;

RocketSM::RocketSM() :
	StateMachine(ST_MAX_STATES),
	m_currentSpeed(0)
{
}
	
// Apogee external event
// void RocketSM::Apogee(RocketSMData* data)
void RocketSM::Apogee()
{
	BEGIN_TRANSITION_MAP			              			// - Current State -
		TRANSITION_MAP_ENTRY (ST_DESCENT)					// ST_FLIGHT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_DESCENT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_GROUND
	END_TRANSITION_MAP(NULL)
	// END_TRANSITION_MAP(data)

	// CANNOT_HAPPEN
}

// Touchdown external event
void RocketSM::Touchdown()
{
	BEGIN_TRANSITION_MAP			              			// - Current State -
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_FLIGHT
		TRANSITION_MAP_ENTRY (ST_GROUND)					// ST_DESCENT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_GROUND
	END_TRANSITION_MAP(NULL)
}

// Code for each state. Do not put while in them. The right function according to the current state
// will be call in the main loop. 

// code for the flight state
STATE_DEFINE(RocketSM, Flight, NoEventData)
{
	cout << "RocketSM::ST_Flight" << endl;
}

// code for the Descent state
STATE_DEFINE(RocketSM, Descent, NoEventData)
{
	cout << "RocketSM::ST_Descent" << endl;
	// m_currentSpeed = 0; 

	// perform the descent processing here
	// transition to Flight via an internal event
	// InternalEvent(ST_FLIGHT);
}

// STATE_DEFINE(RocketSM, Ground, RocketSMData)

// code for the ground state
STATE_DEFINE(RocketSM, Ground, NoEventData)
{
	// cout << "RocketSM::ST_Ground : Speed is " << data->speed << endl;
	cout << "RocketSM::ST_Ground" << endl;

	// m_currentSpeed = data->speed;

}

// Exit action when WaitForDeceleration state exits.
EXIT_DEFINE(RocketSM, ExitFlight)
{
	cout << "RocketSM::ExitFlight" << endl;

}

// Exit action when WaitForDeceleration state exits.
EXIT_DEFINE(RocketSM, ExitDescent)
{
	cout << "RocketSM::ExitDescent" << endl;

}
