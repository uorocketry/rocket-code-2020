#include "stateMachine/stdafx.h"
#include "stateMachine/StateMachine.h"
#include "RocketSM.h"
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

	RocketSM RocketSM;
	 
	while (true) {
		myInterface.update();
		currentState = myInterface.getLatest();

		if (currentState->sbg.Xangle >= 30) {
			RocketSM.Apogee();
			// cout << "Apogee";
		}


		if (currentState->sbg.Xangle >= 60) {
			RocketSM.Touchdown();
		}
		
		RocketSMData data;
		data.data = currentState;
		EventData* dataPtr = &data;
		RocketSM.ExecuteCurrentState(dataPtr);
	}


	return 0;
}
