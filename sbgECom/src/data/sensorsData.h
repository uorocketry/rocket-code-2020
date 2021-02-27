#pragma once

#include "data/SBGData.h"
#include "data/UOSMData.h"

//all the informations about the rocket that the state machine will need
struct sensorsData
{
    uint64_t timeStamp;
    uint16_t currentStateNo;
    int eventNumber;

#if USE_SBG
    sbgData sbg;
#endif
};
