#pragma once

#include "IO.h"
#include "config.h"
#include "data/SensorState.h"
#include <sensors/MAX31865.h>

class Sensors : public IO
{
  public:
    Sensors();

    [[noreturn]] void run() override;
    bool isInitialized() override;
    SensorState getCurrentState();

  private:
#if USE_SENSOR_MAX_31865 == 1
    // MAX31865 RTD
    MAX31865 max31865;
    bool max31865IsInit = false;
    std::atomic<float> temperature = {0};
#endif

    void initSensors();
};
