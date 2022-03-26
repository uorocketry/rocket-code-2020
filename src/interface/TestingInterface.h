#pragma once

#include "config.h"

#include "IO/Radio.h"
#include "IO/SensorLogger.h"
#include "IO/TestingSensors.h"
#include "Interface.h"
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

    time_point getCurrentTime() override;

  private:
    void initializeOutputs();

    std::shared_ptr<spdlog::logger> logger;

    std::shared_ptr<StateData> latestState;

    TestingSensors testingSensors;

    time_point latestTime;

    SensorLogger sensorLogger;
};
