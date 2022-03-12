#include "Gpio.h"
#include "config.h"
#include "data/SensorsData.h"

Gpio::~Gpio() = default;

void Gpio::run()
{
}

void Gpio::initialize()
{

#if USE_WIRING_Pi == 1
    status.gpioSatus = (wiringPiSetupGpio() == 0) ? READY : INIT;
#else
    status.gpioSatus = READY;
#endif
    // init servos

    createThread = false;
    IO::initialize();
}

bool Gpio::isInitialized()
{
    return (status.gpioSatus == READY);
}

GpioData Gpio::setOutputs(const GpioData &data)
{
    for (std::pair<std::string, int> output : data.pwmMap)
    {
        pwmOutputsMap.at(output.first).setValue(output.second);
    }
    for (std::pair<std::string, int> output : data.digitalMap)
    {
        digitalOutputsMap.at(output.first).setValue(output.second);
    }

    GpioData result;
    result.digitalMap = toRawMap(digitalOutputsMap);
    result.pwmMap = toRawMap(pwmOutputsMap);

    return result;
}

void Gpio::createNewGpioOutput(const std::string &name, int pinNbr)
{
    digitalOutputsMap.insert({name, DigitalOutput(name, pinNbr)});
}

void Gpio::createNewGpioPwmOutput(const std::string &name, int pinNbr, int safePosition, bool softPWM)
{
    pwmOutputsMap.insert({name, PwmOutput(name, pinNbr, safePosition, softPWM)});
}

GpioData Gpio::getCurrentState()
{
    GpioData state;

    for (auto i : digitalOutputsMap)
    {
        state.digitalMap.insert({i.first, i.second.getCurrentState()});
    }
    for (auto i : pwmOutputsMap)
    {
        state.pwmMap.insert({i.first, i.second.getCurrentState()});
    }

    return state;
}

/**
 * Convert a map with Output to a map with numbers
 */
template <typename T, typename std::enable_if<std::is_base_of<Output, T>::value>::type *>
std::map<std::string, int> Gpio::toRawMap(std::map<std::string, T> map)
{
    std::map<std::string, int> result;
    for (std::pair<const std::string, T> output : map)
    {
        result.insert({output.first, output.second.getValue()});
    }

    return result;
}