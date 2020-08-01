#include "IO.h"
#include "iostream"
#include<thread>

IO::IO() {
	
}

IO::~IO() {
	// destroy thread
	std::cout << "destroy thread" << std::endl;
	thisThread.~thread(); // thread not killed
	std::cout << "Thread " << "testSensorThread" << " killed:" << std::endl;
}

void IO::initialize() {
	// create thread
	std::cout << "create thread" << std::endl;

	thisThread = std::thread(&IO::run, this);
    thisThread.detach();
}

void IO::run() {

}
