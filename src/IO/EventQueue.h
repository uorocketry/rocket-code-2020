#pragma once

#include "IO.h"
#include "common/pch.h"
#include <queue>

class EventQueue
{
  public:
    EventQueue();

    ~EventQueue();

    // Adds an event to the end of the queue
    // Thread safe
    void push(eventType);

    // Pops the first event from the queue
    // or returns -1 if the queue is empty
    // Thread safe
    eventType pop();

  private:
    std::mutex queueMutex;
    std::queue<eventType> eventNumberQueue;
};
