#include "InterfacingStateMachine.h"
#include "config.h"

InterfacingStateMachine::InterfacingStateMachine(Interface *anInterface, uint8_t maxStates, uint8_t initialState)
    : StateMachine(maxStates, initialState), interface(anInterface)
{
}

void InterfacingStateMachine::enterNewState(uint8_t state)
{
    entryTime = interface->getCurrentTime();
}

double InterfacingStateMachine::getValueForTime(double minimum, double maximum, duration_ms targetTime)
{
    duration_ns timeSinceEntry = interface->getCurrentTime() - entryTime;
    double progress = ((double)timeSinceEntry.count()) / duration_ns(targetTime).count();
    return std::min(maximum, minimum + progress * (maximum - minimum));
}

bool InterfacingStateMachine::isDelayElapsed(duration_ms targetTime)
{
    duration_ns timeSinceEntry = interface->getCurrentTime() - entryTime;
    return timeSinceEntry >= duration_ns(targetTime);
}

bool InterfacingStateMachine::switchStatesAfterTime(uint8_t state, duration_ms targetTime, const EventData &eventData)
{
    if (isDelayElapsed(targetTime))
    {
        InternalEvent(state, eventData);
        return true;
    }

    return false;
}