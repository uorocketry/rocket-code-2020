#include "stdafx.h"
#include "RocketSM.h"

#include <iostream>
using namespace std;

int main(void)
{
	// Create MotorNM (No Macro) test object
	// @see StateMachine.h comments
	bool terminate = false;

	while (! terminate) {
		terminate = true;
		
		// Create Motor object with macro support
		RocketSM RocketSM;
		cout << (int)RocketSM.GetCurrentState() << endl;

		// RocketSMData* data = new RocketSMData();
		// data->speed = 100;
		// RocketSM.Apogee(data);


		RocketSM.Apogee();
		cout << (int)RocketSM.GetCurrentState() << endl;


		// RocketSMData* data2 = new RocketSMData();
		// data2->speed = 200;
		// RocketSM.Apogee(data2);

		RocketSM.Touchdown();
		cout << (int)RocketSM.GetCurrentState() << endl;
	}


	return 0;
}