#pragma once

#include "GroundStationComm.h"
#include "IO.h"
#include <helpers/Helper.h>
#include <zmq.hpp>

class GroundStationTCPCommMonitor : public zmq::monitor_t
{
  public:
    GroundStationTCPCommMonitor(zmq::socket_t &socket, const char *addr, std::string socketName);
    void on_event_accepted(const zmq_event_t &event, const char *addr) override;
    void on_event_disconnected(const zmq_event_t &event_, const char *addr_) override;

  private:
    std::string socketName;
};

class GroundStationTCPComm : public GroundStationComm
{
  public:
    explicit GroundStationTCPComm(EventQueue &eventQueue);
    void sendMessage(const RocketryProto::GroundStationIn &message) override;

    /**
     * Function running in a separate thread that continuously waits for a message to arrive, and handle it using
     * `handleMessage()`
     */
    [[noreturn]] void receiveLoop();

  private:
    zmq::context_t zmq_ctx;
    zmq::socket_t sendingSocket;
    zmq::socket_t receiveSocket;

    GroundStationTCPCommMonitor sendingMonitor;
    GroundStationTCPCommMonitor receiveMonitor;
};
