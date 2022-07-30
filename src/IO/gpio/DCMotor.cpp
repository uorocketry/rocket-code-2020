#include "config.h"

#if USE_GPIO == 1

#include "DCMotor.h"
#include <iostream>
#include <spdlog/spdlog.h>
#include <utility>
#include <wiringSerial.h>

DCMotorOutput::DCMotorOutput(std::string name, int pinForward, int pinReverse, int motorPower, int limitSwitchMinPin,
                             int limitSwitchMaxPin, int potentiometerPin)
    : name(std::move(name)), pinNbrForward(pinForward), pinNbrReverse(pinReverse), motorPower(motorPower),
      limitSwitchMinPin(limitSwitchMinPin), limitSwitchMaxPin(limitSwitchMaxPin), potentiometerPin(potentiometerPin)
{
    logger = spdlog::default_logger();

    SPDLOG_LOGGER_DEBUG(logger, "Created PwmOutput {}", name);

#if USE_ARDUINO_PROXY == 1
    arduinoProxy = ArduinoProxy::getInstance();

    RocketryProto::ArduinoIn arduinoIn;
    arduinoIn.mutable_dcmotorinit()->set_motorforwardpin(pinForward);
    arduinoIn.mutable_dcmotorinit()->set_motorreversepin(pinReverse);
    arduinoIn.mutable_dcmotorinit()->set_motorpower(motorPower);
    arduinoIn.mutable_dcmotorinit()->set_limitswitchminpin(limitSwitchMinPin);
    arduinoIn.mutable_dcmotorinit()->set_limitswitchmaxpin(limitSwitchMaxPin);
    arduinoIn.mutable_dcmotorinit()->set_potentiometerpin(potentiometerPin);
    arduinoProxy->send(arduinoIn);
#endif
}

bool DCMotorOutput::setValue(int value)
{
    if (currentState != value)
    {
        currentState = value;
        SPDLOG_LOGGER_INFO(logger, "DC Motor {} changed to {} on pin {} and {}", name, currentState, pinNbrForward,
                           pinNbrReverse);

#if USE_ARDUINO_PROXY == 1
        RocketryProto::ArduinoIn arduinoIn;
        arduinoIn.mutable_dcmotorcontrol()->set_pinforward(pinNbrForward);
        arduinoIn.mutable_dcmotorcontrol()->set_pinreverse(pinNbrReverse);
        arduinoIn.mutable_dcmotorcontrol()->set_position(value);

        arduinoProxy->send(arduinoIn);
#endif
    }
    return true;
}

DCMotorState DCMotorOutput::getCurrentState()
{
#if USE_ARDUINO_PROXY == 1
    try
    {
        return arduinoProxy->getDCMotorState(pinNbrForward, pinNbrReverse);
    }
    catch (std::out_of_range &error)
    {
        return {-1, 0, false, false, std::chrono::steady_clock::now()};
    }
#else
    return {-1, 0, false, false, std::chrono::steady_clock::now()};
#endif
}

#endif