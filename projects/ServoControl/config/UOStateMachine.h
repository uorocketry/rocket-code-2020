#pragma once

#include "config/config.h"
#include "stateMachine/InterfacingStateMachine.h"
#include "helpers/Types.h"
#include "data/UOSMData.h"

class UOStateMachine : public InterfacingStateMachine
{
public:
    UOStateMachine();

    // External events taken by this state machine
    void StartFillingEXT();
    void StopFillingEXT();
    void AbortFillingEXT();
    void DoneEXT();

    void updateHotFire(UOSMData *data);

protected:

#if !TESTING
    InterfaceImpl interfaceImpl;
#else
    TestingInterface interfaceImpl;
#endif

private:
    void detectExternEvent(std::shared_ptr<sensorsData> data);
    void showInfo(std::shared_ptr<sensorsData> data);

    // State enumeration order must match the order of state method entries
    // in the state map.
    enum States
    {
        ST_INIT,
        ST_WAIT_FOR_INIT,
        ST_WAIT_FOR_FILLING,
        ST_FILLING,
        ST_DONE,
        ST_ABORT_FILLING,
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
    // WaitForFilling
    ENTRY_DECLARE(UOStateMachine, EnterWaitForFilling, UOSMData)
    STATE_DECLARE(UOStateMachine, WaitForFilling, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitWaitForFilling)
    // Filling
    ENTRY_DECLARE(UOStateMachine, EnterFilling, UOSMData)
    STATE_DECLARE(UOStateMachine, Filling, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitFilling)
    // Done
    ENTRY_DECLARE(UOStateMachine, EnterDone, UOSMData)
    STATE_DECLARE(UOStateMachine, Done, UOSMData)
    // AbortFilling
    ENTRY_DECLARE(UOStateMachine, EnterAbortFilling, UOSMData)
    STATE_DECLARE(UOStateMachine, AbortFilling, UOSMData)

    BEGIN_STATE_MAP_EX
    STATE_MAP_ENTRY_ALL_EX(&Init, 0, 0, &ExitInit)
    STATE_MAP_ENTRY_ALL_EX(&WaitForInit, 0, &EnterWaitForInit, &ExitWaitForInit)
    STATE_MAP_ENTRY_ALL_EX(&WaitForFilling, 0, &EnterWaitForFilling, &ExitWaitForFilling)
    STATE_MAP_ENTRY_ALL_EX(&Filling, 0, &EnterFilling, &ExitFilling)
    STATE_MAP_ENTRY_ALL_EX(&Done, 0, &EnterDone, 0)
    STATE_MAP_ENTRY_ALL_EX(&AbortFilling, 0, &EnterAbortFilling, 0)
    END_STATE_MAP_EX

    std::shared_ptr<sensorsData> updateInterface(const UOSMData *smdata, States state);
};