#pragma once

#include "EventQueue.h"
#include "GroundStationComm.pb.h"
#include "GroundStationEncoder.h"
#include "data/sensorsData.h"
#include <optional>

class GroundStationComm
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

  protected:
    /**
     * Handle a message received from the ground station. This function can be safely called from another thread.
     */
    void handleMessage(const RocketryProto::GroundStationOut &gsData);
};
