#pragma once
#include "IO/Interface.h"
#include "IO/InterfaceImpl.h"
#include "IO/TestingInterface.h"
#include "data/StateData.h"
#include "stateMachineLib/StateMachine.h"
#include <memory>

class InterfacingStateMachine : public StateMachine
{

  public:
    InterfacingStateMachine(Interface *anInterface, BYTE maxStates, BYTE initialState = 0);

    void enterNewState(BYTE state);
    double getValueForTime(double minimum, double maximum, duration_ms targetTime);
    bool switchStatesAfterTime(BYTE state, duration_ms targetTime);
    bool isDelayElapsed(duration_ms targetTime);

  protected:
    Interface *interface;

    std::shared_ptr<StateData> interfaceData;
};