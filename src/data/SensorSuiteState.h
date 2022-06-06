#pragma once

#include "config.h"

struct SensorSuiteState
{
    uint32_t timestamp = 0;
    float mspTransducer = 0;
    float swagelockTransducer = 0;
    uint32_t digitalInputs = 0;
    uint32_t daqSampleCount = 0;
    float temp1 = 0;
    float temp2 = 0;
    float temp3 = 0;
    float temp4 = 0;
};