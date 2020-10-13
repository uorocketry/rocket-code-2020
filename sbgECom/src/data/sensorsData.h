#pragma once

#include "../data/SBGData.h"
#include "../data/HotFireSMData.h"
#include "../data/RocketSMData.h"

//all the informations about the rocket that the state machine will need
struct sensorsData
{
#ifdef HOTFIRE_TEST
    HotFireSMData SMData;
#else
    RocketSMData SMData;
#endif

#if USE_SBG
    sbgData sbg;
#endif
#if USE_INPUT
    int inputEventNumber = -1;
#endif
#if USE_SOCKET_CONTROL
    int clientEventNumber = -1;
#endif
};