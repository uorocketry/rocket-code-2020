#pragma once

#include "IO/SBGData.h"


//all the informations about the rocket that the state machine will need 
struct rocketState {
	sbgData sbg;
	int testSensor;
};