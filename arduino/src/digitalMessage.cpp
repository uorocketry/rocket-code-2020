#include "digitalMessage.h"
#include "Arduino.h"
#include "utils.h"

// Servo Information
constexpr int maxDigitalPins = 20;
uint8_t enabledDigitalPins[maxDigitalPins];
uint16_t digitalCount = 0;

void controlDigital(uint8_t pin, bool activate)
{
    if (!arrayContains(enabledDigitalPins, digitalCount, pin))
    {
        serialPrintLn("Digital pin ", pin, " is not initialized. Ignoring request.");
        return;
    }

    serialPrintLn("Digital control: pin: ", pin, ", activate: ", activate);

    digitalWrite(pin, activate);
}

void initDigital(const RocketryProto_DigitalInit &digitalInit)
{
    uint8_t pin = digitalInit.pin;

    if (!arrayContains(enabledDigitalPins, digitalCount, pin))
    {
        // Ignore if we don't have any more free servos
        if (maxDigitalPins == digitalCount)
        {
            return;
        }

        pinMode(pin, OUTPUT);

        enabledDigitalPins[digitalCount] = pin;
        digitalCount++;

        serialPrintLn("Digital init: pin: ", pin);
    }
    else
    {
        controlDigital(pin, false);
    }
}

void controlDigital(const RocketryProto_DigitalControl &digitalControl)
{
    controlDigital(digitalControl.pin, digitalControl.activate);
}