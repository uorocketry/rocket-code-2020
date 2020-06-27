#include "Interface.h"
#include "Sensor/Sensor.h"
#include <iostream>
#include <fstream>
using namespace std;


Interface::Interface() {

}

Interface::~Interface() {
	
}

void Interface::initializeSensors() {

}

void Interface::update() {
	latestState.sbg = mySbgSensor.getData();

}

void Interface::log(string filename, bool debugState)
{
    ofstream myfile(filename.c_str(), std::ios_base::app); //append
    if(myfile.is_open())
    {
		if(debugState)
		{
			cout << "Writing Xangle data: " << this->latestState.sbg.Xangle << " to " << filename << endl;
			cout << "Writing Yangle data: " << this->latestState.sbg.Yangle << " to " << filename << endl;
			cout << "Writing Zangle data: " << this->latestState.sbg.Zangle << " to " << filename << endl;

			cout << "Writing Xangle data: " << this->latestState.sbg.Xangle << " to " << filename << endl;
			cout << "Writing Yangle data: " << this->latestState.sbg.Yangle << " to " << filename << endl;
			cout << "Writing Zangle data: " << this->latestState.sbg.Zangle << " to " << filename << endl;

			cout << "Writing gpsLatitude data: " << this->latestState.sbg.gpsLatitude << " to " << filename << endl;
			cout << "Writing gpsLongitude data: " << this->latestState.sbg.gpsLongitude << " to " << filename << endl;
			cout << "Writing gpsAltitude data: " << this->latestState.sbg.gpsAltitude << " to " << filename << endl;

			cout << "Writing barometricAltitude data: " << this->latestState.sbg.barometricAltitude << " to " << filename << endl;
	
			cout << "Writing velocityN data: " << this->latestState.sbg.velocityN << " to " << filename << endl;
			cout << "Writing velocityE data: " << this->latestState.sbg.velocityE << " to " << filename << endl;
			cout << "Writing velocityD data: " << this->latestState.sbg.velocityD << " to " << filename << endl;

			cout << "Writing filteredXacc data: " << this->latestState.sbg.filteredXacc << " to " << filename << endl;
			cout << "Writing filteredYacc data: " << this->latestState.sbg.filteredYacc << " to " << filename << endl;
			cout << "Writing filteredZacc data: " << this->latestState.sbg.filteredZacc << " to " << filename << endl;

			cout << "Writing solutionStatus data: " << this->latestState.sbg.solutionStatus << " to " << filename << endl;	
		}

		myfile << "Xangle: "<< this->latestState.sbg.Xangle << endl;
		myfile << "Yangle: "<< this->latestState.sbg.Yangle << endl;
		myfile << "Zangle: "<< this->latestState.sbg.Zangle << endl;

		myfile << "XangleAcc: "<< this->latestState.sbg.XangleAcc << endl;
		myfile << "YangleAcc: "<< this->latestState.sbg.YangleAcc << endl;
		myfile << "ZangleAcc: "<< this->latestState.sbg.ZangleAcc << endl;

		myfile << "gpsLatitude: "<< this->latestState.sbg.gpsLatitude << endl;
		myfile << "gpsLongitude: "<< this->latestState.sbg.gpsLongitude << endl;
		myfile << "gpsAltitude: "<< this->latestState.sbg.gpsAltitude << endl;

		myfile << "barometricAltitude: "<< this->latestState.sbg.barometricAltitude << endl;

		myfile << "velocityN: "<< this->latestState.sbg.velocityN << endl;
		myfile << "velocityE: "<< this->latestState.sbg.velocityE << endl;
		myfile << "velocityD: "<< this->latestState.sbg.velocityD << endl;

		myfile << "filteredXacc: "<< this->latestState.sbg.filteredXacc << endl;
		myfile << "filteredYacc: "<< this->latestState.sbg.filteredYacc << endl;
		myfile << "filteredZacc: "<< this->latestState.sbg.filteredZacc << endl;

		myfile << "solutionStatus: "<< this->latestState.sbg.solutionStatus << endl;

        myfile.close();
    }
    else cout << "Unable to open " <<filename << endl;
}

rocketState* Interface::getLatest() {
	
	return &latestState;
}