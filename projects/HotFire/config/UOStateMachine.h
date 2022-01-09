#pragma once

#include "config/config.h"
#include "data/UOSMData.h"
#include "helpers/Types.h"
#include "stateMachine/InterfacingStateMachine.h"

class UOStateMachine : public InterfacingStateMachine
{
  public:
    UOStateMachine(Interface *anInterface);

    // External events taken by this state machine
    void ReadyEXT();
    void StartFillingEXT();
    void AbortEXT();
    void StopFillingEXT();
    void IgnitionEXT();
    void FinalVentingEXT();
    void DoneEXT();
    void ServoControlEXT();

    void updateHotFire(UOSMData *data);

  private:
    void detectConnectionTimeout(const std::shared_ptr<sensorsData> &data);
    void detectExternEvent(const std::shared_ptr<sensorsData> &data);

    std::shared_ptr<spdlog::logger> logger;

    // State enumeration order must match the order of state method entries
    // in the state map.
    enum States
    {
        ST_INIT,
        ST_WAIT_FOR_INIT,
        ST_WAIT_FOR_READY,
        ST_WAIT_FOR_FILLING,
        ST_FILLING,
        ST_WAIT_FOR_IGNITION,
        ST_IGNITION,
        ST_FULL_BURN,
        ST_FINAL_VENTING,
        ST_DONE,
        ST_ABORT_FILLING,
        ST_ABORT_BURN,
        ST_SERVO_CONTROL, // Debugging state
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
    // WaitForReady
    ENTRY_DECLARE(UOStateMachine, EnterWaitForReady, UOSMData)
    STATE_DECLARE(UOStateMachine, WaitForReady, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitWaitForReady)
    // WaitForFilling
    ENTRY_DECLARE(UOStateMachine, EnterWaitForFilling, UOSMData)
    STATE_DECLARE(UOStateMachine, WaitForFilling, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitWaitForFilling)
    // Filling
    ENTRY_DECLARE(UOStateMachine, EnterFilling, UOSMData)
    STATE_DECLARE(UOStateMachine, Filling, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitFilling)
    // WaitForIgnition
    ENTRY_DECLARE(UOStateMachine, EnterWaitForIgnition, UOSMData)
    STATE_DECLARE(UOStateMachine, WaitForIgnition, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitWaitForIgnition)
    // Ignition
    ENTRY_DECLARE(UOStateMachine, EnterIgnition, UOSMData)
    STATE_DECLARE(UOStateMachine, Ignition, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitIgnition)
    // FullBurn
    ENTRY_DECLARE(UOStateMachine, EnterFullBurn, UOSMData)
    STATE_DECLARE(UOStateMachine, FullBurn, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitFullBurn)
    // FinalVenting
    ENTRY_DECLARE(UOStateMachine, EnterFinalVenting, UOSMData)
    STATE_DECLARE(UOStateMachine, FinalVenting, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitFinalVenting)
    // Done
    ENTRY_DECLARE(UOStateMachine, EnterDone, UOSMData)
    STATE_DECLARE(UOStateMachine, Done, UOSMData)
    // AbortFilling
    ENTRY_DECLARE(UOStateMachine, EnterAbortFilling, UOSMData)
    STATE_DECLARE(UOStateMachine, AbortFilling, UOSMData)
    // AbortBurn
    ENTRY_DECLARE(UOStateMachine, EnterAbortBurn, UOSMData)
    STATE_DECLARE(UOStateMachine, AbortBurn, UOSMData)
    // ServoControl
    ENTRY_DECLARE(UOStateMachine, EnterServoControl, UOSMData)
    STATE_DECLARE(UOStateMachine, ServoControl, UOSMData)

    BEGIN_STATE_MAP_EX
    STATE_MAP_ENTRY_ALL_EX(&Init, nullptr, nullptr, &ExitInit)
    STATE_MAP_ENTRY_ALL_EX(&WaitForInit, nullptr, &EnterWaitForInit, &ExitWaitForInit)
    STATE_MAP_ENTRY_ALL_EX(&WaitForReady, nullptr, &EnterWaitForReady, &ExitWaitForReady)
    STATE_MAP_ENTRY_ALL_EX(&WaitForFilling, nullptr, &EnterWaitForFilling, &ExitWaitForFilling)
    STATE_MAP_ENTRY_ALL_EX(&Filling, nullptr, &EnterFilling, &ExitFilling)
    STATE_MAP_ENTRY_ALL_EX(&WaitForIgnition, nullptr, &EnterWaitForIgnition, &ExitWaitForIgnition)
    STATE_MAP_ENTRY_ALL_EX(&Ignition, nullptr, &EnterIgnition, &ExitIgnition)
    STATE_MAP_ENTRY_ALL_EX(&FullBurn, nullptr, &EnterFullBurn, &ExitFullBurn)
    STATE_MAP_ENTRY_ALL_EX(&FinalVenting, nullptr, &EnterFinalVenting, &ExitFinalVenting)
    STATE_MAP_ENTRY_ALL_EX(&Done, nullptr, &EnterDone, nullptr)
    STATE_MAP_ENTRY_ALL_EX(&AbortFilling, nullptr, &EnterAbortFilling, nullptr)
    STATE_MAP_ENTRY_ALL_EX(&AbortBurn, nullptr, &EnterAbortBurn, nullptr)
    STATE_MAP_ENTRY_ALL_EX(&ServoControl, nullptr, &EnterServoControl, nullptr)
    END_STATE_MAP_EX

    std::shared_ptr<sensorsData> updateInterface(const UOSMData *smdata, States state);

    void logValveStatus(std::string valveName, bool status);
};