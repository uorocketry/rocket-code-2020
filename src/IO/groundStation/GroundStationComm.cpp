#include "GroundStationComm.h"

#include "IO/mavlink/RadioMAVLink.h"

/**
 * Specify which template instances that will be used in the program.
 * This is needed because the function definitions are not in the header file.
 */
template class GroundStationComm<RadioMAVLink>;

template <class T>
GroundStationComm<T>::~GroundStationComm()
{
    active = false;
    sendingCondition.notify_all();

    sendingThread.join();
    receiveThread.join();
}

template <class T>
void GroundStationComm<T>::initialize()
{
    mavlinkInterface.initialize();
}

template <class T>
bool GroundStationComm<T>::isInitialized()
{
    return mavlinkInterface.isInitialized();
}

template <class T>
void GroundStationComm<T>::sendState(const StateData &data)
{
    auto msg = data.convertToMAVLink();

    std::lock_guard lock(sendingMutex);
    sendingBuffer.push_back(msg);
    sendingCondition.notify_all();
}

template <class T>
void GroundStationComm<T>::sendingLoop()
{
    std::chrono::time_point<std::chrono::steady_clock> lastPing;
    std::unique_lock sendingLock(sendingMutex, std::defer_lock);

    while (active)
    {
        if (std::chrono::steady_clock::now() - lastPing > std::chrono::seconds(1))
        {
            mavlinkInterface.sendHeartbeat();
            lastPing = std::chrono::steady_clock::now();
        }

        while (true)
        {
            // Acquire the mutex for as short as possible. This way, the other threads don't wait on us while we send
            // the data.
            sendingLock.lock();
            if (sendingBuffer.empty())
            {
                sendingLock.unlock();
                break;
            }

            auto msg = sendingBuffer.front();
            sendingBuffer.pop_front();
            sendingLock.unlock();

            mavlinkInterface.sendMAVLinkMessage(msg);
        }

        sendingCondition.wait_for(sendingLock, std::chrono::seconds(1));
    }
}

template <class T>
void GroundStationComm<T>::receiveLoop()
{
    while (active)
    {
        mavlink_message_t msg = mavlinkInterface.receiveMessage();
        switch (msg.msgid)
        {
        default:
            break;
        }
    }
}

template <class T>
void GroundStationComm<T>::sink_it_(const spdlog::details::log_msg &log)
{
    mavlink_log_message_t mavLog;

    // Convert from spdlog's level to MAVLink's
    switch (log.level)
    {
    case spdlog::level::trace:
    case spdlog::level::debug:
        mavLog.severity = MAV_SEVERITY::MAV_SEVERITY_DEBUG;
        break;
    case spdlog::level::info:
        mavLog.severity = MAV_SEVERITY::MAV_SEVERITY_INFO;
        break;
    case spdlog::level::warn:
        mavLog.severity = MAV_SEVERITY::MAV_SEVERITY_WARNING;
        break;
    case spdlog::level::err:
        mavLog.severity = MAV_SEVERITY::MAV_SEVERITY_ERROR;
        break;
    case spdlog::level::critical:
        mavLog.severity = MAV_SEVERITY::MAV_SEVERITY_CRITICAL;
        break;
    default:
        mavLog.severity = MAV_SEVERITY::MAV_SEVERITY_INFO;
    }

    // Copy the message into the MAVLink struct, making sure we don't overflow.
    auto length = std::min(log.payload.size(), std::size(mavLog.data));
    mavLog.length = length;
    memcpy(mavLog.data, log.payload.data(), length);

    mavlink_message_t msg;
    mavlink_msg_log_message_encode(MAVLINK_SYSTEM.sysid, MAVLINK_SYSTEM.compid, &msg, &mavLog);

    // Queue the message.
    std::lock_guard lock(sendingMutex);
    sendingBuffer.push_back(msg);
    sendingCondition.notify_all();
}
