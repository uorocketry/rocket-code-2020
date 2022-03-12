#pragma once
#include "config.h"

#include "data/SensorsData.h"

#include "IO/Interface.h"
#include "IO/Radio.h"
#include "IO/SensorLogger.h"
#include "IO/TestingSensors.h"
#include "data/SensorsData.h"

class TestingInterface : public Interface
{
  public:
    TestingInterface();
    ~TestingInterface();

    void initialize() override;

    void calibrateTelemetry() override;

    // to get the latest rocket state. return a pointer to latestState
    std::shared_ptr<SensorsData> getLatest() override;

    bool updateInputs() override;
    bool updateOutputs(std::shared_ptr<SensorsData> data) override;

    void createNewGpioOutput(std::string name, int pinNbr) override;
    void createNewGpioPwmOutput(std::string name, int pinNbr, int safePosition, bool softpwm) override;

    time_point getCurrentTime() override;

  private:
    void initializeOutputs();

    EventQueue eventQueue;
    std::shared_ptr<spdlog::logger> logger;

    std::shared_ptr<SensorsData> latestState;

    TestingSensors testingSensors;

    time_point latestTime;

#if USE_LOGGER == 1
    SensorLogger sensorLogger;
#endif

#if USE_RADIO == 1
    Radio radio;
#endif
};