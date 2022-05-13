#pragma once

#include "uorocketry/mavlink.h"

/**
 * Simple interface outlining the methods that a MAVLink class must implement.
 */
class MAVLinkInterface
{
  public:
    /**
     * Initializes the MAVLink class. This must be called exactly once and before any other methods.
     */
    virtual void initialize() = 0;

    /**
     * Returns if the class is initialized.
     */
    virtual bool isInitialized() = 0;

    /**
     * Receives a MAVLink message. This function will block until the message is received. This function should be
     * called from a single thread.
     *
     * @returns the received message.
     */
    virtual mavlink_message_t receiveMessage() = 0;

    /**
     * Sends a MAVLink message. This function is NOT thread-safe.
     *
     * @param message the message to send.
     */
    virtual void sendMAVLinkMessage(const mavlink_message_t &message) = 0;

    /**
     * Convenience function for sending MAVLink heartbeats. Over RF links, this should be called at around 1 Hz.
     */
    virtual void sendHeartbeat();
};