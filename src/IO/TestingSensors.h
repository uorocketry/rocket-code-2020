#pragma once

#include "config/config.h"
#if TESTING == 1

#include "IO.h"
#include "../data/SBGData.h"
#include <iostream>
#include <queue>

class TestingSensors : public IO
{
public:
	void run() override;
	void initialize() override;
	bool isInitialized() override;

	sensorsData getLatest();

private:
	std::queue<sensorsData> data;
};

#endif