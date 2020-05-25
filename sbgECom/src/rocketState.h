#ifndef _ROCKETSTATE_H
#define _ROCKETSTATE_H

#include "Sensor/SBGData.h"


//all the informations about the rocket that the state machine will need 
struct rocketState {
	sbgData sbg;
	int testSensor;
};


#endif