#pragma once

#include "config/config.h"
#if TESTING == 1

#include "data/sensorsData.h"

#include "IO/Interface.h"
#include "IO/Radio.h"
#include "IO/SensorLogger.h"
#include "IO/TestingSensors.h"
#include "data/sensorsData.h"
#include <queue>
#include <string>

class TestingInterface : public Interface
{
  public:
    TestingInterface();
    ~TestingInterface();

    void initialize() override;

    void calibrateTelemetry() override;

    // to get the latest rocket state. return a pointer to latestState
    std::shared_ptr<sensorsData> getLatest() override;

    bool updateInputs() override;
    bool updateOutputs(std::shared_ptr<sensorsData> data) override;

#if USE_GPIO == 1
    void createNewGpioOutput(std::string name, int pinNbr) override;
    void createNewGpioPwmOutput(std::string name, int pinNbr, int safePosition, bool softpwm) override;
#endif

    time_point getCurrentTime() override;

  private:
    void initializeOutputs();

    std::shared_ptr<spdlog::logger> logger;

    std::shared_ptr<sensorsData> latestState;

    TestingSensors testingSensors;

    time_point latestTime;

#if USE_LOGGER == 1
    SensorLogger sensorLogger;
#endif

#if USE_RADIO == 1
    Radio radio;
#endif
};

#endif