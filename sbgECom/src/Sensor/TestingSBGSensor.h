#ifdef TESTING
#ifndef _TESTING_SBGSENSOR_H
#define _TESTING_SBGSENSOR_H

#include "SBGSensor.h"

using namespace std;

void SBGSensor::setData(int index, const char* dataInput) {
	// TODO: Set them all in one shot instead of a switch statement?

	switch (index) {
	case 0:
		data.Xangle = strtof(dataInput, nullptr);
		break;
	case 1:
		data.Yangle = strtof(dataInput, nullptr);
		break;
	case 2:
		data.Zangle = strtof(dataInput, nullptr);
		break;
	case 3:
		data.XangleAcc = strtof(dataInput, nullptr);
		break;
	case 4:
		data.YangleAcc = strtof(dataInput, nullptr);
		break;
	case 5:
		data.YangleAcc = strtof(dataInput, nullptr);
		break;
	}
}

std::string SBGSensor::getDataLabel() {
	return "sbg";
}

SensorType Sensor::getSensorType() {
	return SBG_SENSOR;
}

#endif
#endif