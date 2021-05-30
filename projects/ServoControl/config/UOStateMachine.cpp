#define NOMINMAX // Fix issues on Windows with std:min and std:max

#include <wiringPi.h>
#include "config/config.h"
#include "config/GpioConfig.h"
#include "UOStateMachine.h"
#include <iostream>
#include "data/sensorsData.h"
#include "helpers/Types.h"
#include "data/GpioData.h"
#include <spdlog/spdlog.h>

UOStateMachine::UOStateMachine(Interface* anInterface) :
        InterfacingStateMachine(anInterface, ST_MAX_STATES)
{
    // There is no state entry function for the first state
    enterNewState(States(0));

    logger = spdlog::default_logger();
}

// Code for each state. Do not put while in them. The right function according to the current state
// will be call in the main loop.

STATE_DEFINE(UOStateMachine, Init, UOSMData)
{
    interface->initialize();

    #if USE_GPIO == 1

        #if USE_PWM1 == 1
            interface->createNewGpioPwmOutput(PWM1_NAME, PWM1_PIN, PWM1_SOFTPWM);
        #endif

        #if USE_PWM2 == 1
            interface->createNewGpioPwmOutput(PWM2_NAME, PWM2_PIN, PWM2_SOFTPWM);
        #endif

        #if USE_OUT1 == 1
            interface->createNewGpioOutput(OUT1_NAME, OUT1_PIN);
        #endif

    #endif

    InternalEvent(ST_WAIT_FOR_INIT);
}

EXIT_DEFINE(UOStateMachine, ExitInit)
{
    SPDLOG_LOGGER_INFO(logger, "ServoControlSM::ExitInit");
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForInit, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "ServoControlSM::EnterWaitForInit");
    enterNewState(ST_WAIT_FOR_INIT);
}

STATE_DEFINE(UOStateMachine, WaitForInit, UOSMData)
{
    interfaceData = updateInterface(data, ST_WAIT_FOR_INIT);

    if (interfaceData->isInitialized())
    {
        InternalEvent(ST_CONTROL);
    }

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForInit)
{
    SPDLOG_LOGGER_INFO(logger, "ServoControlSM::ExitWaitForInit");
}

ENTRY_DEFINE(UOStateMachine, EnterControl, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "ServoControlSM::EnterControl");
    enterNewState(ST_CONTROL);
}

STATE_DEFINE(UOStateMachine, Control, UOSMData)
{
    interfaceData = updateInterface(data, ST_CONTROL);

    eventType eventNbr = interfaceData->eventNumber;

    /*
     * GPIO event number, a 4 bit binary number where the
     * 1st bit is the enable bit and the last 3 control
     * whether the PWM2, PWM1, and OUT1 are open/closed.
     * A '1' means to open the valve and a '0' to close it.
     *
     * 0 0 0 0
     * | | | ^--------- Enable bit
     * | | ^----------- OUT1
     * | ^------------- PWM1
     * ^--------------- PWM2
     */

    #if USE_GPIO == 1
        GpioData& gpioData = interfaceData->gpioData;

        // Check if enable bit is set
        bool enabled = eventNbr > 0 && (eventNbr & EVENT_ENABLE_MASK);

        #if USE_OUT1 == 1
            if (enabled)
            {
                // Open OUT1 is the first bit is set
                bool open = eventNbr & OUT1_EVENT_ENABLE_MASK;

                gpioData.digitalOutputMap.insert({OUT1_NAME, open ? OUT1_OPEN : OUT1_CLOSE});

                std::cout << "ServoControlSM::Control OUT1 " << (open ? "OPEN" : "CLOSE") << "\n";
            }
        #endif

        #if USE_PWM1 == 1
            if (enabled)
            {
                // Open PWM2 if the second bit is set
                bool open = eventNbr & PWM1_EVENT_ENABLE_MASK;

                gpioData.pwmOutputMap.insert({PWM1_NAME, open ? PWM1_OPEN : PWM1_CLOSE});

                std::cout << "ServoControlSM::Control PWM1 " << (open ? "OPEN" : "CLOSE") << "\n";
            }
        #endif

        #if USE_PWM2 == 1
            if (enabled)
            {
                // Open PWM2 if the third bit is set
                bool open = eventNbr & PWM2_EVENT_ENABLE_MASK;

                gpioData.pwmOutputMap.insert({PWM2_NAME, open ? PWM2_OPEN : PWM2_CLOSE});

                std::cout << "ServoControlSM::Control PWM2 " << (open ? "OPEN" : "CLOSE") << "\n";
            }
        #endif

    #endif

    interface->updateOutputs(interfaceData);
}

void UOStateMachine::updateHotFire(UOSMData *data)
{
    ExecuteCurrentState(data);
}

std::shared_ptr<sensorsData> UOStateMachine::updateInterface(const UOSMData *smdata, States state)
{
    interface->updateInputs();
    std::shared_ptr<sensorsData> data = interface->getLatest();

    // If statement to prevent overwiring data from TESTING
    if (data->timeStamp == -1) data->timeStamp = smdata->now.time_since_epoch().count();

    data->currentStateNo = state;

    return data;
}
