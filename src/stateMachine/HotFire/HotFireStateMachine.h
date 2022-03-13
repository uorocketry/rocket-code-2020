#pragma once

#include "common/pch.h"
#include "data/UOSMData.h"
#include "stateMachine/InterfacingStateMachine.h"

class HotFireStateMachine : public InterfacingStateMachine
{
  public:
    HotFireStateMachine(Interface *anInterface);

    // External events taken by this state machine
    void ReadyEXT();
    void StartFillingEXT();
    void AbortEXT();
    void StopFillingEXT();
    void IgnitionEXT();
    void FinalVentingEXT();
    void DoneEXT();
    void ServoControlEXT();

    void updateHotFire(UOSMData &data);
    void updateHeater(const std::shared_ptr<sensorsData> &interfaceData);

  private:
    void detectConnectionTimeout(const std::shared_ptr<sensorsData> &data);
    void detectExternEvent(const std::shared_ptr<sensorsData> &data);

    std::shared_ptr<spdlog::logger> logger;
    bool heaterOn = false;

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
    STATE_DECLARE(HotFireStateMachine, Init, UOSMData)
    EXIT_DECLARE(HotFireStateMachine, ExitInit)
    // WaitForInit
    ENTRY_DECLARE(HotFireStateMachine, EnterWaitForInit, UOSMData)
    STATE_DECLARE(HotFireStateMachine, WaitForInit, UOSMData)
    EXIT_DECLARE(HotFireStateMachine, ExitWaitForInit)
    // WaitForReady
    ENTRY_DECLARE(HotFireStateMachine, EnterWaitForReady, UOSMData)
    STATE_DECLARE(HotFireStateMachine, WaitForReady, UOSMData)
    EXIT_DECLARE(HotFireStateMachine, ExitWaitForReady)
    // WaitForFilling
    ENTRY_DECLARE(HotFireStateMachine, EnterWaitForFilling, UOSMData)
    STATE_DECLARE(HotFireStateMachine, WaitForFilling, UOSMData)
    EXIT_DECLARE(HotFireStateMachine, ExitWaitForFilling)
    // Filling
    ENTRY_DECLARE(HotFireStateMachine, EnterFilling, UOSMData)
    STATE_DECLARE(HotFireStateMachine, Filling, UOSMData)
    EXIT_DECLARE(HotFireStateMachine, ExitFilling)
    // WaitForIgnition
    ENTRY_DECLARE(HotFireStateMachine, EnterWaitForIgnition, UOSMData)
    STATE_DECLARE(HotFireStateMachine, WaitForIgnition, UOSMData)
    EXIT_DECLARE(HotFireStateMachine, ExitWaitForIgnition)
    // Ignition
    ENTRY_DECLARE(HotFireStateMachine, EnterIgnition, UOSMData)
    STATE_DECLARE(HotFireStateMachine, Ignition, UOSMData)
    EXIT_DECLARE(HotFireStateMachine, ExitIgnition)
    // FullBurn
    ENTRY_DECLARE(HotFireStateMachine, EnterFullBurn, UOSMData)
    STATE_DECLARE(HotFireStateMachine, FullBurn, UOSMData)
    EXIT_DECLARE(HotFireStateMachine, ExitFullBurn)
    // FinalVenting
    ENTRY_DECLARE(HotFireStateMachine, EnterFinalVenting, UOSMData)
    STATE_DECLARE(HotFireStateMachine, FinalVenting, UOSMData)
    EXIT_DECLARE(HotFireStateMachine, ExitFinalVenting)
    // Done
    ENTRY_DECLARE(HotFireStateMachine, EnterDone, UOSMData)
    STATE_DECLARE(HotFireStateMachine, Done, UOSMData)
    // AbortFilling
    ENTRY_DECLARE(HotFireStateMachine, EnterAbortFilling, UOSMData)
    STATE_DECLARE(HotFireStateMachine, AbortFilling, UOSMData)
    // AbortBurn
    ENTRY_DECLARE(HotFireStateMachine, EnterAbortBurn, UOSMData)
    STATE_DECLARE(HotFireStateMachine, AbortBurn, UOSMData)
    // ServoControl
    ENTRY_DECLARE(HotFireStateMachine, EnterServoControl, UOSMData)
    STATE_DECLARE(HotFireStateMachine, ServoControl, UOSMData)

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