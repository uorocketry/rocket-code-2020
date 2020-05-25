#include "Rocket.h"
#include <iostream>
#include <bitset>

using namespace std;

Rocket::Rocket() :
	StateMachine(ST_MAX_STATES)
{
}
	
// Apogee external event
// void Rocket::Apogee(RocketSMData* data)
void Rocket::Apogee()
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
void Rocket::Touchdown()
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
STATE_DEFINE(Rocket, Flight, RocketSMData)
{
	// showInfo(data);
	std::cout << "Flight \n";
	InternalEvent(ST_DESCENT);
}

// code for the Descent state
STATE_DEFINE(Rocket, Descent, RocketSMData)
{
	// showInfo(data);
	std::cout << "Descent \n";
	InternalEvent(ST_GROUND);

	// perform the descent processing here
	// transition to Flight via an internal event
	// InternalEvent(ST_FLIGHT);
}

// STATE_DEFINE(RocketSM, Ground, RocketSMData)

// code for the ground state
STATE_DEFINE(Rocket, Ground, RocketSMData)
{
	// std::cout << "Ground \n";
	// showInfo(data);

}

// Exit action when WaitForDeceleration state exits.
EXIT_DEFINE(Rocket, ExitFlight)
{
	cout << "RocketSM::ExitFlight" << endl;

}

// Exit action when WaitForDeceleration state exits.
EXIT_DEFINE(Rocket, ExitDescent)
{
	cout << "RocketSM::ExitDescent" << endl;

}


void Rocket::showInfo(const RocketSMData* data) {
	printf("Barometer: %f\tGps: longitude %f\t latitude %f\t altitude %f\t Velocity: N %f\tE %f\tD %f\tSolutionStatus %d\t%d",
		data->data->sbg.barometricAltitude,
		data->data->sbg.gpsLatitude, data->data->sbg.gpsLongitude, data->data->sbg.gpsAltitude,
		data->data->sbg.velocityN, data->data->sbg.velocityE, data->data->sbg.velocityD,
		data->data->sbg.solutionStatus,
		(data->data->sbg.solutionStatus) & 0b1111
		);
	cout << bitset<32>(data->data->sbg.solutionStatus);
	printf("\n");
}

void Rocket::updateRocket() {
	
	ExecuteCurrentState(NULL);
}