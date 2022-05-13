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
