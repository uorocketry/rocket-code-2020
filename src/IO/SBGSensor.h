#pragma once

#include "config.h"

// sbgECom headers
#include <sbgCommon.h>
#include <sbgEComLib.h>

#include "../data/SBGData.h"
#include "IO.h"
#include <ctime>

class SBGSensor : public IO
{
  public:
    void run() override;
    void initialize() override;
    void setZeroBarometricAltitude();
    bool isInitialized() override;

    sbgData getData();
    friend SbgErrorCode onLogReceived(SbgEComHandle *pHandle, SbgEComClass msgClass, SbgEComMsgId msg,
                                      const SbgBinaryLogData *pLogData, void *pUserArg);

  private:
    sbgData data;
    float barometricAltitudeOffset = 0;

    struct InitFlags
    {
    } status;
};
