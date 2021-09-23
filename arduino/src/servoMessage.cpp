#include "Arduino.h"
#include "servoMessage.h"
#include "utils.h"

// Servo Information
constexpr int maxServoCount = 12;
ServoInfo servos[maxServoCount];
uint16_t servoCount = 0;

ServoInfo* findServo(int pin) {
    for (uint16_t i = 0; i < servoCount; i++) {
        ServoInfo &servo = servos[i];
        if (servo.pin == pin) {
            return &servo;
        }
    }

    return nullptr;
}

void controlServo(uint8_t pin, int position) {
    ServoInfo* servo = findServo(pin);
    
    if (servo != nullptr) {
        serialPrintLn("Servo control: pin: ", pin, ", position: ", position);

        servo->servo.write(position);
    } else {
        serialPrintLn("Servo ", pin, " is not initialized. Ignoring request.");
    }
}

void initServo(const RocketryProto_ServoInit &servoInit) {
    ServoInfo* servo = findServo(servoInit.pin);

    if (servo == nullptr) {
        // Ignore if we don't have any more free servos
        if (maxServoCount == servoCount) {
            return;
        }

        servos[servoCount].pin = static_cast<uint8_t>(servoInit.pin);
        servos[servoCount].safePosition = static_cast<int>(servoInit.safePosition);
        servos[servoCount].servo.attach(servoInit.pin);
        servos[servoCount].servo.write(servoInit.safePosition);

        servoCount++;

        serialPrintLn("Servo init: pin: ", servoInit.pin, ", safePosition:", servoInit.safePosition);
    } else {
        servo->safePosition = servoInit.safePosition;

        controlServo(servoInit.pin, servoInit.safePosition);
        serialPrintLn("Servo 2nd time init: pin: ", servoInit.pin, ", safePosition:", servoInit.safePosition);
    }
}

void controlServo(const RocketryProto_ServoControl &servoControl) {
    controlServo(servoControl.pin, servoControl.position);
}