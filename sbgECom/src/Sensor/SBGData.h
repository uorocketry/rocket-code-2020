#ifndef _SBGDATA_H
#define _SBGDATA_H


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
};


#endif