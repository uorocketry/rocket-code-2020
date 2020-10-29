#pragma once

#include "sbgTypes.h"

struct sbgData {
	float roll;
	float pitch;
	float yaw;
	float rollAccuracy;
	float pitchAccuracy;
	float yawAccuracy;
	double gpsLatitude;
	double gpsLongitude;
	double gpsAltitude;
	float barometricAltitude;
	float velocityN;
	float velocityE;
	float velocityD;
	float filteredXaccelerometer;
	float filteredYaccelerometer;
	float filteredZaccelerometer;
	uint32 solutionStatus;

	//to only log

	uint32 gpsPosStatus;
	float gpsPosAccuracyLatitude;
	float gpsPosAccuracyLongitude;
	float gpsPosAccuracyAltitude;
	uint8 NumSvUsed;

	float velocityNAccuracy;
	float velocityEAccuracy;
	float velocityDAccuracy;

	float latitudeAccuracy;
	float longitudeAccuracy;
	float altitudeAccuracy;

	uint16 pressureStatus;
	float barometricPressure;

	uint32 imuStatus;
	float gyroX;
	float gyroY;
	float gyroZ;
	float temp;
	float deltaVelX;
	float deltaVelY;
	float deltaVelZ;
	float deltaAngleX;
	float deltaAngleY;
	float deltaAngleZ;
	
};