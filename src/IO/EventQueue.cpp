#include "EventQueue.h"
#include "helpers/Types.h"

EventQueue::EventQueue() {
}

EventQueue::~EventQueue() {
}

eventType EventQueue::pop() {
    std::lock_guard<std::mutex> lockGuard(queueMutex);

    if (eventNumberQueue.empty()) return -1;

    int event = eventNumberQueue.front();
    eventNumberQueue.pop();
    return event;
}

void EventQueue::push(eventType eventNumber) {
    std::lock_guard<std::mutex> lockGuard(queueMutex);

    eventNumberQueue.push(eventNumber);
}