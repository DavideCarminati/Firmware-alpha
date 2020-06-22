/*! \file global_vars.hpp 
    \brief Header gathering the global variables used in the Firmware

    Global variables are chosen upon uORB because yes.
*/


#include <mbed.h>
#include "common/mavlink.h"
#include "feedback_control.h"
#include "Servo.h"
#include "EthernetInterface.h"

#ifndef UDP_BUFFER
#define UDP_BUFFER


// struct __UDPbuff {
//   uint8_t in_data[MAVLINK_MAX_PACKET_LEN];
//   bool in_data_full;
//   uint8_t out_buf[MAVLINK_MAX_PACKET_LEN];
//   bool out_buf_full;
// };



#endif

#ifndef CONTROLLER_TASK_IO
#define CONTROLLER_TASK_IO

/**
 * The I/O variables of the controller are used as extern since their name is the same if a Simulink project is used. 
 * This allows to keep the Firmware unchanged.
 */

extern ExtU_feedback_control_T feedback_control_U;      /**< External inputs */
extern ExtY_feedback_control_T feedback_control_Y;      /**< External outputs */

#endif

#ifndef SEMAPHORES
#define SEMAPHORES

extern Semaphore semDecode, semEncode;

#endif

#ifndef SERVO_1
#define SERVO_1

extern Servo servo1;

#endif

#ifndef QUEUE_IO
#define QUEUE_IO  

extern EventQueue queue;

#endif


#ifndef ETH_COMM
#define ETH_COMM

extern EthernetInterface eth;
extern UDPSocket socket;

#endif
