#pragma once

#include "config.h"

struct SensorSuiteState
{
    float msp2Transducer = 0;
    float swagelockTransducer = 0;
    float tankTransducer = 0;
    float thrustTransducer = 0;
    uint32_t digitalInputs = 0;
    uint32_t daqSampleCount = 0;
    float temp1 = 0;
    float temp2 = 0;
    float temp3 = 0;
    float temp4 = 0;
    float temp5 = 0;
    float temp6 = 0;
    float temp7 = 0;
    float temp8 = 0;
    uint32_t timestamp = 0;
};