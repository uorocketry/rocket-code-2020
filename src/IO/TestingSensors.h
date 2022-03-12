#pragma once
#include "config.h"

#include "IO.h"
#include "data/SBGData.h"
#include "data/SensorsData.h"

class TestingSensors : public IO
{
  public:
    void run() override;
    void initialize() override;
    bool isInitialized() override;

    SensorsData getLatest();

  private:
    std::queue<SensorsData> data;
};
