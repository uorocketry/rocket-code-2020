#pragma once
#if USE_INPUT

#include "IO.h"
#include <mutex>

class Input : IO {
public:
	Input();
	~Input();

	void initialize();
	void run();
	bool isInitialized();
	int getData();

protected:
	std::mutex mutex;

private:
    int eventNumber = -1;
    bool isNumber(const std::string& s);

};

#endif