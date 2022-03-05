#include "StateMachine.h"
//----------------------------------------------------------------------------
// StateMachine
//----------------------------------------------------------------------------
StateMachine::StateMachine(uint8_t maxStates, uint8_t initialState): MAX_STATES(maxStates), m_currentState(initialState)
{
    BOOST_ASSERT(MAX_STATES < EVENT_IGNORED);
}

//----------------------------------------------------------------------------
// ExternalEvent
//----------------------------------------------------------------------------
void StateMachine::ExternalEvent(uint8_t newState, const EventData &pData)
{
    if (newState != EVENT_IGNORED)
        InternalEvent(newState, pData);
}

//----------------------------------------------------------------------------
// InternalEvent
//----------------------------------------------------------------------------
void StateMachine::InternalEvent(uint8_t newState, const EventData &pData)
{
    m_eventGenerated = true;
    m_newState = newState;

    // Execute the state engine. This function call will only return
    // when all state machine events are processed.
    StateEngine(pData);
}

//----------------------------------------------------------------------------
// StateEngine
//----------------------------------------------------------------------------
void StateMachine::StateEngine(const EventData &pData)
{
    const StateMapRow *pStateMap = GetStateMap();
    if (pStateMap != nullptr)
        StateEngine(pStateMap);
    else
    {
        const StateMapRowEx *pStateMapEx = GetStateMapEx();
        BOOST_ASSERT(pStateMapEx != nullptr);
        StateEngine(pStateMapEx, pData);
    }
}

//----------------------------------------------------------------------------
// StateEngine
//----------------------------------------------------------------------------
void StateMachine::StateEngine(const StateMapRow *const pStateMap)
{
#if EXTERNAL_EVENT_NO_HEAP_DATA
    bool externalEvent = true;
#endif
    const EventData *pDataTemp = nullptr;

    // While events are being generated keep executing states
    while (m_eventGenerated)
    {
        // Error check that the new state is valid before proceeding
        BOOST_ASSERT(m_newState < MAX_STATES);

        // Get the pointer from the state map
        const StateBase *state = pStateMap[m_newState].State;

        // Event used up, reset the flag
        m_eventGenerated = false;

        // Switch to the new current state
        SetCurrentState(m_newState);

        // Execute the state action passing in event data
        BOOST_ASSERT(state != nullptr);

        // we don't want to execute the StateAction because the ExecuteCurrentState
        // method will do it state->InvokeStateAction(this, pDataTemp);
    }
}

//----------------------------------------------------------------------------
// StateEngine
//----------------------------------------------------------------------------
void StateMachine::StateEngine(const StateMapRowEx *const pStateMapEx, const EventData& data)
{
    // While events are being generated keep executing states
    while (m_eventGenerated)
    {
        // Error check that the new state is valid before proceeding
        BOOST_ASSERT(m_newState < MAX_STATES);

        // Get the pointers from the state map
        const StateBase *state = pStateMapEx[m_newState].State;
        const GuardBase *guard = pStateMapEx[m_newState].Guard;
        const EntryBase *entry = pStateMapEx[m_newState].Entry;
        const ExitBase *exit = pStateMapEx[m_currentState].Exit;


        // Event used up, reset the flag
        m_eventGenerated = false;

        // Execute the guard condition
        bool guardResult = true;
        if (guard)
            guardResult = guard->InvokeGuardCondition(this, data);

        // If the guard condition succeeds
        if (guardResult)
        {
            // Transitioning to a new state?
            bool transitioning = (m_newState != m_currentState);
            if (transitioning && exit)
                exit->InvokeExitAction(this);

            if (transitioning && entry)
                entry->InvokeEntryAction(this, data);

            // Ensure exit/entry actions didn't call InternalEvent by accident
            if (transitioning)
                BOOST_ASSERT(m_eventGenerated == false);

            // Switch to the new current state
            SetCurrentState(m_newState);

            // Execute the state action passing in event data
            BOOST_ASSERT(state != nullptr);

            // we don't want to execute the StateAction because the
            // ExecuteCurrentState method will do it state->InvokeStateAction(this, pDataTemp);
        }
    }
}

// Execute the ST_StateName function according to the current state
void StateMachine::ExecuteCurrentState(EventData &data)
{
    const StateMapRowEx *pStateMapEx = GetStateMapEx();

    if (pStateMapEx)
    {
        // const EventData* pDataTemp = nullptr;

        const StateBase *state = pStateMapEx[m_currentState].State;

        // execute the function of the state
        state->InvokeStateAction(this, data);
    }
}

/**
 * Custom code added by uORocketry
 */

void StateMachine::updateStateMachine(EventData &data)
{
    ExecuteCurrentState(data);
}