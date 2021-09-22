#pragma once

#include "Arduino.h"
#include "ArduinoComm.pb.h"

void saveInitData(const uint8_t* buffer, size_t size);
void restoreInitData();