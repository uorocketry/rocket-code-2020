#ifndef _SENSOR_H
#define _SENSOR_H

#include<mutex>
#include<thread>

class Sensor
{
public:
	Sensor();
	~Sensor();

	virtual void initialize();
	virtual void run();

	#ifdef TESTING
	/* Generate random data */
	virtual void randomRun();
	#endif

protected:
	std::mutex mutex;
	
private:
	std::thread thisThread;
};


#endif
