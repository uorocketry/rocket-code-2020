#ifndef SBGECOM_EVENTQUEUE_H
#define SBGECOM_EVENTQUEUE_H

#include <queue>
#include "IO.h"

class EventQueue {
public:
    EventQueue();

    ~EventQueue();

    // Adds an event to the end of the queue
    // Thread safe
    void push(int);

    // Pops the first event from the queue
    // or returns -1 if the queue is empty
    // Thread safe
    int pop();

private:
    std::mutex queueMutex;
    std::queue<int> eventNumberQueue;
};


#endif //SBGECOM_EVENTQUEUE_H
