#pragma once

#include "data/SBGData.h"
#include "data/UOSMData.h"

//all the informations about the rocket that the state machine will need
struct sensorsData
{
    UOSMData SMData;

#if USE_SBG
    sbgData sbg;
#endif

    //#if USE_INPUT
    int inputEventNumber = -1;
    //#endif

    //#if USE_SOCKET_CONTROL
    int clientEventNumber = -1;
    //#endif
};