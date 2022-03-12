#include "common/pch.h"
#include "config.h"

#include "./DigitalOutput.h"
#include <iostream>

DigitalOutput::DigitalOutput(const std::string &name, const int pin) : name(name), pinNbr(pin)
{
    logger = spdlog::default_logger();

    SPDLOG_LOGGER_DEBUG(logger, "Created Output {}", name);

#if USE_ARDUINO_PROXY == 1
    arduinoProxy = ArduinoProxy::getInstance();

    RocketryProto::ArduinoIn arduinoIn;
    arduinoIn.mutable_digitalinit()->set_pin(pin);
    arduinoProxy->send(arduinoIn);
#elif USE_WIRING_Pi == 1
    pinMode(pinNbr, OUTPUT);
#endif
}

bool DigitalOutput::setValue(int value)
{
    if (currentState != value)
    {
        currentState = value;
        SPDLOG_LOGGER_INFO(logger, "OUT {} changed to {}", name, currentState);

#if USE_ARDUINO_PROXY == 1
        RocketryProto::ArduinoIn arduinoIn;
        arduinoIn.mutable_digitalcontrol()->set_pin(pinNbr);
        arduinoIn.mutable_digitalcontrol()->set_activate(value == 1);

        arduinoProxy->send(arduinoIn);
#elif USE_WIRING_Pi == 1
        digitalWrite(pinNbr, value);
#endif
    }
    return true;
}

int DigitalOutput::getCurrentState()
{
#if USE_ARDUINO_PROXY == 1
    try
    {
        return arduinoProxy->getDigitalState(pinNbr);
    }
    catch (std::out_of_range &error)
    {
        return -1;
    }
#else
    return -1;
#endif
}
