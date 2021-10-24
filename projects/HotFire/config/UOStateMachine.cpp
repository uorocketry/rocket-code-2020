#define NOMINMAX // Fix issues on Windows with std:min and std:max

#include "UOStateMachine.h"
#include "config/GpioConfig.h"
#include "config/config.h"
#include "data/GpioData.h"
#include "data/sensorsData.h"
#include "helpers/Types.h"
#include <iostream>
#include <spdlog/spdlog.h>

UOStateMachine::UOStateMachine(Interface *anInterface) : InterfacingStateMachine(anInterface, ST_MAX_STATES)
{

    // There is no state entry function for the first state
    enterNewState(States(0));

    logger = spdlog::default_logger();
}

// StartFilling external event
void UOStateMachine::StartFillingEXT()
{
    BEGIN_TRANSITION_MAP                    // - Current State -
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_INIT
        TRANSITION_MAP_ENTRY(ST_FILLING)    // ST_WAIT_FOR_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FULL_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FINAL_VENTING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DONE
        TRANSITION_MAP_ENTRY(ST_FILLING)    // ST_ABORT_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_SERVO_CONTROL
        END_TRANSITION_MAP(nullptr)
}

// Abort external event
void UOStateMachine::AbortEXT()
{
    BEGIN_TRANSITION_MAP                       // - Current State -
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_WAIT_FOR_INIT
        TRANSITION_MAP_ENTRY(ST_ABORT_FILLING) // ST_WAIT_FOR_FILLING
        TRANSITION_MAP_ENTRY(ST_ABORT_FILLING) // ST_FILLING
        TRANSITION_MAP_ENTRY(ST_ABORT_FILLING) // ST_WAIT_FOR_IGNITION
        TRANSITION_MAP_ENTRY(ST_ABORT_BURN)    // ST_IGNITION
        TRANSITION_MAP_ENTRY(ST_ABORT_BURN)    // ST_FULL_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_FINAL_VENTING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_DONE
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_ABORT_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_ABORT_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_SERVO_CONTROL
        END_TRANSITION_MAP(nullptr)
}

// StopFilling external event
void UOStateMachine::StopFillingEXT()
{
    BEGIN_TRANSITION_MAP                           // - Current State -
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_WAIT_FOR_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_WAIT_FOR_FILLING
        TRANSITION_MAP_ENTRY(ST_WAIT_FOR_IGNITION) // ST_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_WAIT_FOR_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_FULL_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_FINAL_VENTING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_DONE
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_ABORT_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_ABORT_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_SERVO_CONTROL
        END_TRANSITION_MAP(nullptr)
}

// Ignition external event
void UOStateMachine::IgnitionEXT()
{
    BEGIN_TRANSITION_MAP                    // - Current State -
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FILLING
        TRANSITION_MAP_ENTRY(ST_IGNITION)   // ST_WAIT_FOR_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FULL_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FINAL_VENTING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DONE
        TRANSITION_MAP_ENTRY(ST_IGNITION)   // ST_ABORT_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_SERVO_CONTROL
        END_TRANSITION_MAP(nullptr)
}

// FinalVenting external event
void UOStateMachine::FinalVentingEXT()
{
    BEGIN_TRANSITION_MAP                       // - Current State -
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_WAIT_FOR_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_WAIT_FOR_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_WAIT_FOR_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_IGNITION
        TRANSITION_MAP_ENTRY(ST_FINAL_VENTING) // ST_FULL_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_FINAL_VENTING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_DONE
        TRANSITION_MAP_ENTRY(ST_FINAL_VENTING) // ST_ABORT_FILLING
        TRANSITION_MAP_ENTRY(ST_FINAL_VENTING) // ST_ABORT_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_SERVO_CONTROL
        END_TRANSITION_MAP(nullptr)
}

// Done external event
void UOStateMachine::DoneEXT()
{
    BEGIN_TRANSITION_MAP                    // - Current State -
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FULL_BURN
        TRANSITION_MAP_ENTRY(ST_DONE)       // ST_FINAL_VENTING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DONE
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_SERVO_CONTROL
        END_TRANSITION_MAP(nullptr)
}

// Done external event
// clang-format off
void UOStateMachine::ServoControlEXT() {
    BEGIN_TRANSITION_MAP                       // - Current State -
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_INIT
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_WAIT_FOR_INIT
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_WAIT_FOR_FILLING
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_FILLING
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_WAIT_FOR_IGNITION
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_IGNITION
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_FULL_BURN
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_FINAL_VENTING
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_DONE
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_ABORT_FILLING
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_ABORT_BURN
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_SERVO_CONTROL
    END_TRANSITION_MAP(nullptr)
} // clang-format on

// Code for each state. Do not put while in them. The right function according
// to the current state will be call in the main loop.

STATE_DEFINE(UOStateMachine, Init, UOSMData)
{
    interface->initialize();
#if USE_GPIO == 1

#if USE_SV01
    interface->createNewGpioOutput(SV01_NAME, SV01_PIN);
#endif

#if USE_SV02
    interface->createNewGpioOutput(SV02_NAME, SV02_PIN);
#endif

#if USE_PWM_SBV01
    interface->createNewGpioPwmOutput(SBV01_NAME, SBV01_PIN, SBV01_SAFE, SBV01_SOFTPWM);
#endif

#if USE_PWM_SBV02
    interface->createNewGpioPwmOutput(SBV02_NAME, SBV02_PIN, SBV02_SAFE, SBV02_SOFTPWM);
#endif

#if USE_PWM_SBV03
    interface->createNewGpioPwmOutput(SBV03_NAME, SBV03_PIN, SBV03_SAFE, SBV03_SOFTPWM);
#endif

#endif

    InternalEvent(ST_WAIT_FOR_INIT);
}

EXIT_DEFINE(UOStateMachine, ExitInit)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitInit");
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForInit, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterWaitForInit");
    enterNewState(ST_WAIT_FOR_INIT);
}

STATE_DEFINE(UOStateMachine, WaitForInit, UOSMData)
{
    interfaceData = updateInterface(data, ST_WAIT_FOR_INIT);

    if (interfaceData->isInitialized())
    {
        InternalEvent(ST_WAIT_FOR_FILLING);
    }

    // showInfo(interfaceData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForInit)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitWaitForInit");
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForFilling, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterWaitForFilling");
    enterNewState(ST_WAIT_FOR_FILLING);
}

STATE_DEFINE(UOStateMachine, WaitForFilling, UOSMData)
{
    interfaceData = updateInterface(data, ST_WAIT_FOR_FILLING);

#if USE_GPIO == 1
    GpioData &gpioData = interfaceData->gpioData;

#if USE_SV01
    gpioData.digitalOutputMap.insert({SV01_NAME, SV01_CLOSE});
#endif

#if USE_SV02
    gpioData.digitalOutputMap.insert({SV02_NAME, SV02_CLOSE});
#endif

#if USE_PWM_SBV01
    gpioData.pwmOutputMap.insert({SBV01_NAME, SBV01_CLOSE});
#endif

#if USE_PWM_SBV02
    gpioData.pwmOutputMap.insert({SBV02_NAME, SBV02_CLOSE});
#endif

#if USE_PWM_SBV03
    gpioData.pwmOutputMap.insert({SBV03_NAME, SBV03_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForFilling)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitWaitForFilling");
}

ENTRY_DEFINE(UOStateMachine, EnterFilling, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterFilling");
    enterNewState(ST_FILLING);
}

STATE_DEFINE(UOStateMachine, Filling, UOSMData)
{
    interfaceData = updateInterface(data, ST_FILLING);

#if USE_GPIO == 1
    GpioData &gpioData = interfaceData->gpioData;

#if USE_SV01
    gpioData.digitalOutputMap.insert({SV01_NAME, SV01_OPEN});
#endif

#if USE_SV02
    gpioData.digitalOutputMap.insert({SV02_NAME, SV02_CLOSE});
#endif

#if USE_PWM_SBV01
    gpioData.pwmOutputMap.insert({SBV01_NAME, SBV01_CLOSE});
#endif

#if USE_PWM_SBV02
    gpioData.pwmOutputMap.insert({SBV02_NAME, SBV02_OPEN});
#endif

#if USE_PWM_SBV03
    gpioData.pwmOutputMap.insert({SBV03_NAME, SBV03_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitFilling)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitFilling");
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForIgnition, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::WaitForIgnition");
    enterNewState(ST_WAIT_FOR_IGNITION);
}

STATE_DEFINE(UOStateMachine, WaitForIgnition, UOSMData)
{
    interfaceData = updateInterface(data, ST_WAIT_FOR_IGNITION);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_SV01
    gpioData.digitalOutputMap.insert({SV01_NAME, SV01_CLOSE});
#endif

#if USE_SV02
    gpioData.digitalOutputMap.insert({SV02_NAME, SV02_OPEN});
#endif

#if USE_PWM_SBV01
    gpioData.pwmOutputMap.insert({SBV01_NAME, SBV01_CLOSE});
#endif

#if USE_PWM_SBV02
    gpioData.pwmOutputMap.insert({SBV02_NAME, SBV02_CLOSE});
#endif

#if USE_PWM_SBV03
    gpioData.pwmOutputMap.insert({SBV03_NAME, SBV03_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForIgnition)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitWaitForIgnition");
}

ENTRY_DEFINE(UOStateMachine, EnterIgnition, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterIgnition");
    enterNewState(ST_IGNITION);
}

STATE_DEFINE(UOStateMachine, Ignition, UOSMData)
{
    interfaceData = updateInterface(data, ST_IGNITION);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_SV01
    gpioData.digitalOutputMap.insert({SV01_NAME, SV01_CLOSE});
#endif

#if USE_SV02
    gpioData.digitalOutputMap.insert({SV02_NAME, SV02_CLOSE});
#endif

#if USE_PWM_SBV01
    gpioData.pwmOutputMap.insert({SBV01_NAME, SBV01_IGNITION});
#endif

#if USE_PWM_SBV02
    gpioData.pwmOutputMap.insert({SBV02_NAME, SBV02_CLOSE});
#endif

#if USE_PWM_SBV03
    gpioData.pwmOutputMap.insert({SBV03_NAME, SBV03_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);
    switchStatesAfterTime((ST_FULL_BURN), duration_ms(5000));

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitIgnition)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitIgnition");
}

ENTRY_DEFINE(UOStateMachine, EnterFullBurn, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterFullBurn");
    enterNewState(ST_FULL_BURN);
}

STATE_DEFINE(UOStateMachine, FullBurn, UOSMData)
{
    interfaceData = updateInterface(data, ST_FULL_BURN);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_SV01
    gpioData.digitalOutputMap.insert({SV01_NAME, SV01_CLOSE});
#endif

#if USE_SV02
    gpioData.digitalOutputMap.insert({SV02_NAME, SV02_CLOSE});
#endif

#if USE_PWM_SBV01
    gpioData.pwmOutputMap.insert({SBV01_NAME, SBV01_OPEN});
#endif

#if USE_PWM_SBV02
    gpioData.pwmOutputMap.insert({SBV02_NAME, SBV02_CLOSE});
#endif

#if USE_PWM_SBV03
    gpioData.pwmOutputMap.insert({SBV03_NAME, SBV03_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitFullBurn)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitFullBurn");
}

ENTRY_DEFINE(UOStateMachine, EnterFinalVenting, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterFinalVenting");
    enterNewState(ST_FINAL_VENTING);
}

STATE_DEFINE(UOStateMachine, FinalVenting, UOSMData)
{
    interfaceData = updateInterface(data, ST_FINAL_VENTING);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_SV01
    gpioData.digitalOutputMap.insert({SV01_NAME, SV01_OPEN});
#endif

#if USE_SV02
    gpioData.digitalOutputMap.insert({SV02_NAME, SV02_OPEN});
#endif

#if USE_PWM_SBV01
    gpioData.pwmOutputMap.insert({SBV01_NAME, SBV01_CLOSE});
#endif

#if USE_PWM_SBV02
    gpioData.pwmOutputMap.insert({SBV02_NAME, SBV02_OPEN});
#endif

#if USE_PWM_SBV03
    gpioData.pwmOutputMap.insert({SBV03_NAME, SBV03_OPEN});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitFinalVenting)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitFinalVenting");
}

ENTRY_DEFINE(UOStateMachine, EnterDone, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterDone");
    SPDLOG_LOGGER_INFO(logger, "Done.");
    enterNewState(ST_DONE);
}

STATE_DEFINE(UOStateMachine, Done, UOSMData)
{
    interfaceData = updateInterface(data, ST_DONE);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_SV01
    gpioData.digitalOutputMap.insert({SV01_NAME, SV01_CLOSE});
#endif

#if USE_SV02
    gpioData.digitalOutputMap.insert({SV02_NAME, SV02_CLOSE});
#endif

#if USE_PWM_SBV01
    gpioData.pwmOutputMap.insert({SBV01_NAME, SBV01_CLOSE});
#endif

#if USE_PWM_SBV02
    gpioData.pwmOutputMap.insert({SBV02_NAME, SBV02_OPEN});
#endif

#if USE_PWM_SBV03
    gpioData.pwmOutputMap.insert({SBV03_NAME, SBV03_CLOSE});
#endif

#endif

    interface->updateOutputs(interfaceData);
}

ENTRY_DEFINE(UOStateMachine, EnterAbortFilling, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterAbortFilling");
    enterNewState(ST_ABORT_FILLING);
}

STATE_DEFINE(UOStateMachine, AbortFilling, UOSMData)
{
    interfaceData = updateInterface(data, ST_ABORT_FILLING);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_SV01
    gpioData.digitalOutputMap.insert({SV01_NAME, SV01_CLOSE});
#endif

#if USE_SV02
    gpioData.digitalOutputMap.insert({SV02_NAME, SV02_CLOSE});
#endif

#if USE_PWM_SBV01
    gpioData.pwmOutputMap.insert({SBV01_NAME, SBV01_CLOSE});
#endif

#if USE_PWM_SBV02
    gpioData.pwmOutputMap.insert({SBV02_NAME, SBV02_CLOSE});
#endif

#if USE_PWM_SBV03
    gpioData.pwmOutputMap.insert({SBV03_NAME, SBV03_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

ENTRY_DEFINE(UOStateMachine, EnterAbortBurn, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterAbortBurn");
    enterNewState(ST_ABORT_BURN);
}

STATE_DEFINE(UOStateMachine, AbortBurn, UOSMData)
{
    interfaceData = updateInterface(data, ST_ABORT_BURN);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_SV01
    gpioData.digitalOutputMap.insert({SV01_NAME, SV01_CLOSE});
#endif

#if USE_SV02
    gpioData.digitalOutputMap.insert({SV02_NAME, SV02_CLOSE});
#endif

#if USE_PWM_SBV01
    gpioData.pwmOutputMap.insert({SBV01_NAME, SBV01_CLOSE});
#endif

#if USE_PWM_SBV02
    gpioData.pwmOutputMap.insert({SBV02_NAME, SBV02_CLOSE});
#endif

#if USE_PWM_SBV03
    gpioData.pwmOutputMap.insert({SBV03_NAME, SBV03_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

ENTRY_DEFINE(UOStateMachine, EnterServoControl, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterServoControl");
    enterNewState(ST_SERVO_CONTROL);
}

STATE_DEFINE(UOStateMachine, ServoControl, UOSMData)
{
    interfaceData = updateInterface(data, ST_SERVO_CONTROL);

    eventType eventNbr = interfaceData->eventNumber;
    bool dataRecieved = eventNbr > -1;

    if (dataRecieved)
    {
#if USE_GPIO == 1
        GpioData &gpioData = interfaceData->gpioData;

        /*
         * GPIO event number, a 6 bit binary number where the
         * 1st bit is the enable bit and the last 5 control
         * whether the valves are open/closed.
         * A '1' means to open the valve and a '0' to close it.
         *
         * 0 0 0 0 0 0
         * | | | | | ^--------- Enable bit
         * | | | | ^----------- USE_SV01
         * | | | ^------------- USE_SV02
         * | | ^--------------- USE_PWM_SBV01
         * | ^----------------- USE_PWM_SBV02
         * ^------------------- USE_PWM_SBV03
         */

        bool enabled = eventNbr > 0 && (eventNbr & EVENT_ENABLE_MASK);
        if (enabled)
        {

#if USE_SV01 == 1
            {
                bool open = (eventNbr & SV01_EVENT_ENABLE_MASK) > 0;

                gpioData.digitalOutputMap.insert({SV01_NAME, open ? SV01_OPEN : SV01_CLOSE});

                logValveStatus(SV01_NAME, open);
            }
#endif

#if USE_SV02 == 1
            {
                bool open = (eventNbr & SV02_EVENT_ENABLE_MASK) > 0;

                gpioData.digitalOutputMap.insert({SV02_NAME, open ? SV02_OPEN : SV02_CLOSE});

                logValveStatus(SV02_NAME, open);
            }
#endif

#if USE_PWM_SBV01 == 1
            {
                bool open = (eventNbr & SBV01_EVENT_ENABLE_MASK) > 0;

                gpioData.pwmOutputMap.insert({SBV01_NAME, open ? SBV01_OPEN : SBV01_CLOSE});

                logValveStatus(SBV01_NAME, open);
            }
#endif

#if USE_PWM_SBV02 == 1
            {
                bool open = (eventNbr & SBV02_EVENT_ENABLE_MASK) > 0;

                gpioData.pwmOutputMap.insert({SBV02_NAME, open ? SBV02_OPEN : SBV02_CLOSE});

                logValveStatus(SBV02_NAME, open);
            }
#endif

#if USE_PWM_SBV03 == 1
            {
                bool open = (eventNbr & SBV03_EVENT_ENABLE_MASK) > 0;

                gpioData.pwmOutputMap.insert({SBV03_NAME, open ? SBV03_OPEN : SBV03_CLOSE});

                logValveStatus(SBV03_NAME, open);
            }
#endif
        }
        else
        {
            // Switch back to specified state
            InternalEvent(eventNbr >> 1);
        }
#endif
    }

    interface->updateOutputs(interfaceData);
}

void UOStateMachine::logValveStatus(std::string valveName, bool status)
{
    if (status)
    {
        SPDLOG_LOGGER_INFO(logger, "ServoControlSM::Control " + valveName + " OPEN");
    }
    else
    {
        SPDLOG_LOGGER_INFO(logger, "ServoControlSM::Control " + valveName + " CLOSE");
    }
}

void UOStateMachine::detectExternEvent(const std::shared_ptr<sensorsData> &data)
{
    eventType eventNbr = data->eventNumber;

    uint64_t timestamp =
        std::chrono::duration_cast<time_point::duration>(std::chrono::steady_clock::now().time_since_epoch()).count();
    static bool connectionAborted = false;
    if (!connectionAborted && data->lastActiveClientTimestamp != 0 &&
        timestamp - data->lastActiveClientTimestamp > connectionFailsafeTimeout)
    {
        connectionAborted = true;
        SPDLOG_ERROR("TCP Client has been disconnected for too long. Aborting!");
        AbortEXT();
    }

    switch (eventNbr)
    {
    case 0:
        StartFillingEXT();
        break;
    case 1:
        StopFillingEXT();
        break;
    case 2:
        IgnitionEXT();
        break;
    case 3:
        FinalVentingEXT();
        break;
    case 4:
        DoneEXT();
        break;
    case 5:
        AbortEXT();
        break;
    case 6:
        ServoControlEXT();
        break;
    default:
        break;
    }
}

void UOStateMachine::updateHotFire(UOSMData *data)
{
    ExecuteCurrentState(data);
}

std::shared_ptr<sensorsData> UOStateMachine::updateInterface(const UOSMData *smdata, States state)
{
    interface->updateInputs();
    std::shared_ptr<sensorsData> data = interface->getLatest();

    data->currentStateNo = state;

    return data;
}
