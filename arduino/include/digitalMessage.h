#pragma once

#include "ArduinoComm.pb.h"

void initDigital(const RocketryProto_DigitalInit &message);
void controlDigital(const RocketryProto_DigitalControl &message);