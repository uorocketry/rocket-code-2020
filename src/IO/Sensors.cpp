#include "Sensors.h"
#include <spdlog/spdlog.h>

Sensors::Sensors()
#if USE_SENSOR_MAX_31865
    : max31865("/dev/spidev0.0")
#endif
{
}

bool Sensors::isInitialized()
{
    bool init = true;

#if USE_SENSOR_MAX_31865 == 1
    init &= max31865IsInit;
#endif

    return init;
}

void Sensors::initSensors()
{
#if USE_SENSOR_MAX_31865 == 1
    if (!max31865IsInit)
    {
        max31865IsInit = max31865.begin(MAX31865::NumWires::_3WIRE);
        if (!max31865IsInit)
        {
            SPDLOG_WARN("Could not init RTD sensor. Trying again shortly...");
        }
    }
#endif
}

[[noreturn]] void Sensors::run()
{
    while (true)
    {
        if (!isInitialized())
        {
            initSensors();
            continue;
        }

#if USE_SENSOR_MAX_31865 == 1
        temperature = max31865.temperature(100, 430);
#endif

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
SensorState Sensors::getCurrentState()
{
    SensorState state;
#if USE_SENSOR_MAX_31865
    state.temperature = temperature;
#endif

    return state;
}
