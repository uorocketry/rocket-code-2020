#pragma once

#include "data/SBGData.h"
#include "data/UOSMData.h"
#include "data/GpioData.h"
#include "helpers/Types.h"

//all the informations about the rocket that the state machine will need
struct sensorsData
{
    uint64_t timeStamp = 0;
    uint16_t currentStateNo = 0;
    eventType eventNumber = -1;

#if USE_SBG == 1
    sbgData sbg;
#endif

#if USE_GPIO == 1
    GpioData gpioData;
#endif

#if TESTING == 1
    bool outOfData = false;
#endif
};
