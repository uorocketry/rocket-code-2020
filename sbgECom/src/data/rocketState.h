#pragma once

#include "RocketSMData.h"
#include "../data/SBGData.h"

//all the informations about the rocket that the state machine will need 
struct rocketState {
	RocketSMData rocketSMData;
	sbgData sbg;
	int inputEventNumber = -1;
	int clientEventNumber = -1;
};