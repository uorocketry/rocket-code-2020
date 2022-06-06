#pragma once

#include "IO.h"
#include "data/SensorSuiteState.h"
#include <boost/asio.hpp>

class SensorSuite : public IO
{
  public:
    SensorSuite();

    void initialize() override
    {
    }

    [[noreturn]] void run() override;
    bool isInitialized() override;

    SensorSuiteState getCurrentData();

  private:
    boost::asio::io_context io_context;

    std::vector<std::string> latest;
};
