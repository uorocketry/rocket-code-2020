#pragma once

#include "config.h"

#include "../data/SBGData.h"
#include "IO.h"
#include "data/StateData.h"
#include <iostream>
#include <queue>

class TestingSensors : public IO
{
  public:
    void run() override;
    void initialize() override;
    bool isInitialized() override;

    StateData getLatest();

  private:
    std::queue<StateData> data;
};
