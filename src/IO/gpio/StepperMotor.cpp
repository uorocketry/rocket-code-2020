#include "config.h"

#if USE_GPIO == 1

#include "StepperMotor.h"
#include <iostream>
#include <spdlog/spdlog.h>
#include <utility>

StepperMotor::StepperMotor()
{
    logger = spdlog::default_logger();
}

bool StepperMotor::setValue(int value)
{
    if (currentState != value)
    {
        currentState = value;
        SPDLOG_LOGGER_INFO(logger, "Stepper Motor Purge changed to {}", currentState);

#if USE_ARDUINO_PROXY == 1
        RocketryProto::ArduinoIn arduinoIn;
        arduinoIn.mutable_steppermotorcontrol()->set_speed(value);

        arduinoProxy->send(arduinoIn);
#endif
    }
    return true;
}

StepperMotorState StepperMotor::getCurrentState()
{
#if USE_ARDUINO_PROXY == 1
    try
    {
        // Hardcoded the pin for now;
        return arduinoProxy->getStepperMotorState();
    }
    catch (std::out_of_range &error)
    {
        return {0, 0, false, false, 0, std::chrono::steady_clock::now()};
    }
#else
    return {-1, 0, false, false, 0, std::chrono::steady_clock::now()};
#endif
}

#endif