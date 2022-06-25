/** @file
 *    @brief MAVLink comm protocol testsuite generated from uorocketry.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef UOROCKETRY_TESTSUITE_H
#define UOROCKETRY_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_uorocketry(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_common(system_id, component_id, last_msg);
    mavlink_test_uorocketry(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_hotfire_state(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_HOTFIRE_STATE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_hotfire_state_t packet_in = {
        93372036854775807ULL,73.0,17859,17963,18067,18171,18275,18379,18483,18587,18691,18795,18899,235
    };
    mavlink_hotfire_state_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp = packet_in.timestamp;
        packet1.temperature = packet_in.temperature;
        packet1.current_state = packet_in.current_state;
        packet1.heater_target = packet_in.heater_target;
        packet1.filling_valve_target = packet_in.filling_valve_target;
        packet1.main_valve_target = packet_in.main_valve_target;
        packet1.fill_cart_venting_valve_target = packet_in.fill_cart_venting_valve_target;
        packet1.pinhole_venting_valve_target = packet_in.pinhole_venting_valve_target;
        packet1.heater_state = packet_in.heater_state;
        packet1.filling_valve_state = packet_in.filling_valve_state;
        packet1.main_valve_state = packet_in.main_valve_state;
        packet1.fill_cart_venting_valve_state = packet_in.fill_cart_venting_valve_state;
        packet1.pinhole_venting_valve_state = packet_in.pinhole_venting_valve_state;
        packet1.log_status = packet_in.log_status;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_HOTFIRE_STATE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_HOTFIRE_STATE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hotfire_state_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_hotfire_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hotfire_state_pack(system_id, component_id, &msg , packet1.timestamp , packet1.current_state , packet1.heater_target , packet1.filling_valve_target , packet1.main_valve_target , packet1.fill_cart_venting_valve_target , packet1.pinhole_venting_valve_target , packet1.heater_state , packet1.filling_valve_state , packet1.main_valve_state , packet1.fill_cart_venting_valve_state , packet1.pinhole_venting_valve_state , packet1.log_status , packet1.temperature );
    mavlink_msg_hotfire_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hotfire_state_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp , packet1.current_state , packet1.heater_target , packet1.filling_valve_target , packet1.main_valve_target , packet1.fill_cart_venting_valve_target , packet1.pinhole_venting_valve_target , packet1.heater_state , packet1.filling_valve_state , packet1.main_valve_state , packet1.fill_cart_venting_valve_state , packet1.pinhole_venting_valve_state , packet1.log_status , packet1.temperature );
    mavlink_msg_hotfire_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_hotfire_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hotfire_state_send(MAVLINK_COMM_1 , packet1.timestamp , packet1.current_state , packet1.heater_target , packet1.filling_valve_target , packet1.main_valve_target , packet1.fill_cart_venting_valve_target , packet1.pinhole_venting_valve_target , packet1.heater_state , packet1.filling_valve_state , packet1.main_valve_state , packet1.fill_cart_venting_valve_state , packet1.pinhole_venting_valve_state , packet1.log_status , packet1.temperature );
    mavlink_msg_hotfire_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("HOTFIRE_STATE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_HOTFIRE_STATE) != NULL);
#endif
}

static void mavlink_test_log_message(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LOG_MESSAGE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_log_message_t packet_in = {
        5,72,{ 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228 }
    };
    mavlink_log_message_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.severity = packet_in.severity;
        packet1.length = packet_in.length;
        
        mav_array_memcpy(packet1.data, packet_in.data, sizeof(uint8_t)*90);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LOG_MESSAGE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LOG_MESSAGE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_message_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_log_message_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_message_pack(system_id, component_id, &msg , packet1.severity , packet1.length , packet1.data );
    mavlink_msg_log_message_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_message_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.severity , packet1.length , packet1.data );
    mavlink_msg_log_message_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_log_message_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_message_send(MAVLINK_COMM_1 , packet1.severity , packet1.length , packet1.data );
    mavlink_msg_log_message_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LOG_MESSAGE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LOG_MESSAGE) != NULL);
#endif
}

static void mavlink_test_uorocketry(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_hotfire_state(system_id, component_id, last_msg);
    mavlink_test_log_message(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // UOROCKETRY_TESTSUITE_H
