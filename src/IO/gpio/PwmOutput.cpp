#include "config/config.h"

#if USE_GPIO == 1

#include "PwmOutput.h"
#include <iostream>
#include <utility>
#include <spdlog/spdlog.h>
#include <wiringSerial.h>

#if USE_WIRING_Pi == 1

#include <wiringPi.h>
#include <softPwm.h>

#endif

PwmOutput::PwmOutput(std::string name, const int pin, const int safePosition, bool softPWM) : name(std::move(name)), pinNbr(pin), softPWM(softPWM), safePosition(safePosition)
{
    logger = spdlog::default_logger();

    SPDLOG_LOGGER_DEBUG(logger, "Created PwmOutput {}", name);

    if (!softPWM) {
#if USE_WIRING_Pi == 1
        pinMode(pinNbr, PWM_OUTPUT);
        pwmSetMode(PWM_MODE_MS);
        pwmSetRange(256);
        pwmSetClock(192);
#endif
    } else {
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
    if (currentState != value) {
        currentState = value;
        SPDLOG_LOGGER_INFO(logger, "PWM {} changed to {} on pin {}", name, currentState, pinNbr);

        if (!softPWM) {
#if USE_WIRING_Pi == 1
            pwmWrite(pinNbr, value);
#endif
        } else {
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

#endif