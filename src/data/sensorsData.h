#pragma once

#include "data/SBGData.h"
#include "data/UOSMData.h"
#include "helpers/Types.h"

//all the informations about the rocket that the state machine will need
struct sensorsData
{
    uint64_t timeStamp = -1;
    uint16_t currentStateNo = -1;
    eventType eventNumber = -1;

#if USE_SBG
    sbgData sbg;
#endif

#if TESTING
    bool outOfData = false;
#endif

#if USE_RADIO
    int radioEventNumber = -1;
#endif

#if USE_SOCKET_CLIENT
    int clientEventNumber = -1;
#endif
};
