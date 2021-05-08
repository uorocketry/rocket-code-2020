#include "EventQueue.h"

EventQueue::EventQueue() = default;

EventQueue::~EventQueue() = default;

eventType EventQueue::pop() {
    std::lock_guard<std::mutex> lockGuard(queueMutex);

    if (eventNumberQueue.empty()) return -1;

    auto event = eventNumberQueue.front();
    eventNumberQueue.pop();
    return event;
}

void EventQueue::push(eventType eventNumber) {
    std::lock_guard<std::mutex> lockGuard(queueMutex);

    eventNumberQueue.push(eventNumber);
}
