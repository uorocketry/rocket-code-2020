#include<iostream>
#include<thread>
#include<vector>
#include<mutex>
#include<chrono>
#include<unordered_map>
#include"SensorsRead.h"


	

int main()
{
 
	Sensors Sensors_read;

    
    std::thread thread1 = std::thread(&Sensors::add_value, &Sensors_read, 1000);

    typedef std::unordered_map<std::string, std::thread> ThreadMap;
    ThreadMap tm_;

    thread1.detach();
    tm_["thread1"] = std::move(thread1);

    int loop = true;

    while (loop) {
    	int value = Sensors_read.get_value();
    	std::cout << value << std::endl;
    	
    	if (value >= 5) {
	    	ThreadMap::const_iterator it = tm_.find("thread1");
	    	it->second.std::thread::~thread(); // thread not killed
	        tm_.erase("thread1");
	        std::cout << "Thread " << "thread1" << " killed:" << std::endl;
	        loop = false;
	    	
    	}
    }

    // thread1.join();
	return 0;
}