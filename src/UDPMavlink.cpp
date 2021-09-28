/*! @file UDPMavlink.cpp

    @brief Send and receive Mavlink messages from/to the companion computer messages 

*/

#include <mbed.h>
#include <EthernetInterface.h>
#include "global_vars.hpp"
#include "common/mavlink.h"
#include "global_msgs.hpp"
#include <algorithm>
#include <iterator>

#include "UDPMavlink.hpp"

static const char*          mbedIP       = "192.168.1.10";  //IP 
static const char*          mbedMask     = "255.255.255.0";  // Mask
static const char*          mbedGateway  = "192.168.1.1";    //Gateway

static const char*          ltpndIP      = "192.168.1.11";
static const char*          ltpndMask     = "255.255.255.0";  // Mask
static const char*          ltpndGateway  = "192.168.1.1";    //Gateway

SocketAddress sockAddr_in(ltpndIP,8150); // Setting up server to listen to port 8150
SocketAddress sockAddr_out(ltpndIP,8151);

uint8_t in_data[MAVLINK_MAX_PACKET_LEN], out_buf[MAVLINK_MAX_PACKET_LEN];

mavlink_message_t msgIn, ekf_data_fusedOut, imu_k64_Out, encodersOut;
mavlink_status_t status;
// mavlink_odometry_t ekf_data_fused;    // WARNING: Data for fusion are now managed by imu_k64  
mavlink_scaled_imu_t imu_k64;
mavlink_wheel_distance_t encoders;

// mavlink_raw_imu_t raw_imu;


uint8_t SYS_ID = 1;
uint8_t COMP_ID = 1;

float accx, accy, accz, mx, my, mz;

Timer timerUDP;

uint64_t epochUDP;

void UDPMavlink()
{
    // printf("qui thread\n");
    eth.set_network(mbedIP, mbedMask, mbedGateway);
    eth.EthernetInterface::connect(); // Done to avoid methods ambiguity!

    
    socket.open(&eth);
    socket.set_timeout(2000);
    
    socket.bind(8150);
    
    // printf("qui processo start\n");

    timerUDP.start();
    while(1)
    {
        epochUDP = Kernel::get_ms_count();
        timerUDP.reset();
        // receiving data...
        // printf("qui UDPMAV\n");
        if(socket.recvfrom(&sockAddr_in, &in_data, MAVLINK_MAX_PACKET_LEN) != NSAPI_ERROR_WOULD_BLOCK) // now act as a server and receive from simulink data back
        {
            for(int ii = 0; ii < MAVLINK_MAX_PACKET_LEN; ii++) 
            {
                uint8_t byte = in_data[ii];
                if(mavlink_parse_char(MAVLINK_COMM_0, byte, &msgIn, &status))
                {
                    switch (msgIn.msgid)
                    {
                    case MAVLINK_MSG_ID_SET_POSITION_TARGET_LOCAL_NED:
                        mavlink_msg_set_position_target_local_ned_decode(&msgIn, &setpointsTrajectoryPlanner);
                        printf("\033[10;1H");
                        printf("setpoint: %f, %f, %f, %f, %f\n", setpointsTrajectoryPlanner.x, setpointsTrajectoryPlanner.y, \
                            setpointsTrajectoryPlanner.vx, setpointsTrajectoryPlanner.vy, setpointsTrajectoryPlanner.yaw);
                        break;

                    case MAVLINK_MSG_ID_ODOMETRY:
                        mavlink_msg_odometry_decode(&msgIn,&odom);
                        // printf("\033[11;1H");
                        // printf("odometry: %f, %f, %f, %f, %f\n", odom.x, odom.y, odom.vx, odom.vy, atan2(2*odom.q[3]*odom.q[2], 1 - 2*pow(odom.q[2],2))*180/PI);

                        break;

                    case MAVLINK_MSG_ID_RC_CHANNELS:
                        mavlink_msg_rc_channels_decode(&msgIn, &rc);
                        //printf("pwm left, right and direction %d, %d, %d\n", rc.chan1_raw, rc.chan2_raw, rc.chan3_raw);
                        // printf("\033[11;1H");
                        // printf("odometry: %f, %f, %f, %f, %f\n", odom.x, odom.y, odom.vx, odom.vy, atan2(2*odom.q[3]*odom.q[2], 1 - 2*pow(odom.q[2],2))*180/PI);

                        break;    
                    
                    default:
                        printf("\033[4;1H");
                        printf("Mavlink message not decoded!\n");
                        break;
                    }
                    
                    // printf("\033[4;1H");
                    // printf("%f, %f, %f, %f, %f", odom.x, odom.q[0], odom.q[1], odom.q[2], odom.q[3]);
                    // semUDPNav.release();
                    // flagMavlink = true;
                }
            }
        } else
        {
            // printf("\033[15;1H");
            // printf("problema connessione udp\n");
        }

        time_t sec = 0;//time(NULL);

        /* EKF inputs and outputs definition section
        *
        */
        // Kalman_filter_conv_U.X_rs=odom.x;
        // Kalman_filter_conv_U.Y_rs=odom.y;
        // Kalman_filter_conv_U.q0_rs=odom.q[0];
        // Kalman_filter_conv_U.q1_rs=odom.q[1];
        // Kalman_filter_conv_U.q2_rs=odom.q[2];
        // Kalman_filter_conv_U.q3_rs=odom.q[3];
        // float psi_rs;
        // psi_rs= atan2(2*(odom.q[0]*odom.q[3]+odom.q[1]*odom.q[2]),1-2*(pow(odom.q[2],2)+pow(odom.q[3],2)));
        // Kalman_filter_conv_U.Vx_rs=odom.vx*cos(psi_rs)+odom.vy*sin(psi_rs);
        // Kalman_filter_conv_U.Vy_rs=odom.vy*cos(psi_rs)-odom.vx*sin(psi_rs);
        // ekf_data_fused.x = Kalman_filter_conv_Y.X;
        // ekf_data_fused.y = Kalman_filter_conv_Y.Y;
        // ekf_data_fused.vx = Kalman_filter_conv_Y.Vx*cos(Kalman_filter_conv_Y.psi);
        // ekf_data_fused.vy = Kalman_filter_conv_Y.Vx*sin(Kalman_filter_conv_Y.psi); // Vx is in body frame!
        // ekf_data_fused.q[0] = cos(Kalman_filter_conv_Y.psi/2);
        // ekf_data_fused.q[3] = sin(Kalman_filter_conv_Y.psi/2); // q[1] and q[2] are zero since the rotation is around z
       
        
        /* imu_k64 message definition section
        * SCALED_IMU MAVLINK MESSAGE: accelerometers and magnetometers readings in mg and mgauss
        */
        imu_k64.time_boot_ms = sec;
        accx = -accmagValues.ax*1000;
        accy = accmagValues.ay*1000;
        accz = -accmagValues.az*1000;
        mx   = accmagValues.mx*1000;
        my   = accmagValues.my*1000;
        mz   = accmagValues.mz*1000;
        imu_k64.xacc = (int16_t)accx;
        imu_k64.yacc = (int16_t)accy;
        imu_k64.zacc = (int16_t)accz; 
        imu_k64.xmag = (int16_t)mx; 
        imu_k64.ymag = (int16_t)my; 
        imu_k64.zmag = (int16_t)mz; 
        imu_k64.zmag = (int16_t)sin(attitudeValues.psi/2);  // WARNING: zmag is q4 for IMU ROS Message
        
        
        mavlink_msg_scaled_imu_encode(SYS_ID,COMP_ID,&imu_k64_Out,&imu_k64);
        mavlink_msg_to_send_buffer((uint8_t*) &out_buf,&imu_k64_Out); 

        // if(socket.sendto(sockAddr_out,(const void*)out_buf,MAVLINK_MAX_PACKET_LEN) != NSAPI_ERROR_WOULD_BLOCK) // sending data...
        // {
        //     // continue;
        //     // printf("ekf data sent!\n");
        // } 
        // else 
        // {
        //     printf("Data not sent!\n");
        // }

        encoders.time_usec = sec;
        encoders.distance[0] = distanceValues.posL*0.0215; 
        encoders.distance[1] = distanceValues.posR*0.0215;

        mavlink_msg_wheel_distance_encode(SYS_ID,COMP_ID,&encodersOut,&encoders);
        mavlink_msg_to_send_buffer((uint8_t*) &out_buf,&encodersOut);

        // if(socket.sendto(sockAddr_out,(const void*)out_buf,MAVLINK_MAX_PACKET_LEN) != NSAPI_ERROR_WOULD_BLOCK) // sending data...
        // {
        //     // continue;
        //     // printf("ekf data sent!\n");
        // } 
        // else 
        // {
        //     printf("Data not sent!\n");
        // }
        // // int elapsed = timerUDP.read_us();

        ThisThread::sleep_until(epochUDP+50);
    }
}