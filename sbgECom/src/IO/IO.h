#pragma once

#include<mutex>
#include<thread>


class IO {
public:
	IO();
	~IO();

	virtual void initialize();
	virtual void run() = 0;
	virtual bool isInitialized() = 0;
	enum InitStatus {INIT, READY};
	

protected:
	/** Must be set before initialize is called */
	bool createThread = true;
	std::mutex mutex;


private:
	std::thread thisThread;
};
