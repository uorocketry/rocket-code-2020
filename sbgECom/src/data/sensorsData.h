#pragma once

#include "data/SBGData.h"
#include "data/UOSMData.h"
#include "helpers/Types.h"

//all the informations about the rocket that the state machine will need
struct sensorsData
{
    uint64_t timeStamp;
    uint16_t currentStateNo;
    eventType eventNumber;

#if USE_SBG
    sbgData sbg;
#endif
};
