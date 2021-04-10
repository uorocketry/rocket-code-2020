#pragma once
#if USE_INPUT == 1

#include "IO.h"
#include "EventQueue.h"
#include <mutex>

class Input : IO {
public:
	Input(EventQueue &eventQueue);
	~Input();

	void initialize();
	void run();
	bool isInitialized();

private:
    EventQueue &eventQueue;

    bool isNumber(const std::string& s);
};

#endif