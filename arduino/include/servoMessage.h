#pragma once

#include "Servo.h"
#include "ArduinoComm.pb.h"

struct ServoInfo {
    Servo servo;
    uint8_t pin;
    int safePosition;
};

void initServo(const RocketryProto_ServoInit &message);
void controlServo(const RocketryProto_ServoControl &message);
