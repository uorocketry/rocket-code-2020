#include "Arduino.h"
#include "servoMessage.h"
#include "utils.h"

// Servo Information
constexpr int maxServoCount = 10;
ServoInfo servos[maxServoCount];
uint16_t servoCount = 0;

void initServo(const RocketryProto_ArduinoIn &message) {
  // Ignore if we don't have any more free servos
  if (maxServoCount == servoCount) {
    return;
  }

  const RocketryProto_ServoInit &servoInit = message.data.servoInit;

  servos[servoCount] = {Servo(), static_cast<uint8_t>(servoInit.pin), static_cast<int>(servoInit.safePosition)};
  servos[servoCount].servo.attach(servoInit.pin);
  servos[servoCount].servo.write(servoInit.safePosition);

  servoCount++;
}

void controlServo(const RocketryProto_ArduinoIn &message) {
    const RocketryProto_ServoControl &servoControl = message.data.servoControl;

    for (uint16_t i = 0; i < servoCount; i++) {
        ServoInfo &servo = servos[i];
        if (servo.pin != servoControl.pin) {
            continue;
        }

        servo.servo.write(servoControl.position);
        return;
    }

    serialPrintLn("Servo ", servoControl.pin, " is not initialized. Ignoring request.");
}