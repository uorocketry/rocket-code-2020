#include "Interface.h"
#include "Sensor/Sensor.h"
#include <iostream>
#include <fstream>
#include <queue>


Interface::Interface() {

}

Interface::~Interface() {
	
}

void Interface::initializeSensors() {

}

void Interface::update() {
	latestState.sbg = mySbgSensor.getData();

}

void Interface::EnqueueSensorData(rocketState cur_sensor_data)
{
	this->myqueue.push(cur_sensor_data);
}

void Interface::DequeueToFile(std::string filename)
{
	while(!this->myqueue.empty())
	{
		rocketState temp = this->myqueue.front();
		this->myqueue.pop();
		std::ofstream myfile(filename.c_str(), std::ios_base::app); //append
    	if(myfile.is_open())
		{
			myfile << "Xangle: "<< temp.sbg.Xangle << "\n";
			myfile << "Yangle: "<< temp.sbg.Yangle << "\n";
			myfile << "Zangle: "<< temp.sbg.Zangle << "\n";

			myfile << "XangleAcc: "<< temp.sbg.XangleAcc << "\n";
			myfile << "YangleAcc: "<< temp.sbg.YangleAcc << "\n";
			myfile << "ZangleAcc: "<< temp.sbg.ZangleAcc << "\n";

			myfile << "gpsLatitude: "<< temp.sbg.gpsLatitude << "\n";
			myfile << "gpsLongitude: "<< temp.sbg.gpsLongitude << "\n";
			myfile << "gpsAltitude: "<< temp.sbg.gpsAltitude << "\n";

			myfile << "barometricAltitude: "<< temp.sbg.barometricAltitude << "\n";

			myfile << "velocityN: "<< temp.sbg.velocityN << "\n";
			myfile << "velocityE: "<< temp.sbg.velocityE << "\n";
			myfile << "velocityD: "<< temp.sbg.velocityD << "\n";

			myfile << "filteredXacc: "<< temp.sbg.filteredXacc << "\n";
			myfile << "filteredYacc: "<< temp.sbg.filteredYacc << "\n";
			myfile << "filteredZacc: "<< temp.sbg.filteredZacc << "\n";

			myfile << "solutionStatus: "<< temp.sbg.solutionStatus << "\n";

			myfile.close();
		}
		else 
		{
			std::cout << "Unable to open " <<filename << "\n";
		}
	}
}

void Interface::log(std::string filename)
{
	//enqueue latest sensor data
	EnqueueSensorData(this->latestState);

	//write the contents of queue to txt file
	DequeueToFile(filename);
}

rocketState* Interface::getLatest() {
	
	return &latestState;
}