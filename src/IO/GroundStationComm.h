#pragma once

#include "EventQueue.h"
#include "GroundStationComm.pb.h"
#include "GroundStationEncoder.h"
#include "data/sensorsData.h"
#include "spdlog/sinks/base_sink.h"
#include <mutex>
#include <optional>

class GroundStationComm : public spdlog::sinks::base_sink<std::mutex>
{
  public:
    explicit GroundStationComm(EventQueue &eventQueue) : eventQueue(eventQueue)
    {
    }

    /**
     * Send sensor data to the ground station.
     */
    void sendSensorData(const sensorsData &data);

    virtual bool isInitialized() = 0;

  private:
    EventQueue &eventQueue;

    /**
     * Send a protobuf message to the ground-station. This function is non-blocking and can drop the data if needed.
     */
    virtual void sendMessage(const RocketryProto::GroundStationIn &gsData) = 0;

    /**
     * Handle any logs from spdlog and send them to the ground station
     */
    void sink_it_(const spdlog::details::log_msg &msg) override;
    void flush_() override
    {
    }

  protected:
    /**
     * Handle a message received from the ground station. This function can be safely called from another thread.
     */
    void handleMessage(const RocketryProto::GroundStationOut &gsData);
};
