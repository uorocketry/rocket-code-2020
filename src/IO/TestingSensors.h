#pragma once

#include "config.h"
#if TESTING == 1

#include "../data/SBGData.h"
#include "IO.h"
#include "data/sensorsData.h"
#include <iostream>
#include <queue>

class TestingSensors : public IO
{
  public:
    void run() override;
    void initialize() override;
    bool isInitialized() override;

    sensorsData getLatest();

  private:
    std::queue<sensorsData> data;
};

#endif