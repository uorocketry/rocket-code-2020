#pragma once

#ifdef TESTING

#include "IO.h"
#include "../data/SBGData.h"
#include <iostream>
#include <queue>

class TestingSensors : public IO {
public:
	void run();
	void initialize();

	rocketState getLatest();
private:
	std::queue<rocketState> data;

	int processInt(std::string data);
	float processFloat(std::string data);
	double processDouble(std::string data);
};

#endif