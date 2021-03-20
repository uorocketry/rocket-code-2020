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
<<<<<<< HEAD:sbgECom/src/IO/Input.h
	int getData();

protected:
	std::mutex mutex;
=======
>>>>>>> master:src/IO/Input.h

private:
    EventQueue &eventQueue;

    bool isNumber(const std::string& s);
};

#endif