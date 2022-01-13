#include "InterfacingStateMachine.h"
#include "config.h"

InterfacingStateMachine::InterfacingStateMachine(Interface *anInterface, BYTE maxStates, BYTE initialState)
    : StateMachine(maxStates, initialState), interface(anInterface)
{
}

void InterfacingStateMachine::enterNewState(BYTE state)
{
    entryTime = interface->getCurrentTime();
}

double InterfacingStateMachine::getValueForTime(double minimum, double maximum, duration_ms targetTime)
{
    duration_ns timeSinceEntry = interface->getCurrentTime() - entryTime;
    double progress = ((double)timeSinceEntry.count()) / duration_ns(targetTime).count();
    return minimum(maximum, minimum + progress * (maximum - minimum));
}

bool InterfacingStateMachine::isDelayElapsed(duration_ms targetTime)
{
    duration_ns timeSinceEntry = interface->getCurrentTime() - entryTime;
    return timeSinceEntry >= duration_ns(targetTime);
}

bool InterfacingStateMachine::switchStatesAfterTime(BYTE state, duration_ms targetTime)
{
    if (isDelayElapsed(targetTime))
    {
        InternalEvent(state);

        return true;
    }

    return false;
}