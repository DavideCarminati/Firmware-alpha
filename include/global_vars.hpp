/*! \file global_vars.hpp 
    \brief Header gathering the global variables used in the Firmware

    Global variables are chosen upon uORB because yes.
*/


#include <mbed.h>
#include "common/mavlink.h"
#include "PI_contr.h"
#include "Servo.h"
#include "EthernetInterface.h"
#include "FXOS8700CQ.h"
#include "Kalman_filter_conv.h"
#include "APF_SMC/APF_SMC.h"
#include "Imu/ADXL345_I2C.h"

#include "Imu/ADXL345_I2C.h"

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

extern ExtU_PI_contr_T PI_contr_U;     // External inputs
extern ExtY_PI_contr_T PI_contr_Y;     // External outputs

#endif

#ifndef SEMAPHORES
#define SEMAPHORES

extern Semaphore semDecode, semEncode, semUDPNav, semNavContr, semContrPWM;
extern bool flagMavlink;

#endif

#ifndef SERVO_1
#define SERVO_1

extern Servo servo1;

#endif

// #ifndef QUEUE_IO IT DOESN'T WORK!!!
// #define QUEUE_IO  

// extern EventQueue queue;

// #endif


#ifndef ETH_COMM
#define ETH_COMM

extern EthernetInterface eth;
extern UDPSocket socket;

#endif

#ifndef ACCMAG_VALUES
#define ACCMAG_VALUES

extern Data accmagValues;

#endif

#ifndef IMUEXT_VALUES
#define IMUEXT_VALUES

extern Data2 imuextValues;

#endif

#ifndef LED_MUTEX
#define LED_MUTEX

extern Mutex led_lock;

#endif

#ifndef TRAJECTORY_PLANNER_SETPOINTS
#define TRAJECTORY_PLANNER_SETPOINTS

extern mavlink_set_position_target_local_ned_t setpointsTrajectoryPlanner;

#endif

#ifndef EKF_TASK
#define EKF_TASK

extern ExtU_Kalman_filter_conv_T Kalman_filter_conv_U;// External inputs
extern ExtY_Kalman_filter_conv_T Kalman_filter_conv_Y;// External outputs

#endif

#ifndef APF_TASK
#define APF_TASK

extern ExtU_APF_SMC_T APF_SMC_U; // External inputs
extern ExtY_APF_SMC_T APF_SMC_Y; // External outputs

#endif

#ifndef DEBUG_APF
#define DEBUG_APF

extern real_T debug_psi_ref;
extern real_T debug_vel_ref;

#endif

#ifndef EXTIMU_VALUES
#define EXTIMU_VALUES

extern Data2 imuextValues;

#endif

// // Calibration flags are used to notify whether a sensor has undergone the process of calibration successfully
// #ifndef CALIBRATION_FLAGS
// #define CALIBRATION_FLAGS

// extern bool magCalibFlag;

// #endif

// // Calibration values are used by the sensors at start up to correct errors
// #ifndef CALIBRATION_VALUES
// #define CALIBRATION_VALUES

// extern float minMag[3], maxMag[3];

// #endif
