#include "Rocket.h"
#include <iostream>
#include <bitset>

using namespace std;

Rocket::Rocket() :
	StateMachine(ST_MAX_STATES),
	m_currentSpeed(0)
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
	// printf("Angle: X %f\tY %f\tZ %f\tbarometerAltitude %f\tvelocityN %f\tvelocityE %f\tvelocityD %f\n", 
	// 	data->data->sbg.Xangle, data->data->sbg.Yangle, data->data->sbg.Zangle, 
	// 	data->data->sbg.barometricAltitude, 
	// 	// data->data->sbg.filteredXacc, data->data->sbg.filteredYacc, data->data->sbg.filteredZacc
	// 	data->data->sbg.velocityN, data->data->sbg.velocityE, data->data->sbg.velocityD
	// 	);
	showInfo(data);
}

// code for the Descent state
STATE_DEFINE(Rocket, Descent, RocketSMData)
{

	// printf("Angle: X %f\tY %f\tZ %f\tbarometerAltitude %f\tvelocityN %f\tvelocityE %f\tvelocityD %f\n", 
	// 	data->data->sbg.Xangle, data->data->sbg.Yangle, data->data->sbg.Zangle, 
	// 	data->data->sbg.barometricAltitude, 
	// 	// data->data->sbg.filteredXacc, data->data->sbg.filteredYacc, data->data->sbg.filteredZacc
	// 	data->data->sbg.velocityN, data->data->sbg.velocityE, data->data->sbg.velocityD
	// 	);
	
	showInfo(data);
	// perform the descent processing here
	// transition to Flight via an internal event
	// InternalEvent(ST_FLIGHT);
}

// STATE_DEFINE(RocketSM, Ground, RocketSMData)

// code for the ground state
STATE_DEFINE(Rocket, Ground, RocketSMData)
{

	// printf("Angle: X %f\tY %f\tZ %f\tbarometerAltitude %f\tvelocityN %f\tvelocityE %f\tvelocityD %f\n", 
	// 	data->data->sbg.Xangle, data->data->sbg.Yangle, data->data->sbg.Zangle, 
	// 	data->data->sbg.barometricAltitude, 
	// 	// data->data->sbg.filteredXacc, data->data->sbg.filteredYacc, data->data->sbg.filteredZacc
	// 	data->data->sbg.velocityN, data->data->sbg.velocityE, data->data->sbg.velocityD
	// 	);
	showInfo(data);

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
	printf("Barometer: %f\tGps: longitude %f\t latitude %f\t altitude %f\t Velocity: N %f\tE %f\tD %f\tSolutionStatus %d\t%d\t%d\t%d\t",
		data->data->sbg.barometricAltitude,
		data->data->sbg.gpsLatitude, data->data->sbg.gpsLongitude, data->data->sbg.gpsAltitude,
		data->data->sbg.velocityN, data->data->sbg.velocityE, data->data->sbg.velocityD,
		data->data->sbg.solutionStatus,
		(data->data->sbg.solutionStatus) & 0b1111,
		(get_bits(data->data->sbg.solutionStatus, 28)[10]),
		(get_bits(data->data->sbg.solutionStatus, 28)[11])
		);
	cout << bitset<32>(data->data->sbg.solutionStatus);
	printf("\n");
}

int* Rocket::get_bits(int n, int bitswanted){
  int *bits = (int*)malloc(sizeof(int) * bitswanted);

  int k;
  for(k=0; k<bitswanted; k++){
    int mask =  1 << k;
    int masked_n = n & mask;
    int thebit = masked_n >> k;
    bits[k] = thebit;
  }

  return bits;
}

