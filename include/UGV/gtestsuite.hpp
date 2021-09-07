/** @file
 *	@brief MAVLink comm testsuite protocol generated from UGV.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "UGV.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(UGV, IMU_COVARIANCE)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::UGV::msg::IMU_COVARIANCE packet_in{};
    packet_in.time_boot_ms = 963497464;
    packet_in.xacc = 23059;
    packet_in.yacc = 23163;
    packet_in.zacc = 23267;
    packet_in.xgyro = 23371;
    packet_in.ygyro = 23475;
    packet_in.zgyro = 23579;
    packet_in.xmag = 23683;
    packet_in.ymag = 23787;
    packet_in.zmag = 23891;
    packet_in.acc_cov = {{ 45.0, 46.0, 47.0, 48.0, 49.0, 50.0, 51.0, 52.0, 53.0 }};
    packet_in.gyro_cov = {{ 297.0, 298.0, 299.0, 300.0, 301.0, 302.0, 303.0, 304.0, 305.0 }};
    packet_in.mag_cov = {{ 549.0, 550.0, 551.0, 552.0, 553.0, 554.0, 555.0, 556.0, 557.0 }};
    packet_in.temperature = 23995;

    mavlink::UGV::msg::IMU_COVARIANCE packet1{};
    mavlink::UGV::msg::IMU_COVARIANCE packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.time_boot_ms, packet2.time_boot_ms);
    EXPECT_EQ(packet1.xacc, packet2.xacc);
    EXPECT_EQ(packet1.yacc, packet2.yacc);
    EXPECT_EQ(packet1.zacc, packet2.zacc);
    EXPECT_EQ(packet1.xgyro, packet2.xgyro);
    EXPECT_EQ(packet1.ygyro, packet2.ygyro);
    EXPECT_EQ(packet1.zgyro, packet2.zgyro);
    EXPECT_EQ(packet1.xmag, packet2.xmag);
    EXPECT_EQ(packet1.ymag, packet2.ymag);
    EXPECT_EQ(packet1.zmag, packet2.zmag);
    EXPECT_EQ(packet1.acc_cov, packet2.acc_cov);
    EXPECT_EQ(packet1.gyro_cov, packet2.gyro_cov);
    EXPECT_EQ(packet1.mag_cov, packet2.mag_cov);
    EXPECT_EQ(packet1.temperature, packet2.temperature);
}

#ifdef TEST_INTEROP
TEST(UGV_interop, IMU_COVARIANCE)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_imu_covariance_t packet_c {
         963497464, { 45.0, 46.0, 47.0, 48.0, 49.0, 50.0, 51.0, 52.0, 53.0 }, { 297.0, 298.0, 299.0, 300.0, 301.0, 302.0, 303.0, 304.0, 305.0 }, { 549.0, 550.0, 551.0, 552.0, 553.0, 554.0, 555.0, 556.0, 557.0 }, 23059, 23163, 23267, 23371, 23475, 23579, 23683, 23787, 23891, 23995
    };

    mavlink::UGV::msg::IMU_COVARIANCE packet_in{};
    packet_in.time_boot_ms = 963497464;
    packet_in.xacc = 23059;
    packet_in.yacc = 23163;
    packet_in.zacc = 23267;
    packet_in.xgyro = 23371;
    packet_in.ygyro = 23475;
    packet_in.zgyro = 23579;
    packet_in.xmag = 23683;
    packet_in.ymag = 23787;
    packet_in.zmag = 23891;
    packet_in.acc_cov = {{ 45.0, 46.0, 47.0, 48.0, 49.0, 50.0, 51.0, 52.0, 53.0 }};
    packet_in.gyro_cov = {{ 297.0, 298.0, 299.0, 300.0, 301.0, 302.0, 303.0, 304.0, 305.0 }};
    packet_in.mag_cov = {{ 549.0, 550.0, 551.0, 552.0, 553.0, 554.0, 555.0, 556.0, 557.0 }};
    packet_in.temperature = 23995;

    mavlink::UGV::msg::IMU_COVARIANCE packet2{};

    mavlink_msg_imu_covariance_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.time_boot_ms, packet2.time_boot_ms);
    EXPECT_EQ(packet_in.xacc, packet2.xacc);
    EXPECT_EQ(packet_in.yacc, packet2.yacc);
    EXPECT_EQ(packet_in.zacc, packet2.zacc);
    EXPECT_EQ(packet_in.xgyro, packet2.xgyro);
    EXPECT_EQ(packet_in.ygyro, packet2.ygyro);
    EXPECT_EQ(packet_in.zgyro, packet2.zgyro);
    EXPECT_EQ(packet_in.xmag, packet2.xmag);
    EXPECT_EQ(packet_in.ymag, packet2.ymag);
    EXPECT_EQ(packet_in.zmag, packet2.zmag);
    EXPECT_EQ(packet_in.acc_cov, packet2.acc_cov);
    EXPECT_EQ(packet_in.gyro_cov, packet2.gyro_cov);
    EXPECT_EQ(packet_in.mag_cov, packet2.mag_cov);
    EXPECT_EQ(packet_in.temperature, packet2.temperature);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
