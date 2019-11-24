#include<iostream>
#include<thread>
#include<vector>
#include<mutex>
#include<chrono>
#include<unordered_map>


class Sensors
{
	int sensor_value;
	std::mutex mutex;
public:
	Sensors() :sensor_value(0){}
	int get_value()   { 	return sensor_value; }
	void add_value(int money)
	{
		std::lock_guard<std::mutex> lockGuard(mutex);
		for(int i = 0; i < money; ++i)
		{	
			sensor_value++;
			std::this_thread::sleep_for (std::chrono::seconds(1));
			if (i == 100) {
				std::cout << "end";
				std::terminate();
			}
		}
	}

};

	

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