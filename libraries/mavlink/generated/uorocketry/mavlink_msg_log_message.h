#pragma once
// MESSAGE LOG_MESSAGE PACKING

#define MAVLINK_MSG_ID_LOG_MESSAGE 50001


typedef struct __mavlink_log_message_t {
 uint8_t severity; /*<  Severity of the message*/
 uint8_t length; /*<  The length of the log contained in data*/
 uint8_t data[90]; /*<  The actual log*/
} mavlink_log_message_t;

#define MAVLINK_MSG_ID_LOG_MESSAGE_LEN 92
#define MAVLINK_MSG_ID_LOG_MESSAGE_MIN_LEN 92
#define MAVLINK_MSG_ID_50001_LEN 92
#define MAVLINK_MSG_ID_50001_MIN_LEN 92

#define MAVLINK_MSG_ID_LOG_MESSAGE_CRC 112
#define MAVLINK_MSG_ID_50001_CRC 112

#define MAVLINK_MSG_LOG_MESSAGE_FIELD_DATA_LEN 90

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LOG_MESSAGE { \
    50001, \
    "LOG_MESSAGE", \
    3, \
    {  { "severity", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_log_message_t, severity) }, \
         { "length", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_log_message_t, length) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 90, 2, offsetof(mavlink_log_message_t, data) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LOG_MESSAGE { \
    "LOG_MESSAGE", \
    3, \
    {  { "severity", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_log_message_t, severity) }, \
         { "length", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_log_message_t, length) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 90, 2, offsetof(mavlink_log_message_t, data) }, \
         } \
}
#endif

/**
 * @brief Pack a log_message message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param severity  Severity of the message
 * @param length  The length of the log contained in data
 * @param data  The actual log
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_log_message_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t severity, uint8_t length, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOG_MESSAGE_LEN];
    _mav_put_uint8_t(buf, 0, severity);
    _mav_put_uint8_t(buf, 1, length);
    _mav_put_uint8_t_array(buf, 2, data, 90);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOG_MESSAGE_LEN);
#else
    mavlink_log_message_t packet;
    packet.severity = severity;
    packet.length = length;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*90);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LOG_MESSAGE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LOG_MESSAGE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LOG_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_CRC);
}

/**
 * @brief Pack a log_message message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param severity  Severity of the message
 * @param length  The length of the log contained in data
 * @param data  The actual log
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_log_message_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t severity,uint8_t length,const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOG_MESSAGE_LEN];
    _mav_put_uint8_t(buf, 0, severity);
    _mav_put_uint8_t(buf, 1, length);
    _mav_put_uint8_t_array(buf, 2, data, 90);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOG_MESSAGE_LEN);
#else
    mavlink_log_message_t packet;
    packet.severity = severity;
    packet.length = length;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*90);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LOG_MESSAGE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LOG_MESSAGE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LOG_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_CRC);
}

/**
 * @brief Encode a log_message struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param log_message C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_log_message_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_log_message_t* log_message)
{
    return mavlink_msg_log_message_pack(system_id, component_id, msg, log_message->severity, log_message->length, log_message->data);
}

/**
 * @brief Encode a log_message struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param log_message C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_log_message_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_log_message_t* log_message)
{
    return mavlink_msg_log_message_pack_chan(system_id, component_id, chan, msg, log_message->severity, log_message->length, log_message->data);
}

/**
 * @brief Send a log_message message
 * @param chan MAVLink channel to send the message
 *
 * @param severity  Severity of the message
 * @param length  The length of the log contained in data
 * @param data  The actual log
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_log_message_send(mavlink_channel_t chan, uint8_t severity, uint8_t length, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOG_MESSAGE_LEN];
    _mav_put_uint8_t(buf, 0, severity);
    _mav_put_uint8_t(buf, 1, length);
    _mav_put_uint8_t_array(buf, 2, data, 90);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOG_MESSAGE, buf, MAVLINK_MSG_ID_LOG_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_CRC);
#else
    mavlink_log_message_t packet;
    packet.severity = severity;
    packet.length = length;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*90);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOG_MESSAGE, (const char *)&packet, MAVLINK_MSG_ID_LOG_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_CRC);
#endif
}

/**
 * @brief Send a log_message message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_log_message_send_struct(mavlink_channel_t chan, const mavlink_log_message_t* log_message)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_log_message_send(chan, log_message->severity, log_message->length, log_message->data);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOG_MESSAGE, (const char *)log_message, MAVLINK_MSG_ID_LOG_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_CRC);
#endif
}

#if MAVLINK_MSG_ID_LOG_MESSAGE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_log_message_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t severity, uint8_t length, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, severity);
    _mav_put_uint8_t(buf, 1, length);
    _mav_put_uint8_t_array(buf, 2, data, 90);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOG_MESSAGE, buf, MAVLINK_MSG_ID_LOG_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_CRC);
#else
    mavlink_log_message_t *packet = (mavlink_log_message_t *)msgbuf;
    packet->severity = severity;
    packet->length = length;
    mav_array_memcpy(packet->data, data, sizeof(uint8_t)*90);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOG_MESSAGE, (const char *)packet, MAVLINK_MSG_ID_LOG_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_LEN, MAVLINK_MSG_ID_LOG_MESSAGE_CRC);
#endif
}
#endif

#endif

// MESSAGE LOG_MESSAGE UNPACKING


/**
 * @brief Get field severity from log_message message
 *
 * @return  Severity of the message
 */
static inline uint8_t mavlink_msg_log_message_get_severity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field length from log_message message
 *
 * @return  The length of the log contained in data
 */
static inline uint8_t mavlink_msg_log_message_get_length(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field data from log_message message
 *
 * @return  The actual log
 */
static inline uint16_t mavlink_msg_log_message_get_data(const mavlink_message_t* msg, uint8_t *data)
{
    return _MAV_RETURN_uint8_t_array(msg, data, 90,  2);
}

/**
 * @brief Decode a log_message message into a struct
 *
 * @param msg The message to decode
 * @param log_message C-struct to decode the message contents into
 */
static inline void mavlink_msg_log_message_decode(const mavlink_message_t* msg, mavlink_log_message_t* log_message)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    log_message->severity = mavlink_msg_log_message_get_severity(msg);
    log_message->length = mavlink_msg_log_message_get_length(msg);
    mavlink_msg_log_message_get_data(msg, log_message->data);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LOG_MESSAGE_LEN? msg->len : MAVLINK_MSG_ID_LOG_MESSAGE_LEN;
        memset(log_message, 0, MAVLINK_MSG_ID_LOG_MESSAGE_LEN);
    memcpy(log_message, _MAV_PAYLOAD(msg), len);
#endif
}
