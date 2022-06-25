#pragma once

#include <mutex>
#include <uorocketry/mavlink.h>

#include "MAVLinkInterface.h"

class RadioMAVLink : public MAVLinkInterface
{
  public:
    explicit RadioMAVLink(std::string port, int mavlinkChannel);
    ~RadioMAVLink();

    void initialize() override;
    bool isInitialized() override;
    mavlink_message_t receiveMessage() override;
    void sendMAVLinkMessage(const mavlink_message_t &message) override;

  private:
    int mavlinkChannel;
    std::string port;

    int fd = -1;
    bool ready = false;

    mavlink_status_t status;
};
