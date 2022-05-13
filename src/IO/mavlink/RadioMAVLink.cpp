#include "RadioMAVLink.h"

#include <sys/poll.h>
#include <unistd.h>
#include <uorocketry/mavlink.h>
#include <wiringSerial.h>

RadioMAVLink::RadioMAVLink(std::string port, int mavlinkChannel) : port(port), mavlinkChannel(mavlinkChannel)
{
}

RadioMAVLink::~RadioMAVLink()
{
    if (ready)
    {
        close(fd);
    }
}

void RadioMAVLink::initialize()
{
    if ((fd = serialOpen(port.c_str(), 57600)) < 0)
    {
        SPDLOG_ERROR("Error while opening serial communication!");
        ready = false;
    }
    else
    {
        ready = true;
    }
}

bool RadioMAVLink::isInitialized()
{
    return ready;
}

mavlink_message_t RadioMAVLink::receiveMessage()
{
    if (!ready)
    {
        throw std::runtime_error("Can't receive MAVLink message: not initialized.");
    }

    mavlink_message_t msg;
    bool receivedMessage = false;

    while (!receivedMessage)
    {
        struct pollfd pfds[1] = {fd, POLLIN};
        poll(pfds, 1, -1);

        while (serialDataAvail(fd) > 0 && !receivedMessage)
        {
            int byte = serialGetchar(fd);
            receivedMessage = mavlink_parse_char(mavlinkChannel, byte, &msg, &status);
        }
    }

    return msg;
}
void RadioMAVLink::sendMAVLinkMessage(const mavlink_message_t &message)
{
    if (!ready)
    {
        throw std::runtime_error("Can't send MAVLink message: not initialized.");
    }

    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    auto len = mavlink_msg_to_send_buffer(buf, &message);

    auto num = write(fd, buf, len);
    if (num == -1)
    {
        SPDLOG_ERROR("Error sending MAVLink message");
    }
    else if (num != len)
    {
        // Maybe eventually send all the bytes if this happens too often.
        SPDLOG_ERROR("Couldn't send the full MAVLink message");
    }
}
