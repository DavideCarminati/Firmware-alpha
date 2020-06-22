#include <mbed.h>
#include <EthernetInterface.h>
#include "global_vars.hpp"
#include "common/mavlink.h"

#include "ethInit.hpp"

static const char*          mbedIP       = "192.168.1.10";  //IP 
static const char*          mbedMask     = "255.255.255.0";  // Mask
static const char*          mbedGateway  = "192.168.1.1";    //Gateway

static const char*          ltpndIP      = "192.168.1.11";
static const char*          ltpndMask     = "255.255.255.0";  // Mask
static const char*          ltpndGateway  = "192.168.1.1";    //Gateway

static const char*          recvIP = "192.168.1.203";// */ "192.168.1.249"; IP of the PC receiving the msg
static const char*          localIP = "0.0.0.0"; // not used if connecting directly board and lattepanda with ethernet!!

EthernetInterface eth;
UDPSocket socket;

SocketAddress sockAddr_in(ltpndIP,8150); // Setting up server to listen to port 8150

uint8_t in_data[MAVLINK_MAX_PACKET_LEN], out_buf[MAVLINK_MAX_PACKET_LEN];

mavlink_message_t msgIn;
mavlink_status_t status;
mavlink_attitude_t att;

uint8_t SYS_ID = 1;
uint8_t COMP_ID = 1;

float odometryx;

Timer timerUDP;

uint64_t epochUDP;

void UDPComm()
{
    printf("qui thread\n");
    eth.set_network(mbedIP, mbedMask, mbedGateway);
    eth.EthernetInterface::connect(); // Done to avoid methods ambiguity!

    
    socket.open(&eth);
    socket.set_timeout(2000);
    
    socket.bind(8150);
    #if PIL_MODE
        // Setting up server to listen to port 8150
        SocketAddress sockAddr_in(localIP,8050); // FIXME change port for PIL!!
        socket.bind(8150);
        // Setting up client to speak to port 8151 of external PC
        SocketAddress sockAddr(recvIP, 8151);
    #endif
    
    printf("qui processo start\n");

    timerUDP.start();
    while(1)
    {
        epochUDP = Kernel::get_ms_count();
        timerUDP.reset();
        // receiving data...
        printf("qui UDPMAV\n");
        if(socket.recvfrom(&sockAddr_in, &in_data, MAVLINK_MAX_PACKET_LEN) != NSAPI_ERROR_WOULD_BLOCK) // now act as a server and receive from simulink data back
        {
            for(int ii = 0; ii < MAVLINK_MAX_PACKET_LEN; ii++) 
            {
                uint8_t byte = in_data[ii];
                if(mavlink_parse_char(MAVLINK_COMM_0, byte, &msgIn, &status))
                {
                    odometryx = mavlink_msg_odometry_get_x(&msgIn); // TODO cambiare nome alle variabili per thread navigazione
                    // int tempo = timer.read_us();
                    printf("%f\n",odometryx);
                }
            }
        } else
        {
            printf("problema connessione udp\n");
        }
        // int elapsed = timerUDP.read_us();
        ThisThread::sleep_until(epochUDP+500);
        #if PIL_MODE // TODO creare nuovo processo udp solo per pil
            // receiving data...
            if(socket.recvfrom(&sockAddr_in, &in_data, MAVLINK_MAX_PACKET_LEN) != NSAPI_ERROR_WOULD_BLOCK) // now act as a server and receive from simulink data back
            {
                for(int ii = 0; ii < MAVLINK_MAX_PACKET_LEN; ii++) 
                {
                    uint8_t byte = in_data[ii];
                    if(mavlink_parse_char(MAVLINK_COMM_0, byte, &pos_decoded, &status))
                    {
                        // feedback_control_U.estimated = mavlink_msg_local_position_ned_get_x(&pos_decoded);
                    }
                }
                semDecode.release();
                // ThisThread::sleep_for(250);
            } else
            {
                // feedback_control_U.estimated = 0;
                semDecode.release();
            }
            

            // sending data...
            semEncode.acquire();
            // att.roll = feedback_control_Y.u;
            time_t sec = 0;//time(NULL);
            att.time_boot_ms = sec;

            mavlink_msg_attitude_encode(SYS_ID,COMP_ID,&msg,&att);
            mavlink_msg_to_send_buffer((uint8_t*) &out_buf,&msg); 

            if(socket.sendto(sockAddr,(const void*)out_buf,MAVLINK_MAX_PACKET_LEN)<0) // sending data...
            {
                    printf("Error sending data\n");

                } else {
                    printf("Data sent!\n");
                }

                // ThisThread::sleep_for(250);
            

        #endif
    }
}