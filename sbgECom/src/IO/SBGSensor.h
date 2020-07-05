#ifndef _SBGSENSOR_H
#define _SBGSENSOR_H

#include "IO.h"
#include "SBGData.h"

#include <sbgEComLib.h>
#include <time.h>

class SBGSensor : public IO
{
public:
	void run();
	void initialize();
	sbgData getData();
	friend SbgErrorCode onLogReceived(SbgEComHandle *pHandle, SbgEComClass msgClass, SbgEComMsgId msg, const SbgBinaryLogData *pLogData, void *pUserArg);
private:
	sbgData data{0,0,0,0,0,0,0,0,0,0,0,0,0};

};

#endif