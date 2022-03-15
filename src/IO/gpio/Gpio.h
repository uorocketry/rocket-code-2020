#pragma once

#include "config.h"

#include "IO/IO.h"
#include "IO/gpio/DigitalOutput.h"
#include "IO/gpio/PwmOutput.h"
#include "data/GpioData.h"
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

class Gpio : public IO
{
  public:
    ~Gpio();

    void initialize() override;

    void run() override;

    bool isInitialized() override;

    void createNewGpioOutput(const std::string &name, int pinNbr);

    void createNewGpioPwmOutput(const std::string &name, int pinNbr, int safePosition, bool softPWM = false);

    GpioData setOutputs(const GpioData &data);

    GpioState getCurrentState();

  protected:
    std::mutex mutex;

  private:
    std::map<std::string, DigitalOutput> digitalOutputsMap;
    std::map<std::string, PwmOutput> pwmOutputsMap;

    struct InitFlags
    {
        InitStatus gpioSatus = INIT;
    } status;

    template <typename T, typename std::enable_if<std::is_base_of<Output, T>::value>::type * = nullptr>
    std::map<std::string, int> toRawMap(std::map<std::string, T> map);
};
