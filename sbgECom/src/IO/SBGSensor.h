#pragma once

#include "config/config.h"
#if USE_SBG

#include "IO.h"
#include "../data/SBGData.h"

#include <../common/sbgEComLib.h>
#include <time.h>

class SBGSensor : public IO
{
public:
	void run();
	void initialize();
	void setZeroBarometricAltitude();
	bool isInitialized();

	sbgData getData();
	friend SbgErrorCode onLogReceived(SbgEComHandle *pHandle, SbgEComClass msgClass, SbgEComMsgId msg, const SbgBinaryLogData *pLogData, void *pUserArg);

private:
	sbgData data{0,0,0,0,0,0,0,0,0,0,0,0,0};
	float barometricAltitudeOffset = 0;

	struct InitFlags
	{
		
	} status;
};

#endif