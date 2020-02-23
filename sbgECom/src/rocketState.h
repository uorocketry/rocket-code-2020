#ifndef _ROCKETSTATE_H
#define _ROCKETSTATE_H


//all the informations about the rocket that the state machine will need 
struct rocketState {
	float Xangle;
	float Yangle;
	float Zangle;
	int testSensor;
};

#endif