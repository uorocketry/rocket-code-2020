#pragma once

#include "config.h"
#if TESTING == 1

#include "IO/Interface.h"
#include "IO/Radio.h"
#include "IO/SensorLogger.h"
#include "IO/TestingSensors.h"
#include "data/StateData.h"
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
    std::shared_ptr<StateData> getLatest() override;

    bool updateInputs() override;
    bool updateOutputs(std::shared_ptr<StateData> data) override;

#if USE_GPIO == 1
    void createNewGpioOutput(std::string name, int pinNbr) override;
    void createNewGpioPwmOutput(std::string name, int pinNbr, int safePosition, bool softpwm) override;
#endif

#if USE_LOGGER == 1
    virtual void restartLogger() override;
#endif

    time_point getCurrentTime() override;

  private:
    void initializeOutputs();

    std::shared_ptr<spdlog::logger> logger;

    std::shared_ptr<StateData> latestState;

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