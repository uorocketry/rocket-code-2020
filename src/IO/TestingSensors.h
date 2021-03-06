#pragma once

#include "config/config.h"
#if TESTING

#include "IO.h"
#include "../data/SBGData.h"
#include <iostream>
#include <queue>

class TestingSensors : public IO
{
public:
	void run();
	void initialize();
	bool isInitialized();

	sensorsData getLatest();

private:
	std::queue<sensorsData> data;
};

#endif