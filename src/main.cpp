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
#include "cli2.hpp"
#include "ethInit.hpp"


const char* UDP_PIL_thread_name = "UDPIO_PIL";
const char* cntrInit_thread_name = "cntrInit";
const char* sensInit_thread_name = "sensInit";
const char* outportInit_thread_name = "outportInit";
const char* cli_thread_name = "cli";
const char* UDP_Comm_thread_name = "ethInit"; // TODO CHANGE THE NAME OF PROCESS TO UDP MAVLINK

// Serial serial(USBTX,USBRX);
Serial* serial = new Serial(USBTX,USBRX,115200);
// FileHandle *fh = &serial; // oppure FileHandle fh = new FileHandle(serial)

// #if PIL_MODE
//   #include "UDPComm.hpp"
//   /** This spawns the thread responsible for receving/sending simulation data from/to an external PC. It is enables only if 
//    * the build flag PIL_MODE is set to 1. The thread function is in UDPComm.cpp
//    */
//   Thread UDPIO_PIL(osPriorityHigh,8092,nullptr,UDP_PIL_thread_name);
// #endif


Thread ControllerInit(osPriorityHigh,8092,nullptr,cntrInit_thread_name);
Thread SensorInit(osPriorityNormal,8092,nullptr,sensInit_thread_name);
Thread OutputPortInit(osPriorityNormal,16184,nullptr,outportInit_thread_name);
Thread CommandLineInterface(osPriorityNormal,8092,nullptr,cli_thread_name);
Thread UDPCommunicationInit(osPriorityNormal,16184,nullptr,UDP_Comm_thread_name);
// TODO aggiungere thread navigazione

// TODO Include semaphores for synchronizing sensor read/controller/pwm write
Semaphore semDecode(0), semEncode(0);

Servo servo1(PTC10);

EventQueue queue(32);

ExtU_feedback_control_T feedback_control_U;
ExtY_feedback_control_T feedback_control_Y;

int main() 
{

  // serial.baud(115200);
  printf("\033[2J");
  set_time(0);

  // #if PIL_MODE // Start UDP communtication only if in PIL mode!
  //   UDPIO_PIL.start(UDPComm);
  // #endif
  
  ControllerInit.start(cntrInit);
  SensorInit.start(sensInit);
  OutputPortInit.start(outportInit);
  UDPCommunicationInit.start(UDPComm);
  CommandLineInterface.start(callback(cli2,serial));
  ControllerInit.join();
  SensorInit.join();

  queue.dispatch();
  while(1) {
    ThisThread::sleep_for(900);
  }
  
}