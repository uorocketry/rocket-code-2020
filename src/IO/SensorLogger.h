#pragma once
#include "common/pch.h"
#include "config.h"

#include "../data/SensorsData.h"
#include "IO.h"
#include <condition_variable>

class SensorLogger : public IO
{
  public:
    static int working;
    ~SensorLogger();

    void initialize() override;
    void run() override;
    bool isInitialized() override;

    // write data to sensorsData struct and push to queue on main thread
    void enqueueSensorData(const SensorsData &curSensorData);

    bool queueEmpty();

  protected:
    std::mutex mutex;

  private:
    // pop queue and log the data from sensorsData on logging thread
    void dequeueToFile(std::ofstream &fileStream);

    static void writeHeader(std::ofstream &file);
    static void writeData(std::ofstream &file, const SensorsData &currentState);

    static int getBootId(std::string &path);

    const std::chrono::duration<int64_t, std::ratio<1, 1>> ONE_SECOND =
        std::chrono::duration<int64_t, std::ratio<1, 1>>(1);

    std::thread thisThread;

    // queue of sensor data to be logged
    std::queue<SensorsData> logQueue;

    std::mutex writingMutex;
    std::unique_lock<std::mutex> writingLock;
    std::condition_variable writingCondition;

    struct InitFlags
    {
        InitStatus fileStatus = INIT;
    } status;
};