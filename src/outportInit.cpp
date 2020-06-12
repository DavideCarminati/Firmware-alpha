/*! @file outportInit.cpp

    @author Davide Carminati

    @brief This thread creates the periodic task sending the pulse-width modulated signals to the enabled pins.

    @details The script uses events and a queue to pile periodic tasks. The queue contains both read-from and write-to pins events. 


*/

#include <mbed.h>
#include "Servo.h"
#include "global_vars.hpp"

#include "outportInit.hpp"


float pos = 0.0;

// PwmOut servo2(PTC10); ///< The PIN enable for PWM is PTC10.

// EventQueue queue;
Event<void(void)> servowriteEvent(&queue,Servo1Write);

Thread ServoWrite(osPriorityNormal,8092,nullptr,"servoWrite");

// CRITICAL Also in here I have to protect the read of the output of the controller algorithm with a mutex!!!

/** Initialization of the servomotor, spawn of the event posting thread and dispatch queue.
 *  The Servo::calibrate() method accepts as first input a value IN SECONDS.
 */
void outportInit()
{
    servo1.calibrate(0.0005,90); // 0.0005 s from center (1.5ms) to max/min
    ServoWrite.start(postServoEvent);
    queue.dispatch();
}

/** The period and the initial delay of the PWM write event are set. Then it is posted in the queue.
 */
void postServoEvent(void)
{
    servowriteEvent.period(50);
    servowriteEvent.delay(500);
    servowriteEvent.post();
}

/** The event is simply a method writing the computed duty cycle to the enabled pin port. The duty cycle is directly dependent on the output of the
 *  controller thread: note that the extern variable feedback_control_Y is present.
 */

void Servo1Write(void)
{
    // TODO add semaphore in here!
    pos = feedback_control_Y.u;//*180;
    servo1.write(pos);
    // printf("\033[1;1H");
    // printf("pos given to pwm port: %f\n",pos);
}