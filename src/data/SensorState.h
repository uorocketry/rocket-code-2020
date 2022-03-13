#pragma once

#include "config.h"

struct SensorState
{
#ifdef USE_SENSOR_MAX_31865
    float temperature = 0;
#endif
};