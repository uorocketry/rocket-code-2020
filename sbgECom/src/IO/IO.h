#pragma once

#include<mutex>
#include<thread>

enum InitStatus {INIT, READY};

class IO {
public:
	IO();
	~IO();

	virtual void initialize();
	virtual void run();
	virtual bool isInitialized();
	

protected:
	/** Must be set before initialize is called */
	bool createThread = true;
	std::mutex mutex;


private:
	std::thread thisThread;
};
