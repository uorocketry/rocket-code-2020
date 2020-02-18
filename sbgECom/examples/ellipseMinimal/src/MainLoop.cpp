#include "stateMachine/stdafx.h"
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
	 
	while (true) {
		myInterface.update();
		currentState = myInterface.getLatest();
		cout << "sensor 1 :" << currentState->x << " sensor 2 : " << currentState->y << "\n";

	}


	return 0;
}
