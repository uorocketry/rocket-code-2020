/** @file
 *	@brief MAVLink comm testsuite protocol generated from uorocketry.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "uorocketry.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(uorocketry, HOTFIRE_STATE)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::uorocketry::msg::HOTFIRE_STATE packet_in{};
    packet_in.timestamp = 93372036854775807ULL;
    packet_in.current_state = 17859;
    packet_in.heater_target = 17963;
    packet_in.filling_valve_target = 18067;
    packet_in.main_valve_target = 18171;
    packet_in.fill_cart_venting_valve_target = 18275;
    packet_in.pinhole_venting_valve_target = 18379;
    packet_in.heater_state = 18483;
    packet_in.filling_valve_state = 18587;
    packet_in.main_valve_state = 18691;
    packet_in.fill_cart_venting_valve_state = 18795;
    packet_in.pinhole_venting_valve_state = 18899;
    packet_in.log_status = 235;
    packet_in.temperature = 73.0;

    mavlink::uorocketry::msg::HOTFIRE_STATE packet1{};
    mavlink::uorocketry::msg::HOTFIRE_STATE packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.timestamp, packet2.timestamp);
    EXPECT_EQ(packet1.current_state, packet2.current_state);
    EXPECT_EQ(packet1.heater_target, packet2.heater_target);
    EXPECT_EQ(packet1.filling_valve_target, packet2.filling_valve_target);
    EXPECT_EQ(packet1.main_valve_target, packet2.main_valve_target);
    EXPECT_EQ(packet1.fill_cart_venting_valve_target, packet2.fill_cart_venting_valve_target);
    EXPECT_EQ(packet1.pinhole_venting_valve_target, packet2.pinhole_venting_valve_target);
    EXPECT_EQ(packet1.heater_state, packet2.heater_state);
    EXPECT_EQ(packet1.filling_valve_state, packet2.filling_valve_state);
    EXPECT_EQ(packet1.main_valve_state, packet2.main_valve_state);
    EXPECT_EQ(packet1.fill_cart_venting_valve_state, packet2.fill_cart_venting_valve_state);
    EXPECT_EQ(packet1.pinhole_venting_valve_state, packet2.pinhole_venting_valve_state);
    EXPECT_EQ(packet1.log_status, packet2.log_status);
    EXPECT_EQ(packet1.temperature, packet2.temperature);
}

#ifdef TEST_INTEROP
TEST(uorocketry_interop, HOTFIRE_STATE)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_hotfire_state_t packet_c {
         93372036854775807ULL, 73.0, 17859, 17963, 18067, 18171, 18275, 18379, 18483, 18587, 18691, 18795, 18899, 235
    };

    mavlink::uorocketry::msg::HOTFIRE_STATE packet_in{};
    packet_in.timestamp = 93372036854775807ULL;
    packet_in.current_state = 17859;
    packet_in.heater_target = 17963;
    packet_in.filling_valve_target = 18067;
    packet_in.main_valve_target = 18171;
    packet_in.fill_cart_venting_valve_target = 18275;
    packet_in.pinhole_venting_valve_target = 18379;
    packet_in.heater_state = 18483;
    packet_in.filling_valve_state = 18587;
    packet_in.main_valve_state = 18691;
    packet_in.fill_cart_venting_valve_state = 18795;
    packet_in.pinhole_venting_valve_state = 18899;
    packet_in.log_status = 235;
    packet_in.temperature = 73.0;

    mavlink::uorocketry::msg::HOTFIRE_STATE packet2{};

    mavlink_msg_hotfire_state_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.timestamp, packet2.timestamp);
    EXPECT_EQ(packet_in.current_state, packet2.current_state);
    EXPECT_EQ(packet_in.heater_target, packet2.heater_target);
    EXPECT_EQ(packet_in.filling_valve_target, packet2.filling_valve_target);
    EXPECT_EQ(packet_in.main_valve_target, packet2.main_valve_target);
    EXPECT_EQ(packet_in.fill_cart_venting_valve_target, packet2.fill_cart_venting_valve_target);
    EXPECT_EQ(packet_in.pinhole_venting_valve_target, packet2.pinhole_venting_valve_target);
    EXPECT_EQ(packet_in.heater_state, packet2.heater_state);
    EXPECT_EQ(packet_in.filling_valve_state, packet2.filling_valve_state);
    EXPECT_EQ(packet_in.main_valve_state, packet2.main_valve_state);
    EXPECT_EQ(packet_in.fill_cart_venting_valve_state, packet2.fill_cart_venting_valve_state);
    EXPECT_EQ(packet_in.pinhole_venting_valve_state, packet2.pinhole_venting_valve_state);
    EXPECT_EQ(packet_in.log_status, packet2.log_status);
    EXPECT_EQ(packet_in.temperature, packet2.temperature);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(uorocketry, LOG_MESSAGE)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::uorocketry::msg::LOG_MESSAGE packet_in{};
    packet_in.severity = 5;
    packet_in.length = 72;
    packet_in.data = {{ 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228 }};

    mavlink::uorocketry::msg::LOG_MESSAGE packet1{};
    mavlink::uorocketry::msg::LOG_MESSAGE packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.severity, packet2.severity);
    EXPECT_EQ(packet1.length, packet2.length);
    EXPECT_EQ(packet1.data, packet2.data);
}

#ifdef TEST_INTEROP
TEST(uorocketry_interop, LOG_MESSAGE)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_log_message_t packet_c {
         5, 72, { 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228 }
    };

    mavlink::uorocketry::msg::LOG_MESSAGE packet_in{};
    packet_in.severity = 5;
    packet_in.length = 72;
    packet_in.data = {{ 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228 }};

    mavlink::uorocketry::msg::LOG_MESSAGE packet2{};

    mavlink_msg_log_message_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.severity, packet2.severity);
    EXPECT_EQ(packet_in.length, packet2.length);
    EXPECT_EQ(packet_in.data, packet2.data);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
