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

	myInterface.initializeSensors();
	
	while (true) {
		rocketState *currentState = myInterface.getLatest();
		cout << currentState->x << "\n";

	}


	return 0;
}
