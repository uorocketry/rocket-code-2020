#include "Arduino.h"
#include "digitalMessage.h"
#include "utils.h"

// Servo Information
constexpr int maxDigitalPins = 20;
uint8_t enabledDigitalPins[maxDigitalPins];
uint16_t digitalCount = 0;

void initDigital(const RocketryProto_ArduinoIn &message) {
  // Ignore if we don't have any more free servos
  if (maxDigitalPins == digitalCount) {
    return;
  }

  const RocketryProto_DigitalInit &digitalInit = message.data.digitalInit;

  pinMode(digitalInit.pin, OUTPUT);

  enabledDigitalPins[digitalCount] = digitalInit.pin;
  digitalCount++;
}

void controlDigital(const RocketryProto_ArduinoIn &message) {
    const RocketryProto_DigitalControl &digitalControl = message.data.digitalControl;

    uint8_t pin = digitalControl.pin;

    if (!arrayContains(enabledDigitalPins, digitalCount, pin)) {
      serialPrintLn("Digital pin ", digitalControl.pin, " is not initialized. Ignoring request.");
      return;
    }

    digitalWrite(pin, digitalControl.activate);
}