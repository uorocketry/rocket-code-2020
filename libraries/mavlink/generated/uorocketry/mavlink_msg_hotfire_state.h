#pragma once
// MESSAGE HOTFIRE_STATE PACKING

#define MAVLINK_MSG_ID_HOTFIRE_STATE 50000


typedef struct __mavlink_hotfire_state_t {
 uint64_t timestamp; /*< [ms] The timestamp. This is from a monotonic clock, so may be
                different from the current UTC time.
            */
 float temperature; /*<  Temperature*/
 uint16_t current_state; /*<  Current state of the State Machine*/
 int16_t heater_target; /*<  Heater Target*/
 int16_t filling_valve_target; /*<  Filling Valve Target*/
 int16_t main_valve_target; /*<  Main Valve Target*/
 int16_t fill_cart_venting_valve_target; /*<  Fill Cart Venting Valve Target*/
 int16_t pinhole_venting_valve_target; /*<  Valve Filling Target*/
 int16_t heater_state; /*<  Heater State*/
 int16_t filling_valve_state; /*<  Filling Valve State*/
 int16_t main_valve_state; /*<  Main Valve State*/
 int16_t fill_cart_venting_valve_state; /*<  Fill Cart Venting Valve State*/
 int16_t pinhole_venting_valve_state; /*<  Valve Filling State*/
 uint8_t log_status; /*<  Log Status*/
} mavlink_hotfire_state_t;

#define MAVLINK_MSG_ID_HOTFIRE_STATE_LEN 35
#define MAVLINK_MSG_ID_HOTFIRE_STATE_MIN_LEN 35
#define MAVLINK_MSG_ID_50000_LEN 35
#define MAVLINK_MSG_ID_50000_MIN_LEN 35

#define MAVLINK_MSG_ID_HOTFIRE_STATE_CRC 197
#define MAVLINK_MSG_ID_50000_CRC 197



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_HOTFIRE_STATE { \
    50000, \
    "HOTFIRE_STATE", \
    14, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_hotfire_state_t, timestamp) }, \
         { "current_state", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_hotfire_state_t, current_state) }, \
         { "heater_target", NULL, MAVLINK_TYPE_INT16_T, 0, 14, offsetof(mavlink_hotfire_state_t, heater_target) }, \
         { "filling_valve_target", NULL, MAVLINK_TYPE_INT16_T, 0, 16, offsetof(mavlink_hotfire_state_t, filling_valve_target) }, \
         { "main_valve_target", NULL, MAVLINK_TYPE_INT16_T, 0, 18, offsetof(mavlink_hotfire_state_t, main_valve_target) }, \
         { "fill_cart_venting_valve_target", NULL, MAVLINK_TYPE_INT16_T, 0, 20, offsetof(mavlink_hotfire_state_t, fill_cart_venting_valve_target) }, \
         { "pinhole_venting_valve_target", NULL, MAVLINK_TYPE_INT16_T, 0, 22, offsetof(mavlink_hotfire_state_t, pinhole_venting_valve_target) }, \
         { "heater_state", NULL, MAVLINK_TYPE_INT16_T, 0, 24, offsetof(mavlink_hotfire_state_t, heater_state) }, \
         { "filling_valve_state", NULL, MAVLINK_TYPE_INT16_T, 0, 26, offsetof(mavlink_hotfire_state_t, filling_valve_state) }, \
         { "main_valve_state", NULL, MAVLINK_TYPE_INT16_T, 0, 28, offsetof(mavlink_hotfire_state_t, main_valve_state) }, \
         { "fill_cart_venting_valve_state", NULL, MAVLINK_TYPE_INT16_T, 0, 30, offsetof(mavlink_hotfire_state_t, fill_cart_venting_valve_state) }, \
         { "pinhole_venting_valve_state", NULL, MAVLINK_TYPE_INT16_T, 0, 32, offsetof(mavlink_hotfire_state_t, pinhole_venting_valve_state) }, \
         { "log_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 34, offsetof(mavlink_hotfire_state_t, log_status) }, \
         { "temperature", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_hotfire_state_t, temperature) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_HOTFIRE_STATE { \
    "HOTFIRE_STATE", \
    14, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_hotfire_state_t, timestamp) }, \
         { "current_state", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_hotfire_state_t, current_state) }, \
         { "heater_target", NULL, MAVLINK_TYPE_INT16_T, 0, 14, offsetof(mavlink_hotfire_state_t, heater_target) }, \
         { "filling_valve_target", NULL, MAVLINK_TYPE_INT16_T, 0, 16, offsetof(mavlink_hotfire_state_t, filling_valve_target) }, \
         { "main_valve_target", NULL, MAVLINK_TYPE_INT16_T, 0, 18, offsetof(mavlink_hotfire_state_t, main_valve_target) }, \
         { "fill_cart_venting_valve_target", NULL, MAVLINK_TYPE_INT16_T, 0, 20, offsetof(mavlink_hotfire_state_t, fill_cart_venting_valve_target) }, \
         { "pinhole_venting_valve_target", NULL, MAVLINK_TYPE_INT16_T, 0, 22, offsetof(mavlink_hotfire_state_t, pinhole_venting_valve_target) }, \
         { "heater_state", NULL, MAVLINK_TYPE_INT16_T, 0, 24, offsetof(mavlink_hotfire_state_t, heater_state) }, \
         { "filling_valve_state", NULL, MAVLINK_TYPE_INT16_T, 0, 26, offsetof(mavlink_hotfire_state_t, filling_valve_state) }, \
         { "main_valve_state", NULL, MAVLINK_TYPE_INT16_T, 0, 28, offsetof(mavlink_hotfire_state_t, main_valve_state) }, \
         { "fill_cart_venting_valve_state", NULL, MAVLINK_TYPE_INT16_T, 0, 30, offsetof(mavlink_hotfire_state_t, fill_cart_venting_valve_state) }, \
         { "pinhole_venting_valve_state", NULL, MAVLINK_TYPE_INT16_T, 0, 32, offsetof(mavlink_hotfire_state_t, pinhole_venting_valve_state) }, \
         { "log_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 34, offsetof(mavlink_hotfire_state_t, log_status) }, \
         { "temperature", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_hotfire_state_t, temperature) }, \
         } \
}
#endif

/**
 * @brief Pack a hotfire_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp [ms] The timestamp. This is from a monotonic clock, so may be
                different from the current UTC time.
            
 * @param current_state  Current state of the State Machine
 * @param heater_target  Heater Target
 * @param filling_valve_target  Filling Valve Target
 * @param main_valve_target  Main Valve Target
 * @param fill_cart_venting_valve_target  Fill Cart Venting Valve Target
 * @param pinhole_venting_valve_target  Valve Filling Target
 * @param heater_state  Heater State
 * @param filling_valve_state  Filling Valve State
 * @param main_valve_state  Main Valve State
 * @param fill_cart_venting_valve_state  Fill Cart Venting Valve State
 * @param pinhole_venting_valve_state  Valve Filling State
 * @param log_status  Log Status
 * @param temperature  Temperature
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hotfire_state_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t timestamp, uint16_t current_state, int16_t heater_target, int16_t filling_valve_target, int16_t main_valve_target, int16_t fill_cart_venting_valve_target, int16_t pinhole_venting_valve_target, int16_t heater_state, int16_t filling_valve_state, int16_t main_valve_state, int16_t fill_cart_venting_valve_state, int16_t pinhole_venting_valve_state, uint8_t log_status, float temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HOTFIRE_STATE_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, temperature);
    _mav_put_uint16_t(buf, 12, current_state);
    _mav_put_int16_t(buf, 14, heater_target);
    _mav_put_int16_t(buf, 16, filling_valve_target);
    _mav_put_int16_t(buf, 18, main_valve_target);
    _mav_put_int16_t(buf, 20, fill_cart_venting_valve_target);
    _mav_put_int16_t(buf, 22, pinhole_venting_valve_target);
    _mav_put_int16_t(buf, 24, heater_state);
    _mav_put_int16_t(buf, 26, filling_valve_state);
    _mav_put_int16_t(buf, 28, main_valve_state);
    _mav_put_int16_t(buf, 30, fill_cart_venting_valve_state);
    _mav_put_int16_t(buf, 32, pinhole_venting_valve_state);
    _mav_put_uint8_t(buf, 34, log_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HOTFIRE_STATE_LEN);
#else
    mavlink_hotfire_state_t packet;
    packet.timestamp = timestamp;
    packet.temperature = temperature;
    packet.current_state = current_state;
    packet.heater_target = heater_target;
    packet.filling_valve_target = filling_valve_target;
    packet.main_valve_target = main_valve_target;
    packet.fill_cart_venting_valve_target = fill_cart_venting_valve_target;
    packet.pinhole_venting_valve_target = pinhole_venting_valve_target;
    packet.heater_state = heater_state;
    packet.filling_valve_state = filling_valve_state;
    packet.main_valve_state = main_valve_state;
    packet.fill_cart_venting_valve_state = fill_cart_venting_valve_state;
    packet.pinhole_venting_valve_state = pinhole_venting_valve_state;
    packet.log_status = log_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HOTFIRE_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HOTFIRE_STATE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HOTFIRE_STATE_MIN_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_CRC);
}

/**
 * @brief Pack a hotfire_state message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp [ms] The timestamp. This is from a monotonic clock, so may be
                different from the current UTC time.
            
 * @param current_state  Current state of the State Machine
 * @param heater_target  Heater Target
 * @param filling_valve_target  Filling Valve Target
 * @param main_valve_target  Main Valve Target
 * @param fill_cart_venting_valve_target  Fill Cart Venting Valve Target
 * @param pinhole_venting_valve_target  Valve Filling Target
 * @param heater_state  Heater State
 * @param filling_valve_state  Filling Valve State
 * @param main_valve_state  Main Valve State
 * @param fill_cart_venting_valve_state  Fill Cart Venting Valve State
 * @param pinhole_venting_valve_state  Valve Filling State
 * @param log_status  Log Status
 * @param temperature  Temperature
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_hotfire_state_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t timestamp,uint16_t current_state,int16_t heater_target,int16_t filling_valve_target,int16_t main_valve_target,int16_t fill_cart_venting_valve_target,int16_t pinhole_venting_valve_target,int16_t heater_state,int16_t filling_valve_state,int16_t main_valve_state,int16_t fill_cart_venting_valve_state,int16_t pinhole_venting_valve_state,uint8_t log_status,float temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HOTFIRE_STATE_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, temperature);
    _mav_put_uint16_t(buf, 12, current_state);
    _mav_put_int16_t(buf, 14, heater_target);
    _mav_put_int16_t(buf, 16, filling_valve_target);
    _mav_put_int16_t(buf, 18, main_valve_target);
    _mav_put_int16_t(buf, 20, fill_cart_venting_valve_target);
    _mav_put_int16_t(buf, 22, pinhole_venting_valve_target);
    _mav_put_int16_t(buf, 24, heater_state);
    _mav_put_int16_t(buf, 26, filling_valve_state);
    _mav_put_int16_t(buf, 28, main_valve_state);
    _mav_put_int16_t(buf, 30, fill_cart_venting_valve_state);
    _mav_put_int16_t(buf, 32, pinhole_venting_valve_state);
    _mav_put_uint8_t(buf, 34, log_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HOTFIRE_STATE_LEN);
#else
    mavlink_hotfire_state_t packet;
    packet.timestamp = timestamp;
    packet.temperature = temperature;
    packet.current_state = current_state;
    packet.heater_target = heater_target;
    packet.filling_valve_target = filling_valve_target;
    packet.main_valve_target = main_valve_target;
    packet.fill_cart_venting_valve_target = fill_cart_venting_valve_target;
    packet.pinhole_venting_valve_target = pinhole_venting_valve_target;
    packet.heater_state = heater_state;
    packet.filling_valve_state = filling_valve_state;
    packet.main_valve_state = main_valve_state;
    packet.fill_cart_venting_valve_state = fill_cart_venting_valve_state;
    packet.pinhole_venting_valve_state = pinhole_venting_valve_state;
    packet.log_status = log_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HOTFIRE_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HOTFIRE_STATE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HOTFIRE_STATE_MIN_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_CRC);
}

/**
 * @brief Encode a hotfire_state struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param hotfire_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hotfire_state_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_hotfire_state_t* hotfire_state)
{
    return mavlink_msg_hotfire_state_pack(system_id, component_id, msg, hotfire_state->timestamp, hotfire_state->current_state, hotfire_state->heater_target, hotfire_state->filling_valve_target, hotfire_state->main_valve_target, hotfire_state->fill_cart_venting_valve_target, hotfire_state->pinhole_venting_valve_target, hotfire_state->heater_state, hotfire_state->filling_valve_state, hotfire_state->main_valve_state, hotfire_state->fill_cart_venting_valve_state, hotfire_state->pinhole_venting_valve_state, hotfire_state->log_status, hotfire_state->temperature);
}

/**
 * @brief Encode a hotfire_state struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param hotfire_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_hotfire_state_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_hotfire_state_t* hotfire_state)
{
    return mavlink_msg_hotfire_state_pack_chan(system_id, component_id, chan, msg, hotfire_state->timestamp, hotfire_state->current_state, hotfire_state->heater_target, hotfire_state->filling_valve_target, hotfire_state->main_valve_target, hotfire_state->fill_cart_venting_valve_target, hotfire_state->pinhole_venting_valve_target, hotfire_state->heater_state, hotfire_state->filling_valve_state, hotfire_state->main_valve_state, hotfire_state->fill_cart_venting_valve_state, hotfire_state->pinhole_venting_valve_state, hotfire_state->log_status, hotfire_state->temperature);
}

/**
 * @brief Send a hotfire_state message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp [ms] The timestamp. This is from a monotonic clock, so may be
                different from the current UTC time.
            
 * @param current_state  Current state of the State Machine
 * @param heater_target  Heater Target
 * @param filling_valve_target  Filling Valve Target
 * @param main_valve_target  Main Valve Target
 * @param fill_cart_venting_valve_target  Fill Cart Venting Valve Target
 * @param pinhole_venting_valve_target  Valve Filling Target
 * @param heater_state  Heater State
 * @param filling_valve_state  Filling Valve State
 * @param main_valve_state  Main Valve State
 * @param fill_cart_venting_valve_state  Fill Cart Venting Valve State
 * @param pinhole_venting_valve_state  Valve Filling State
 * @param log_status  Log Status
 * @param temperature  Temperature
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_hotfire_state_send(mavlink_channel_t chan, uint64_t timestamp, uint16_t current_state, int16_t heater_target, int16_t filling_valve_target, int16_t main_valve_target, int16_t fill_cart_venting_valve_target, int16_t pinhole_venting_valve_target, int16_t heater_state, int16_t filling_valve_state, int16_t main_valve_state, int16_t fill_cart_venting_valve_state, int16_t pinhole_venting_valve_state, uint8_t log_status, float temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HOTFIRE_STATE_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, temperature);
    _mav_put_uint16_t(buf, 12, current_state);
    _mav_put_int16_t(buf, 14, heater_target);
    _mav_put_int16_t(buf, 16, filling_valve_target);
    _mav_put_int16_t(buf, 18, main_valve_target);
    _mav_put_int16_t(buf, 20, fill_cart_venting_valve_target);
    _mav_put_int16_t(buf, 22, pinhole_venting_valve_target);
    _mav_put_int16_t(buf, 24, heater_state);
    _mav_put_int16_t(buf, 26, filling_valve_state);
    _mav_put_int16_t(buf, 28, main_valve_state);
    _mav_put_int16_t(buf, 30, fill_cart_venting_valve_state);
    _mav_put_int16_t(buf, 32, pinhole_venting_valve_state);
    _mav_put_uint8_t(buf, 34, log_status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HOTFIRE_STATE, buf, MAVLINK_MSG_ID_HOTFIRE_STATE_MIN_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_CRC);
#else
    mavlink_hotfire_state_t packet;
    packet.timestamp = timestamp;
    packet.temperature = temperature;
    packet.current_state = current_state;
    packet.heater_target = heater_target;
    packet.filling_valve_target = filling_valve_target;
    packet.main_valve_target = main_valve_target;
    packet.fill_cart_venting_valve_target = fill_cart_venting_valve_target;
    packet.pinhole_venting_valve_target = pinhole_venting_valve_target;
    packet.heater_state = heater_state;
    packet.filling_valve_state = filling_valve_state;
    packet.main_valve_state = main_valve_state;
    packet.fill_cart_venting_valve_state = fill_cart_venting_valve_state;
    packet.pinhole_venting_valve_state = pinhole_venting_valve_state;
    packet.log_status = log_status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HOTFIRE_STATE, (const char *)&packet, MAVLINK_MSG_ID_HOTFIRE_STATE_MIN_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_CRC);
#endif
}

/**
 * @brief Send a hotfire_state message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_hotfire_state_send_struct(mavlink_channel_t chan, const mavlink_hotfire_state_t* hotfire_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_hotfire_state_send(chan, hotfire_state->timestamp, hotfire_state->current_state, hotfire_state->heater_target, hotfire_state->filling_valve_target, hotfire_state->main_valve_target, hotfire_state->fill_cart_venting_valve_target, hotfire_state->pinhole_venting_valve_target, hotfire_state->heater_state, hotfire_state->filling_valve_state, hotfire_state->main_valve_state, hotfire_state->fill_cart_venting_valve_state, hotfire_state->pinhole_venting_valve_state, hotfire_state->log_status, hotfire_state->temperature);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HOTFIRE_STATE, (const char *)hotfire_state, MAVLINK_MSG_ID_HOTFIRE_STATE_MIN_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_CRC);
#endif
}

#if MAVLINK_MSG_ID_HOTFIRE_STATE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_hotfire_state_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t timestamp, uint16_t current_state, int16_t heater_target, int16_t filling_valve_target, int16_t main_valve_target, int16_t fill_cart_venting_valve_target, int16_t pinhole_venting_valve_target, int16_t heater_state, int16_t filling_valve_state, int16_t main_valve_state, int16_t fill_cart_venting_valve_state, int16_t pinhole_venting_valve_state, uint8_t log_status, float temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, temperature);
    _mav_put_uint16_t(buf, 12, current_state);
    _mav_put_int16_t(buf, 14, heater_target);
    _mav_put_int16_t(buf, 16, filling_valve_target);
    _mav_put_int16_t(buf, 18, main_valve_target);
    _mav_put_int16_t(buf, 20, fill_cart_venting_valve_target);
    _mav_put_int16_t(buf, 22, pinhole_venting_valve_target);
    _mav_put_int16_t(buf, 24, heater_state);
    _mav_put_int16_t(buf, 26, filling_valve_state);
    _mav_put_int16_t(buf, 28, main_valve_state);
    _mav_put_int16_t(buf, 30, fill_cart_venting_valve_state);
    _mav_put_int16_t(buf, 32, pinhole_venting_valve_state);
    _mav_put_uint8_t(buf, 34, log_status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HOTFIRE_STATE, buf, MAVLINK_MSG_ID_HOTFIRE_STATE_MIN_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_CRC);
#else
    mavlink_hotfire_state_t *packet = (mavlink_hotfire_state_t *)msgbuf;
    packet->timestamp = timestamp;
    packet->temperature = temperature;
    packet->current_state = current_state;
    packet->heater_target = heater_target;
    packet->filling_valve_target = filling_valve_target;
    packet->main_valve_target = main_valve_target;
    packet->fill_cart_venting_valve_target = fill_cart_venting_valve_target;
    packet->pinhole_venting_valve_target = pinhole_venting_valve_target;
    packet->heater_state = heater_state;
    packet->filling_valve_state = filling_valve_state;
    packet->main_valve_state = main_valve_state;
    packet->fill_cart_venting_valve_state = fill_cart_venting_valve_state;
    packet->pinhole_venting_valve_state = pinhole_venting_valve_state;
    packet->log_status = log_status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HOTFIRE_STATE, (const char *)packet, MAVLINK_MSG_ID_HOTFIRE_STATE_MIN_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_LEN, MAVLINK_MSG_ID_HOTFIRE_STATE_CRC);
#endif
}
#endif

#endif

// MESSAGE HOTFIRE_STATE UNPACKING


/**
 * @brief Get field timestamp from hotfire_state message
 *
 * @return [ms] The timestamp. This is from a monotonic clock, so may be
                different from the current UTC time.
            
 */
static inline uint64_t mavlink_msg_hotfire_state_get_timestamp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field current_state from hotfire_state message
 *
 * @return  Current state of the State Machine
 */
static inline uint16_t mavlink_msg_hotfire_state_get_current_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Get field heater_target from hotfire_state message
 *
 * @return  Heater Target
 */
static inline int16_t mavlink_msg_hotfire_state_get_heater_target(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  14);
}

/**
 * @brief Get field filling_valve_target from hotfire_state message
 *
 * @return  Filling Valve Target
 */
static inline int16_t mavlink_msg_hotfire_state_get_filling_valve_target(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  16);
}

/**
 * @brief Get field main_valve_target from hotfire_state message
 *
 * @return  Main Valve Target
 */
static inline int16_t mavlink_msg_hotfire_state_get_main_valve_target(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  18);
}

/**
 * @brief Get field fill_cart_venting_valve_target from hotfire_state message
 *
 * @return  Fill Cart Venting Valve Target
 */
static inline int16_t mavlink_msg_hotfire_state_get_fill_cart_venting_valve_target(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  20);
}

/**
 * @brief Get field pinhole_venting_valve_target from hotfire_state message
 *
 * @return  Valve Filling Target
 */
static inline int16_t mavlink_msg_hotfire_state_get_pinhole_venting_valve_target(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  22);
}

/**
 * @brief Get field heater_state from hotfire_state message
 *
 * @return  Heater State
 */
static inline int16_t mavlink_msg_hotfire_state_get_heater_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  24);
}

/**
 * @brief Get field filling_valve_state from hotfire_state message
 *
 * @return  Filling Valve State
 */
static inline int16_t mavlink_msg_hotfire_state_get_filling_valve_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  26);
}

/**
 * @brief Get field main_valve_state from hotfire_state message
 *
 * @return  Main Valve State
 */
static inline int16_t mavlink_msg_hotfire_state_get_main_valve_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  28);
}

/**
 * @brief Get field fill_cart_venting_valve_state from hotfire_state message
 *
 * @return  Fill Cart Venting Valve State
 */
static inline int16_t mavlink_msg_hotfire_state_get_fill_cart_venting_valve_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  30);
}

/**
 * @brief Get field pinhole_venting_valve_state from hotfire_state message
 *
 * @return  Valve Filling State
 */
static inline int16_t mavlink_msg_hotfire_state_get_pinhole_venting_valve_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  32);
}

/**
 * @brief Get field log_status from hotfire_state message
 *
 * @return  Log Status
 */
static inline uint8_t mavlink_msg_hotfire_state_get_log_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  34);
}

/**
 * @brief Get field temperature from hotfire_state message
 *
 * @return  Temperature
 */
static inline float mavlink_msg_hotfire_state_get_temperature(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a hotfire_state message into a struct
 *
 * @param msg The message to decode
 * @param hotfire_state C-struct to decode the message contents into
 */
static inline void mavlink_msg_hotfire_state_decode(const mavlink_message_t* msg, mavlink_hotfire_state_t* hotfire_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    hotfire_state->timestamp = mavlink_msg_hotfire_state_get_timestamp(msg);
    hotfire_state->temperature = mavlink_msg_hotfire_state_get_temperature(msg);
    hotfire_state->current_state = mavlink_msg_hotfire_state_get_current_state(msg);
    hotfire_state->heater_target = mavlink_msg_hotfire_state_get_heater_target(msg);
    hotfire_state->filling_valve_target = mavlink_msg_hotfire_state_get_filling_valve_target(msg);
    hotfire_state->main_valve_target = mavlink_msg_hotfire_state_get_main_valve_target(msg);
    hotfire_state->fill_cart_venting_valve_target = mavlink_msg_hotfire_state_get_fill_cart_venting_valve_target(msg);
    hotfire_state->pinhole_venting_valve_target = mavlink_msg_hotfire_state_get_pinhole_venting_valve_target(msg);
    hotfire_state->heater_state = mavlink_msg_hotfire_state_get_heater_state(msg);
    hotfire_state->filling_valve_state = mavlink_msg_hotfire_state_get_filling_valve_state(msg);
    hotfire_state->main_valve_state = mavlink_msg_hotfire_state_get_main_valve_state(msg);
    hotfire_state->fill_cart_venting_valve_state = mavlink_msg_hotfire_state_get_fill_cart_venting_valve_state(msg);
    hotfire_state->pinhole_venting_valve_state = mavlink_msg_hotfire_state_get_pinhole_venting_valve_state(msg);
    hotfire_state->log_status = mavlink_msg_hotfire_state_get_log_status(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_HOTFIRE_STATE_LEN? msg->len : MAVLINK_MSG_ID_HOTFIRE_STATE_LEN;
        memset(hotfire_state, 0, MAVLINK_MSG_ID_HOTFIRE_STATE_LEN);
    memcpy(hotfire_state, _MAV_PAYLOAD(msg), len);
#endif
}
