#pragma once

#include "config.h"
#if USE_LOGGER == 1

#include "../data/sensorsData.h"
#include "IO.h"
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class SensorLogger : public IO
{
  public:
    static int working;
    ~SensorLogger();

    void initialize() override;
    void run() override;
    bool isInitialized() override;

    // write data to sensorsData struct and push to queue on main thread
    void enqueueSensorData(const sensorsData &curSensorData);

    bool queueEmpty();

  protected:
    std::mutex mutex;

  private:
    // pop queue and log the data from sensorsData on logging thread
    bool writeToFile(std::ofstream &fileStream, sensorsData currentState);

    static void writeHeader(std::ofstream &file, sensorsData currentState); 
    static void writeData(std::ofstream &file, const sensorsData &currentState);

    static int getBootId(std::string &path);

    const std::chrono::duration<int64_t, std::ratio<1, 1>> ONE_SECOND =
        std::chrono::duration<int64_t, std::ratio<1, 1>>(1);

    std::thread thisThread;

    // queue of sensor data to be logged
    std::queue<sensorsData> logQueue;

    std::mutex writingMutex;
    std::unique_lock<std::mutex> writingLock;
    std::condition_variable writingCondition;

    sensorsData getCurrentState();
    void writeToHeader(sensorsData currentState, bool &isFirstLine, std::string path, std::string filename);
    bool sendToWriteFile(std::string path, std::string filename, sensorsData currentState);
    void popData();

    struct InitFlags
    {
        InitStatus fileStatus = INIT;
    } status;
};

#endif