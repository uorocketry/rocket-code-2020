#pragma once
#include <Arduino.h>
#include "ArduinoComm.pb.h"
#include "Servo.h"

void onPacketReceived(const uint8_t* buffer, size_t size);