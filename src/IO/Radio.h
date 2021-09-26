#pragma once

#include "config/config.h"
#if USE_RADIO == 1

#include "../data/sensorsData.h"
#include "EventQueue.h"
#include "IO.h"
#include <condition_variable>
#include <mutex>
#include <queue>
#include <spdlog/logger.h>

class Radio : public IO
{
  public:
    explicit Radio(EventQueue &eventQueue);
    ~Radio();

    void initialize() override;
    void run() override;
    bool isInitialized() override;

    // write data to sensorsData struct and push to queue on main thread
    void enqueueSensorData(const sensorsData &curSensorData);

  protected:
    std::mutex mutex;

  private:
    EventQueue &eventQueue;

    std::shared_ptr<spdlog::logger> logger;

    // pop queue and log the data from sensorsData on logging thread
    void dequeueToRadio();

    void sendData(const sensorsData &currentState) const;

    const std::chrono::duration<int64_t, std::ratio<1, 1>> ONE_SECOND =
        std::chrono::duration<int64_t, std::ratio<1, 1>>(1);

    std::thread thisThread;

    // queue of sensor data to be logged
    std::queue<sensorsData> logQueue;

    std::mutex writingMutex;
    std::unique_lock<std::mutex> writingLock;
    std::condition_variable writingCondition;

    std::shared_ptr<std::ofstream> fileStream = nullptr;

    int fd = 0;

    struct InitFlags
    {
        InitStatus wiringPiStatus = INIT;
    } status;
};

#endif