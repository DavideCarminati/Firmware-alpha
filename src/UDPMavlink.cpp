/*! @file UDPMavlink.cpp

    @brief Send and receive Mavlink messages from/to the companion computer messages 

*/

#include <mbed.h>
#include <EthernetInterface.h>
#include "global_vars.hpp"
#include "common/mavlink.h"
#include "global_msgs.hpp"

#include "UDPMavlink.hpp"

static const char*          mbedIP       = "192.168.1.10";  //IP 
static const char*          mbedMask     = "255.255.255.0";  // Mask
static const char*          mbedGateway  = "192.168.1.1";    //Gateway

static const char*          ltpndIP      = "192.168.1.11";
static const char*          ltpndMask     = "255.255.255.0";  // Mask
static const char*          ltpndGateway  = "192.168.1.1";    //Gateway

SocketAddress sockAddr_in(ltpndIP,8150); // Setting up server to listen to port 8150

uint8_t in_data[MAVLINK_MAX_PACKET_LEN], out_buf[MAVLINK_MAX_PACKET_LEN];

mavlink_message_t msgIn;
mavlink_status_t status;
mavlink_attitude_t att;
// mavlink_raw_imu_t raw_imu;


uint8_t SYS_ID = 1;
uint8_t COMP_ID = 1;

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
                    mavlink_msg_odometry_decode(&msgIn,&odom);
                    // printf("\033[4;1H");
                    // printf("%f, %f, %f, %f, %f", odom.x, odom.q[0], odom.q[1], odom.q[2], odom.q[3]);
                    // semUDPNav.release();
                    // flagMavlink = true;
                }
            }
        } else
        {
            printf("problema connessione udp\n");
        }
        // int elapsed = timerUDP.read_us();
        ThisThread::sleep_until(epochUDP+200);
    }
}