#include "stateMachine/stdafx.h"
#include "RocketSM.h"


#include<thread>
#include<chrono>
#include<unordered_map>
#include"ReadSensors.h"

#include <iostream>
using namespace std;
#include "Interface.h"

using namespace std;

int main(void)
{
	Interface myInterface;

	myInterface.initializeSensors();
	


	return 0;
}
