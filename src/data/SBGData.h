#pragma once

#include "sbgTypes.h"

struct sbgData {
	float roll = -1;
	float pitch = -1;
	float yaw = -1;
	float rollAccuracy = -1;
	float pitchAccuracy = -1;
	float yawAccuracy = -1;
	double gpsLatitude = -1;
	double gpsLongitude = -1;
	double gpsAltitude = -1;
	float barometricAltitude = -1;
	float relativeBarometricAltitude = -1;
	float velocityN = -1;
	float velocityE = -1;
	float velocityD = -1;
	float filteredXaccelerometer = -1;
	float filteredYaccelerometer = -1;
	float filteredZaccelerometer = -1;
	uint32 solutionStatus = -1;

	//to only log

	uint32 gpsPosStatus = -1;
	float gpsPosAccuracyLatitude = -1;
	float gpsPosAccuracyLongitude = -1;
	float gpsPosAccuracyAltitude = -1;
	uint8 NumSvUsed = -1;

	float velocityNAccuracy = -1;
	float velocityEAccuracy = -1;
	float velocityDAccuracy = -1;

	float latitudeAccuracy = -1;
	float longitudeAccuracy = -1;
	float altitudeAccuracy = -1;

	uint16 pressureStatus = -1;
	float barometricPressure = -1;

	uint32 imuStatus = -1;
	float gyroX = -1;
	float gyroY = -1;
	float gyroZ = -1;
	float temp = -1;
	float deltaVelX = -1;
	float deltaVelY = -1;
	float deltaVelZ = -1;
	float deltaAngleX = -1;
	float deltaAngleY = -1;
	float deltaAngleZ = -1;
	
};