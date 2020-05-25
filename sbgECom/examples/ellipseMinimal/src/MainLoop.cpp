#include "stateMachine/stdafx.h"
#include "stateMachine/StateMachine.h"
#include "Rocket.h"
#include"ReadSensors.h"
#include "Interface.h"
#include "rocketState.h"
#include <iostream>

using namespace std;

int main()
{
	Interface myInterface;

	// myInterface.initializeSensors();
	
	rocketState *currentState;

	Rocket Rocket;
	 
	while (true) {
		myInterface.update();
		currentState = myInterface.getLatest();

		if (currentState->sbg.Xangle >= 30) {
			Rocket.Apogee();
			// cout << "Apogee";
		}


		if (currentState->sbg.Xangle >= 60) {
			Rocket.Touchdown();
		}
		
		RocketSMData data;
		data.data = currentState;
		EventData* dataPtr = &data;
		Rocket.ExecuteCurrentState(dataPtr);
	}


	return 0;
}
