#pragma once
#include "config/config.h"

struct GpioData {
    #if VAVLE1
        bool valve1Status = false;
    #endif
    #if VALVE2
    bool valve2Status = false;
    #endif
   
};