#pragma once

#include "IO.h"
#include "data/SensorSuiteState.h"
#include <boost/asio.hpp>

class SensorSuite : public IO
{
  public:
    SensorSuite();

    void initialize() override;

    void run() override;
    bool isInitialized() override;

    SensorSuiteState getCurrentData();

  private:
    boost::asio::io_context io_context;

    std::vector<std::string> latestOne;
    std::vector<std::string> latestTwo;

    std::thread secondConnectionThread;

    void startListening(std::string host, int port, int index);
    void runSecondListener();

    void connect(boost::asio::ip::tcp::socket &socket, boost::asio::ip::tcp::endpoint &endpoint);
};
