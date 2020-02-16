#include "stateMachine/stdafx.h"
#include "RocketSM.h"
#include"ReadSensors.h"
#include "Interface.h"
#include <iostream>

using namespace std;

int main(void)
{
	Interface myInterface;

	myInterface.initializeSensors();
	


	return 0;
}
