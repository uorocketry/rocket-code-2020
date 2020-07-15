#pragma once

#include<mutex>
#include<thread>

class IO
{
public:
	IO();
	~IO();

	virtual void initialize();
	virtual void run();

protected:
	std::mutex mutex;
	
private:
	std::thread thisThread;
};
