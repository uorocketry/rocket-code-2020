#pragma once

#include "config/config.h"
#include "data/UOSMData.h"
#include "stateMachine/InterfacingStateMachine.h"

#include "helpers/Types.h"

class UOStateMachine : public InterfacingStateMachine
{
  public:
    UOStateMachine(Interface *anInterface);

    // External events taken by this state machine
    // void Apogee(UOSMData* data);
    void Launch();
    void MotorBurnout();
    void Apogee();
    void Touchdown();

  private:
    void detectExternEvent(const std::shared_ptr<sensorsData> &data);
    void detectApogee(const std::shared_ptr<sensorsData> &data);
    void detectLaunch(const std::shared_ptr<sensorsData> &data);
    void detectMotorBurnout(const std::shared_ptr<sensorsData> &data);
    void detectTouchdown(const std::shared_ptr<sensorsData> &data);

    static void showInfo(const std::shared_ptr<sensorsData> &data);

    std::shared_ptr<spdlog::logger> logger;

    // number of consecutive readings needed to trigger apogee
    uint8_t ApogeeThreshold = 5;

    // number of consecutive readings needed to trigger launch
    uint8_t LaunchThreshold = 5;

    // number of consecutive readings needed to trigger motor burnout
    uint8_t BurnOutThreshold = 5;

    // number of consecutive readings needed to trigger touchdown
    uint8_t TouchdownThreshold = 5;

    // State enumeration order must match the order of state method entries
    // in the state map.
    enum States
    {
        ST_INIT,
        ST_WAIT_FOR_INIT,
        ST_WAIT_FOR_LAUNCH,
        ST_POWERED_FLIGHT,
        ST_COAST,
        ST_DESCENT_PHASE_1,
        ST_DESCENT_PHASE_2,
        ST_GROUND,
        ST_MAX_STATES
    };

    // Define the state machine state functions with event data type
    STATE_DECLARE(UOStateMachine, Init, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitInit)

    ENTRY_DECLARE(UOStateMachine, EnterWaitForInit, UOSMData)
    STATE_DECLARE(UOStateMachine, WaitForInit, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitWaitForInit)

    ENTRY_DECLARE(UOStateMachine, EnterWaitForLaunch, UOSMData)
    STATE_DECLARE(UOStateMachine, WaitForLaunch, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitWaitForLaunch)

    ENTRY_DECLARE(UOStateMachine, EnterPoweredFlight, UOSMData)
    STATE_DECLARE(UOStateMachine, PoweredFlight, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitPoweredFlight)

    STATE_DECLARE(UOStateMachine, Coast, UOSMData)
    ENTRY_DECLARE(UOStateMachine, EnterCoast, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitCoast)

    STATE_DECLARE(UOStateMachine, DescentPhase1, UOSMData)
    ENTRY_DECLARE(UOStateMachine, EnterDescentPhase1, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitDescentPhase1)

    STATE_DECLARE(UOStateMachine, DescentPhase2, UOSMData)
    ENTRY_DECLARE(UOStateMachine, EnterDescentPhase2, UOSMData)
    EXIT_DECLARE(UOStateMachine, ExitDescentPhase2)

    STATE_DECLARE(UOStateMachine, Ground, UOSMData)
    ENTRY_DECLARE(UOStateMachine, EnterGround, UOSMData)

    // State map to define state object order. Each state map entry defines a
    // state object.
    BEGIN_STATE_MAP_EX
    STATE_MAP_ENTRY_ALL_EX(&Init, nullptr, nullptr, &ExitInit)
    STATE_MAP_ENTRY_ALL_EX(&WaitForInit, nullptr, &EnterWaitForInit, &ExitWaitForInit)
    STATE_MAP_ENTRY_ALL_EX(&WaitForLaunch, nullptr, &EnterWaitForLaunch, &ExitWaitForLaunch)
    STATE_MAP_ENTRY_ALL_EX(&PoweredFlight, nullptr, &EnterPoweredFlight, &ExitPoweredFlight)
    STATE_MAP_ENTRY_ALL_EX(&Coast, nullptr, &EnterCoast, &ExitCoast)
    STATE_MAP_ENTRY_ALL_EX(&DescentPhase1, nullptr, &EnterDescentPhase1, &ExitDescentPhase1)
    STATE_MAP_ENTRY_ALL_EX(&DescentPhase2, nullptr, &EnterDescentPhase2, &ExitDescentPhase2)
    STATE_MAP_ENTRY_ALL_EX(&Ground, nullptr, &EnterGround, nullptr)
    END_STATE_MAP_EX

    std::shared_ptr<sensorsData> updateInterface(const UOSMData *smdata, States state);
};