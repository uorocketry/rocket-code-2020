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
	
	rocketState *currentState = myInterface.getLatest();
	cout << currentState->x;


	return 0;
}
