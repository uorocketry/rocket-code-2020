#pragma once
#if USE_INPUT

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
	int getData();

protected:
	std::mutex mutex;

private:
    EventQueue &eventQueue;

    bool isNumber(const std::string& s);
};

#endif