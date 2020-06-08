/*! \file main.cpp 
    \brief Entry point for mbed OS.

    This script creates and spawns threads and declare global variables defined
    in the header global_vars.hpp.
*/


#include <mbed.h>
#include <Serial.h>
#include <EthernetInterface.h>

#include "global_vars.hpp"
#include "common/mavlink.h"
#include "cntrInit.hpp"
#include "sensInit.hpp"
#include "outportInit.hpp"


const char* UDP_thread_name = "UDPIO";
const char* cntrInit_thread_name = "cntrInit";
const char* sensInit_thread_name = "sensInit";
const char* outportInit_thread_name = "outportInit";

Serial serial(USBTX,USBRX);
FileHandle *fh = &serial; // oppure FileHandle fh = new FileHandle(serial)

#if PIL_MODE
  #include "UDPComm.hpp"
  Thread UDPIO(osPriorityHigh,8092,nullptr,UDP_thread_name);
#endif


Thread ControllerInit(osPriorityHigh,8092,nullptr,cntrInit_thread_name);
Thread SensorInit(osPriorityNormal,8092,nullptr,sensInit_thread_name);
Thread OutputPortInit(osPriorityNormal,8092,nullptr,outportInit_thread_name);

// TODO Include semaphores for synchronizing sensor read/controller/pwm write
Semaphore semDecode(0), semEncode(0);

Servo servo1(PTC10);

EventQueue queue;

ExtU_feedback_control_T feedback_control_U;/* External inputs */
ExtY_feedback_control_T feedback_control_Y;/* External outputs */

int main() 
{

  serial.baud(115200);
  printf("\033[2J");
  set_time(0);

  #if PIL_MODE // Start UDP communtication only if in PIL mode!
    UDPIO.start(UDPComm);
  #endif
  
  ControllerInit.start(cntrInit);
  SensorInit.start(sensInit);
  OutputPortInit.start(outportInit);
  ControllerInit.join();
  SensorInit.join();

  while(1) {
    ThisThread::sleep_for(900);
  }
  
}