#pragma once

#include "config/config.h"
#include "stateMachine/InterfacingStateMachine.h"
#include "helpers/Types.h"
#include "data/UOSMData.h"

class UOStateMachine : public InterfacingStateMachine
{
public:
    UOStateMachine();

    void updateHotFire(UOSMData *data);

protected:

#if !TESTING
    InterfaceImpl interfaceImpl;
#else
    TestingInterface interfaceImpl;
#endif

private:
    enum States
    {
        ST_INIT,
        ST_WAIT_FOR_INIT,
        ST_CONTROL,
        ST_MAX_STATES
    };

    // Define the state machine state functions with event data type
    // Init
    STATE_DECLARE(UOStateMachine, Init, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitInit)
    // WaitForInit
    ENTRY_DECLARE(UOStateMachine, EnterWaitForInit, UOSMData)
    STATE_DECLARE(UOStateMachine, WaitForInit, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitWaitForInit)
    // Control
    ENTRY_DECLARE(UOStateMachine, EnterControl, UOSMData)
    STATE_DECLARE(UOStateMachine, Control, UOSMData)

    BEGIN_STATE_MAP_EX
    STATE_MAP_ENTRY_ALL_EX(&Init, 0, 0, &ExitInit)
    STATE_MAP_ENTRY_ALL_EX(&WaitForInit, 0, &EnterWaitForInit, &ExitWaitForInit)
    STATE_MAP_ENTRY_ALL_EX(&Control, 0, &EnterControl, 0)
    END_STATE_MAP_EX

    std::shared_ptr<sensorsData> updateInterface(const UOSMData *smdata, States state);
};
