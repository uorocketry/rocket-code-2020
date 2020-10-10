#include "Rocket.h"
#include <iostream>
#include <bitset>
#include "../data/rocketState.h"
#include <math.h>

#define PI 3.14159265

Rocket::Rocket() :
	StateMachine(ST_MAX_STATES) {

	// There is no state entry function for the first state
	StateMachine::enterNewState(States(0));
}
	
// Start external event
void Rocket::Start() {
	BEGIN_TRANSITION_MAP			              			// - Current State -
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_INIT
		TRANSITION_MAP_ENTRY (ST_FLIGHT)					// ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_FLIGHT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_DESCENT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_GROUND
	END_TRANSITION_MAP(NULL)
}

// Apogee external event
// void Rocket::Apogee(RocketSMData* data)
void Rocket::Apogee() {
	BEGIN_TRANSITION_MAP			              			// - Current State -
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_INIT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_WAIT_FOR_INIT
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
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_INIT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_FLIGHT
		TRANSITION_MAP_ENTRY (ST_GROUND)					// ST_DESCENT
		TRANSITION_MAP_ENTRY (EVENT_IGNORED)				// ST_GROUND
	END_TRANSITION_MAP(NULL)
}

// Code for each state. Do not put while in them. The right function according to the current state
// will be call in the main loop. 

// code for the initialization state
STATE_DEFINE(Rocket, Init, RocketSMData) {
	rocketInterface.initializeSensors();

	InternalEvent(ST_WAIT_FOR_INIT);

}

EXIT_DEFINE(Rocket, ExitInit) {
	std::cout << "RocketSM::ExitInit\n";

}

ENTRY_DEFINE(Rocket, EnterWaitForInit, RocketSMData) {
	enterNewState(ST_WAIT_FOR_INIT);

	std::cout << "RocketSM::EnterWaitForInit\n";
	
}

// code for the wait for initialization state
STATE_DEFINE(Rocket, WaitForInit, RocketSMData) {
	rocketInterface.update(data);
	rocketData = rocketInterface.getLatest();

	if (rocketInterface.sensorsInitialized())
		InternalEvent(ST_FLIGHT);
	
	// showInfo(rocketData);
}

EXIT_DEFINE(Rocket, ExitWaitForInit) {
	std::cout << "RocketSM::ExitWaitForInit\n";

}

ENTRY_DEFINE(Rocket, EnterFlight, RocketSMData) {
	enterNewState(ST_FLIGHT);

	std::cout << "RocketSM::EnterFlight\n";
}

// code for the flight state
STATE_DEFINE(Rocket, Flight, RocketSMData) {
	rocketInterface.update(data);
	rocketData = rocketInterface.getLatest();

	// TODO: move detect Apogee to coast state when new states are added 
	detectApogee(rocketData);

	detectExternEvent(rocketData);

	// showInfo(rocketData);
}

// Exit action when WaitForDeceleration state exits.
EXIT_DEFINE(Rocket, ExitFlight) {
	std::cout << "RocketSM::ExitFlight\n";

}

ENTRY_DEFINE(Rocket, EnterDescent, RocketSMData) {
	enterNewState(ST_DESCENT);

	std::cout << "RocketSM::EnterDescent\n";
	
}

// code for the Descent state
STATE_DEFINE(Rocket, Descent, RocketSMData) {
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
EXIT_DEFINE(Rocket, ExitDescent) {
	std::cout << "RocketSM::ExitDescent\n";
}

// Entry action when ExitDescent state exits.
ENTRY_DEFINE(Rocket, EnterGround, RocketSMData) {
	enterNewState(ST_GROUND);
	
	std::cout << "RocketSM::EnterGround\n";
}

// code for the ground state
STATE_DEFINE(Rocket, Ground, RocketSMData) {
	rocketInterface.update(data);
	rocketData = rocketInterface.getLatest();

	detectExternEvent(rocketData);
	// showInfo(rocketData);

}


void Rocket::detectExternEvent(const rocketState* data) {
	int eventNbr = data->inputEventNumber;
	switch (eventNbr) {
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

#ifndef NO_SOCKET_CONTROL
	eventNbr = data->clientEventNumber;
	switch (eventNbr) {
		case 0:
			Apogee();
			break;
		case 1:
			Touchdown();
			break;
		default:
			break;
	}
#endif

}

void Rocket::detectApogee(const rocketState* data) {
	// TODO: only check for apogee x seconds after launch 
	// Euler angle
	// pitch is Yangle 
	static uint8_t consecutiveEvents = 0; 

	float Yangle = (180/PI)*(acos(cos(data->sbg.Xangle*(PI/180))*cos(data->sbg.Yangle*(PI/180))));
	
	if( Yangle >= 45) {
		consecutiveEvents++;
	}
	else {
		consecutiveEvents = 0;
	}

	// trigger appogee if the sbg detects "ApogeeThreshold" number of consecutive times 
	// that the rocket is pointing downwards and falling
	if(consecutiveEvents >= ApogeeThreshold) {
		std::cout << "Apogee \n";
		Apogee();
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

void Rocket::enterNewState(States state) {
	StateMachine::enterNewState(state);
}