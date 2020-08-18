#pragma once

struct sbgData {
	float Xangle;
	float Yangle;
	float Zangle;
	float XangleAcc;
	float YangleAcc;
	float ZangleAcc;
	double gpsLatitude;
	double gpsLongitude;
	double gpsAltitude;
	float barometricAltitude;
	float velocityN;
	float velocityE;
	float velocityD;
	float filteredXacc;
	float filteredYacc;
	float filteredZacc;
	int solutionStatus;
};