// MESSAGE HOTFIRE_STATE support class

#pragma once

namespace mavlink {
namespace uorocketry {
namespace msg {

/**
 * @brief HOTFIRE_STATE message
 *
 * Hotfire State
 */
struct HOTFIRE_STATE : mavlink::Message {
    static constexpr msgid_t MSG_ID = 50000;
    static constexpr size_t LENGTH = 35;
    static constexpr size_t MIN_LENGTH = 35;
    static constexpr uint8_t CRC_EXTRA = 197;
    static constexpr auto NAME = "HOTFIRE_STATE";


    uint64_t timestamp; /*< [ms] The timestamp. This is from a monotonic clock, so may be
                different from the current UTC time.
             */
    uint16_t current_state; /*<  Current state of the State Machine */
    int16_t heater_target; /*<  Heater Target */
    int16_t filling_valve_target; /*<  Filling Valve Target */
    int16_t main_valve_target; /*<  Main Valve Target */
    int16_t fill_cart_venting_valve_target; /*<  Fill Cart Venting Valve Target */
    int16_t pinhole_venting_valve_target; /*<  Valve Filling Target */
    int16_t heater_state; /*<  Heater State */
    int16_t filling_valve_state; /*<  Filling Valve State */
    int16_t main_valve_state; /*<  Main Valve State */
    int16_t fill_cart_venting_valve_state; /*<  Fill Cart Venting Valve State */
    int16_t pinhole_venting_valve_state; /*<  Valve Filling State */
    uint8_t log_status; /*<  Log Status */
    float temperature; /*<  Temperature */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  timestamp: " << timestamp << std::endl;
        ss << "  current_state: " << current_state << std::endl;
        ss << "  heater_target: " << heater_target << std::endl;
        ss << "  filling_valve_target: " << filling_valve_target << std::endl;
        ss << "  main_valve_target: " << main_valve_target << std::endl;
        ss << "  fill_cart_venting_valve_target: " << fill_cart_venting_valve_target << std::endl;
        ss << "  pinhole_venting_valve_target: " << pinhole_venting_valve_target << std::endl;
        ss << "  heater_state: " << heater_state << std::endl;
        ss << "  filling_valve_state: " << filling_valve_state << std::endl;
        ss << "  main_valve_state: " << main_valve_state << std::endl;
        ss << "  fill_cart_venting_valve_state: " << fill_cart_venting_valve_state << std::endl;
        ss << "  pinhole_venting_valve_state: " << pinhole_venting_valve_state << std::endl;
        ss << "  log_status: " << +log_status << std::endl;
        ss << "  temperature: " << temperature << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << timestamp;                     // offset: 0
        map << temperature;                   // offset: 8
        map << current_state;                 // offset: 12
        map << heater_target;                 // offset: 14
        map << filling_valve_target;          // offset: 16
        map << main_valve_target;             // offset: 18
        map << fill_cart_venting_valve_target; // offset: 20
        map << pinhole_venting_valve_target;  // offset: 22
        map << heater_state;                  // offset: 24
        map << filling_valve_state;           // offset: 26
        map << main_valve_state;              // offset: 28
        map << fill_cart_venting_valve_state; // offset: 30
        map << pinhole_venting_valve_state;   // offset: 32
        map << log_status;                    // offset: 34
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> timestamp;                     // offset: 0
        map >> temperature;                   // offset: 8
        map >> current_state;                 // offset: 12
        map >> heater_target;                 // offset: 14
        map >> filling_valve_target;          // offset: 16
        map >> main_valve_target;             // offset: 18
        map >> fill_cart_venting_valve_target; // offset: 20
        map >> pinhole_venting_valve_target;  // offset: 22
        map >> heater_state;                  // offset: 24
        map >> filling_valve_state;           // offset: 26
        map >> main_valve_state;              // offset: 28
        map >> fill_cart_venting_valve_state; // offset: 30
        map >> pinhole_venting_valve_state;   // offset: 32
        map >> log_status;                    // offset: 34
    }
};

} // namespace msg
} // namespace uorocketry
} // namespace mavlink
