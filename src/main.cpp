/*! @file main.cpp 

    @brief Entry point for mbed OS.

    This script creates and spawns threads and declare global variables defined
    in the header global_vars.hpp.
*/


#include <mbed.h>
#include <Serial.h>
#include <EthernetInterface.h>

#include "global_vars.hpp"
#include "global_msgs.hpp"
#include "common/mavlink.h"
#include "cntrInit.hpp"
#include "sensInit.hpp"
#include "outportInit.hpp"
#include "cli2.hpp"
#include "UDPMavlink.hpp"
#include "navigator.hpp"
#include "prognostic.hpp"
#include "massStorage.hpp"

#include "Thread.h"

using namespace events;
using namespace rtos;
using namespace ThisThread;
using namespace mbed;

const char* cntrInit_thread_name = "cntrInit";
const char* sensInit_thread_name = "sensInit";
const char* outportInit_thread_name = "outportInit";
const char* cli_thread_name = "cli";
const char* UDPMavlink_thread_name = "UDPMavlink";
const char* UDP_PIL_thread_name = "UDPPIL";
const char* Navi_thread_name = "Navigator";
const char* prognostic_thread_name = "Prognostic";
const char* sdcard_thread_name = "SDStorage";


Serial* serial = new Serial(USBTX,USBRX,115200);
// FileHandle *fh = &serial; // oppure FileHandle fh = new FileHandle(serial)

#if PIL_MODE
  #include "UDPPIL.hpp"
  /** This spawns the thread responsible for receving/sending simulation data from/to an external PC. It is enables only if 
   * the build flag PIL_MODE is set to 1. The thread function is in UDPComm.cpp
   */
  Thread UDPIO_PIL(osPriorityHigh,8092,nullptr,UDP_PIL_thread_name);
#endif


Thread ControllerInit(osPriorityHigh,8092,nullptr,cntrInit_thread_name);
Thread SensorInit(osPriorityNormal,8092,nullptr,sensInit_thread_name);
Thread OutputPortInit(osPriorityNormal,16184,nullptr,outportInit_thread_name);
Thread CommandLineInterface(osPriorityNormal,8092,nullptr,cli_thread_name);
Thread UDPMavlinkComm(osPriorityNormal,16184,nullptr,UDPMavlink_thread_name);
Thread Navigator(osPriorityNormal,16184,nullptr,Navi_thread_name);
Thread Prognostic(osPriorityNormal,8092,nullptr,prognostic_thread_name);
Thread SDStorage(osPriorityNormal,8092,nullptr,sdcard_thread_name);

/** Defining semaphores for synchronization purposes
 * 
 */
Semaphore semDecode(0), semEncode(0), semUDPNav(0), semNavContr(0), semContrPWM(0);
bool flagMavlink = false;

Servo servo1(PTC10);

/** Defining global queue in which sensor/actuators event run
 * 
 */
// EventQueue queue(32);

/** Defining global inputs/outputs of the controller feedback_control.cpp
 * 
 */ 
ExtU_feedback_control_T feedback_control_U;
ExtY_feedback_control_T feedback_control_Y;

/** Defining global mavlink messages declared in global_msgs.hpp
 * 
 */
mavlink_odometry_t odom;

/** Defining global onboard accelerometer and magnetometer values
 * 
 */

Data accmagValues;

// Data accmagValues;

/** Initializing ethernet interface and the socket to enable UDP communications in threads UDPMavlink.cpp and UDPPIL.cpp
 * 
 */
EthernetInterface eth;
UDPSocket socket;


int main() 
{
  printf("\033[2J");
  set_time(0);

  #if PIL_MODE // Start UDP communtication only if in PIL mode!
    UDPIO_PIL.start(UDPPIL);
  #endif
  
  printf("Spawning threads...\n");
  SDStorage.start(massStorage);
  printf("%s thread started\n", sdcard_thread_name);
  SDStorage.join();
  printf("Mass storage initialized\n");
  ControllerInit.start(cntrInit);
  printf("%s thread started\n", cntrInit_thread_name);
  SensorInit.start(sensInit);
  OutputPortInit.start(outportInit);
  UDPMavlinkComm.start(UDPMavlink);
  // Navigator.start(navigator);
  Prognostic.start(prognostic);
  CommandLineInterface.start(callback(cli2,serial));
  // printf("Command line available\n");

  ControllerInit.join();
  
  
  while(1) {
    ThisThread::sleep_for(900);
  }
  
}