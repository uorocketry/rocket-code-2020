#include "Rocket.h"
#include <iostream>
#include <bitset>
#include "rocketState.h"

Rocket::Rocket() :
	StateMachine(ST_MAX_STATES) {
}
	
// Apogee external event
// void Rocket::Apogee(RocketSMData* data)
void Rocket::Apogee() {
	BEGIN_TRANSITION_MAP			              			// - Current State -
		TRANSITION_MAP_ENTRY (ST_DESCENT)					// ST_FLIGHT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_DESCENT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_GROUND
	END_TRANSITION_MAP(NULL)
	// END_TRANSITION_MAP(data)

	// CANNOT_HAPPEN
}

// Touchdown external event
void Rocket::Touchdown() {
	BEGIN_TRANSITION_MAP			              			// - Current State -
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_FLIGHT
		TRANSITION_MAP_ENTRY (ST_GROUND)					// ST_DESCENT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_GROUND
	END_TRANSITION_MAP(NULL)
}

// Code for each state. Do not put while in them. The right function according to the current state
// will be call in the main loop. 

// code for the flight state
STATE_DEFINE(Rocket, Flight, RocketSMData) {
	rocketInterface.update();
	rocketData = rocketInterface.getLatest();
	detectExternEvent(rocketData);

	
	std::cout << data->now.time_since_epoch().count() << "\n";
	// showInfo(rocketData);
	
}

// Exit action when WaitForDeceleration state exits.
EXIT_DEFINE(Rocket, ExitFlight) {
	std::cout << "RocketSM::ExitFlight\n";

}


ENTRY_DEFINE(Rocket, EnterDescent, RocketSMData) {
	std::cout << "RocketSM::EnterDescent\n";
	
}

// code for the Descent state
STATE_DEFINE(Rocket, Descent, RocketSMData) {
	// InternalEvent(ST_GROUND);

	rocketInterface.update();
	rocketData = rocketInterface.getLatest();

	detectExternEvent(rocketData);
	// showInfo(rocketData);

	// perform the descent processing here
	// transition to Flight via an internal event
	// InternalEvent(ST_FLIGHT);
}

// Exit action when ExitDescent state exits.
EXIT_DEFINE(Rocket, ExitDescent) {
	std::cout << "RocketSM::ExitDescent\n";
}

// Entry action when ExitDescent state exits.
ENTRY_DEFINE(Rocket, EnterGround, RocketSMData) {
	std::cout << "RocketSM::EnterGround\n";
}

// code for the ground state
STATE_DEFINE(Rocket, Ground, RocketSMData) {
	rocketInterface.update();
	rocketData = rocketInterface.getLatest();

	detectExternEvent(rocketData);
	// showInfo(rocketData);

}


void Rocket::detectExternEvent(const rocketState* data) {
	int eventNbr = data->inputEventNumber;
	switch (eventNbr)
	{
	case 0:
		Apogee();
		break;
	case 1:
		Touchdown();
		break;
	default:
		break;
	}
}

void Rocket::showInfo(const rocketState* data) {
	printf("Barometer: %f\tGps: longitude %f\t latitude %f\t altitude %f\t Velocity: N %f\tE %f\tD %f\tSolutionStatus %d\t%d\n",
		data->sbg.barometricAltitude,
		data->sbg.gpsLatitude, data->sbg.gpsLongitude, data->sbg.gpsAltitude,
		data->sbg.velocityN, data->sbg.velocityE, data->sbg.velocityD,
		data->sbg.solutionStatus,
		(data->sbg.solutionStatus) & 0b1111
		);
	// std::cout << std::bitset<32>(data->sbg.solutionStatus) << "\n";
}

void Rocket::updateRocket(RocketSMData* data) {
	ExecuteCurrentState(data);
}