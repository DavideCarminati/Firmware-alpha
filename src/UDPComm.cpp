/*! @file UDPComm.cpp

    @brief Enables UDP communication between the target board and an external PC to perform Processor-In-the-Loop.

    @details Processor-In-the-Loop validation uses the external PC to simulate the physical model, its actuators and
    its sensors. The target board runs the firmware with full functionalities plus this thread that is responsible for
    sending/receiving simulation data to/from the external PC. The target board controls the model just as it was controlling 
    the physical system.

    @note The used communication protocol is Mavlink v2.0.


*/

#include <UDPComm.hpp>

static const char*          mbedIP       = "192.168.1.55";  //IP 
static const char*          mbedMask     = "255.255.255.0";  // Mask
static const char*          mbedGateway  = "192.168.1.254";    //Gateway

static const char*          recvIP = "192.168.1.203";// */ "192.168.1.249";
static const char*          localIP = "0.0.0.0";

uint8_t in_data[MAVLINK_MAX_PACKET_LEN], out_buf[MAVLINK_MAX_PACKET_LEN];

mavlink_message_t pos_decoded, msg;
mavlink_status_t status;
mavlink_attitude_t att;

uint8_t SYS_ID = 1;
uint8_t COMP_ID = 1;

void UDPComm(void) 
{
    EthernetInterface eth;
    eth.set_network(mbedIP, mbedMask, mbedGateway);
    eth.EthernetInterface::connect();

    UDPSocket socket;
    socket.open(&eth);
    // Setting up server to listen to port 8150
    SocketAddress sockAddr_in(localIP,8050);
    socket.bind(8150);
    socket.set_timeout(2000);
    // Setting up client to speak to port 8151 of external PC
    SocketAddress sockAddr(recvIP, 8151);

    while (true)
    {   
        // receiving data...
        if(socket.recvfrom(&sockAddr_in, &in_data, MAVLINK_MAX_PACKET_LEN) != NSAPI_ERROR_WOULD_BLOCK) // now act as a server and receive from simulink data back
        {
            for(int ii = 0; ii < MAVLINK_MAX_PACKET_LEN; ii++) 
            {
                uint8_t byte = in_data[ii];
                if(mavlink_parse_char(MAVLINK_COMM_0, byte, &pos_decoded, &status))
                {
                    feedback_control_U.estimated = mavlink_msg_local_position_ned_get_x(&pos_decoded);
                }
            }
            semDecode.release();
            ThisThread::sleep_for(250);
        } else
        {
            feedback_control_U.estimated = 0;
            semDecode.release();
        }
        

        // sending data...
        semEncode.acquire();
        att.roll = feedback_control_Y.u;
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

            ThisThread::sleep_for(250);
        
    }


}

