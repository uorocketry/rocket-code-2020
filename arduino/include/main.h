#pragma once
#include "ArduinoComm.pb.h"
#include "Servo.h"
#include <Arduino.h>

void onPacketReceived(const uint8_t *buffer, size_t size);