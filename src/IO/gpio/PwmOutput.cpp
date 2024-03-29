#include "config.h"

#if USE_GPIO == 1

#include "PwmOutput.h"
#include <iostream>
#include <spdlog/spdlog.h>
#include <utility>
#include <wiringSerial.h>

#if USE_WIRING_Pi == 1

#include <softPwm.h>
#include <wiringPi.h>

#endif

PwmOutput::PwmOutput(std::string name, const int pin, const int safePosition, bool softPWM)
    : name(std::move(name)), pinNbr(pin), softPWM(softPWM), safePosition(safePosition)
{
    logger = spdlog::default_logger();

    SPDLOG_LOGGER_DEBUG(logger, "Created PwmOutput {}", name);

    if (!softPWM)
    {
#if USE_WIRING_Pi == 1
        pinMode(pinNbr, PWM_OUTPUT);
        pwmSetMode(PWM_MODE_MS);
        pwmSetRange(256);
        pwmSetClock(192);
#endif
    }
    else
    {
#if USE_ARDUINO_PROXY == 1
        arduinoProxy = ArduinoProxy::getInstance();

        RocketryProto::ArduinoIn arduinoIn;
        arduinoIn.mutable_servoinit()->set_pin(pinNbr);
        arduinoIn.mutable_servoinit()->set_safeposition(safePosition);
        arduinoProxy->send(arduinoIn);
#endif
    }
}

bool PwmOutput::setValue(int value)
{
    if (currentState != value)
    {
        currentState = value;
        SPDLOG_LOGGER_INFO(logger, "PWM {} changed to {} on pin {}", name, currentState, pinNbr);

        if (!softPWM)
        {
#if USE_WIRING_Pi == 1
            pwmWrite(pinNbr, value);
#endif
        }
        else
        {
#if USE_ARDUINO_PROXY == 1
            RocketryProto::ArduinoIn arduinoIn;
            arduinoIn.mutable_servocontrol()->set_pin(pinNbr);
            arduinoIn.mutable_servocontrol()->set_position(value);

            arduinoProxy->send(arduinoIn);
#endif
        }
    }
    return true;
}

int PwmOutput::getCurrentState()
{
#if USE_ARDUINO_PROXY == 1
    try
    {
        return arduinoProxy->getServoState(pinNbr);
    }
    catch (std::out_of_range &error)
    {
        return -1;
    }
#else
    return -1;
#endif
}

#endif