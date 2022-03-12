#pragma once
#include "IO/Interface.h"
#include "IO/InterfaceImpl.h"
#include "IO/TestingInterface.h"
#include "data/SensorsData.h"
#include "stateMachineLib/StateMachine.h"
#include <memory>

class InterfacingStateMachine : public StateMachine
{

  public:
    InterfacingStateMachine(Interface *anInterface, uint8_t maxStates, uint8_t initialState = 0);

    void enterNewState(uint8_t state);
    double getValueForTime(double minimum, double maximum, duration_ms targetTime);
    bool switchStatesAfterTime(uint8_t state, duration_ms targetTime, const EventData &eventData);
    bool isDelayElapsed(duration_ms targetTime);

  protected:
    Interface *interface;

    std::shared_ptr<SensorsData> interfaceData;
};