#ifndef _SBGSENSOR_H
#define _SBGSENSOR_H

#include "Sensor.h"
#include "SBGData.h"

#include <sbgEComLib.h>
#include <time.h>

class SBGSensor : public Sensor
{
public:
	void run();
	void initialize();
	sbgData getData();
	friend SbgErrorCode onLogReceived(SbgEComHandle *pHandle, SbgEComClass msgClass, SbgEComMsgId msg, const SbgBinaryLogData *pLogData, void *pUserArg);

	#ifdef TESTING
	void setData(int index, const char* data);
	std::string getDataLabel();
	#endif
private:
	sbgData data{0,0,0,0,0,0,0,0,0,0,0,0,0};

	#ifdef TESTING
	// Used by the random number generator to construct realistic data
	sbgData minDataRange{ 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	sbgData maxDataRange{ 100,100,100,100,100,100,100,100,100,100,100,100,100 };
	#endif

};

#endif