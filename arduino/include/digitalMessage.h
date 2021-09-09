#pragma once

#include "ArduinoComm.pb.h"

void initDigital(const RocketryProto_ArduinoIn &message);
void controlDigital(const RocketryProto_ArduinoIn &message);