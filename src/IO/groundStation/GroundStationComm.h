#pragma once

#include <boost/circular_buffer.hpp>
#include <mutex>
#include <spdlog/sinks/base_sink.h>

#include "IO/EventQueue.h"
#include "data/StateData.h"

template <class T>
class GroundStationComm : public spdlog::sinks::base_sink<std::mutex>
{
  public:
    template <typename... Args>
    explicit GroundStationComm(EventQueue &eventQueue, Args &&...data)
        : eventQueue(eventQueue), mavlinkInterface(std::forward<Args>(data)...),
          sendingThread(std::bind(&GroundStationComm<T>::sendingLoop, this)),
          receiveThread(std::bind(&GroundStationComm<T>::receiveLoop, this))
    {
    }

    ~GroundStationComm() override;

    void initialize();
    bool isInitialized();

    /**
     * Send the state to the ground station.
     */
    void sendState(const StateData &data);

    //    virtual bool isInitialized() = 0;

    /**
     * Handle any logs from spdlog and send them to the ground station
     */
    void sink_it_(const spdlog::details::log_msg &msg) override;
    void flush_() override
    {
    }

  private:
    void sendingLoop();
    void receiveLoop();

    T mavlinkInterface;
    EventQueue &eventQueue;

    std::atomic<bool> active{true};
    std::thread sendingThread;
    std::thread receiveThread;

    std::mutex sendingMutex;
    std::condition_variable sendingCondition;
    boost::circular_buffer<mavlink_message_t> sendingBuffer;
};
