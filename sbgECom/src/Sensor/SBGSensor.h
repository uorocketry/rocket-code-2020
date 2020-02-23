#ifndef _SBGSENSOR_H
#define _SBGSENSOR_H

#include "Sensor.h"

#include <sbgEComLib.h>
#include <time.h>

class SBGSensor : public Sensor
{
public:
	void run();
	void initialize();
	float getValue();
	void changeValue(float v);
	friend SbgErrorCode onLogReceived(SbgEComHandle *pHandle, SbgEComClass msgClass, SbgEComMsgId msg, const SbgBinaryLogData *pLogData, void *pUserArg);
private:
	float sensorValue = 0.;
};

#endif