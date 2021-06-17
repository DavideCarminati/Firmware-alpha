/*! @file outportInit.cpp

    @author Davide Carminati

    @brief This thread creates the periodic task sending the pulse-width modulated signals to the enabled pins.

    @details The script uses events and a queue to pile periodic tasks. The queue contains both read-from and write-to pins events. 


*/

#include <mbed.h>
#include "Servo.h"
#include "global_vars.hpp"
#include "TankMotor.hpp"
#include "global_msgs.hpp"

#include "outportInit.hpp"


float pos = 75.0/180;
float delta_pos = 0.01;
int signs, signt, right_pwm=0, left_pwm=0;

// Servo servo2(PTC3); ///< The PIN enable for PWM is PTC10.
PwmOut servopwm(PTC3);

EventQueue queuePWM;
Event<void(void)> servowriteEvent(&queuePWM,Servo1Write);
Event<void(void)> motorwriteEvent(&queuePWM,MotorWrite);

Thread ServoWrite(osPriorityNormal,16184,nullptr,"servoWrite");

// TankMotor leftMotor(PTC10,PTC16,PTC17), rightMotor(PTC11,PTB9,PTA1);
TankMotor leftMotor(PTC10,PTB23,PTA2), rightMotor(PTC11,PTB9,PTA1);

// CRITICAL Also in here I have to protect the read of the output of the controller algorithm with a mutex!!!

/** Initialization of the servomotor, spawn of the event posting thread and dispatch queue.
 *  The Servo::calibrate() method accepts as first input a value IN SECONDS.
 */
void outportInit()
{
    // servo1.calibrate(0.0005,90); // 0.0005 s from center (1.5ms) to max/min
    // servo2.calibrate(0.0005,90);
    servopwm.pulsewidth_us(1500);
    ServoWrite.start(postServoEvent);
    queuePWM.dispatch(); // Also here the queue has to be started in this thread!!! otherwise doesn't dispatch
}

/** The period and the initial delay of the PWM write event are set. Then it is posted in the queue.
 */
void postServoEvent(void)
{
    servowriteEvent.period(500);
    servowriteEvent.delay(500);
    // servowriteEvent.post();

    motorwriteEvent.delay(4000);
    motorwriteEvent.period(200);
    motorwriteEvent.post();
    // printf("\033[2;60Hpost");
}

/** The event is simply a method writing the computed duty cycle to the enabled pin port. The duty cycle is directly dependent on the output of the
 *  controller thread: note that the extern variable feedback_control_Y is present.
 */

void Servo1Write(void)
{
    // TODO add semaphore in here!
    if (pos <= 75.0/180)
    {
        delta_pos = 0.01;
    }
    else if (pos >= 105.0/180)
    {
        delta_pos = -0.01;
    }
    printf("delta pos = %f  pos = %f\n", delta_pos, pos);
    pos = pos + delta_pos;
    servopwm.pulsewidth_us(pos*2000);
    // servo1.write(pos);
    // servo2.write(pos);
    
    
    // pos = feedback_control_Y.u;//*180;
    // servo1.write(pos);
    // printf("\033[1;1H");
    // printf("Pos given to PWM port: %f\n",pos);
}

/** MotorWrite assigns PWM values to left Motor and right Motor;
 *  a possibility is to use the rc.chan_raw values coming from Controller (MAVLINK message)
 */

void MotorWrite(void)
{
    // printf("\033[2;50Hout1");
    // semContrPWM.acquire();
    // printf("\033[2;50Hout2");

    // MODE 1:
    //  leftMotor.Move(rc.chan1_raw-40000);
    //  rightMotor.Move(rc.chan2_raw);
   
    // MODE 2: 
    signs = 1;
    signt = 1;

    if (rc.chan3_raw == 1)
      {
        signs = -1; 
      }
    
    if (rc.chan4_raw == 1)
      { 
        signt = -1; 
      }

    left_pwm = signs*rc.chan1_raw+signt*rc.chan2_raw;
    right_pwm = signs*rc.chan1_raw-signt*rc.chan2_raw;

    leftMotor.Move(left_pwm);
    rightMotor.Move(right_pwm);

    printf("pwm left, right  %d, %d \n", left_pwm, right_pwm);

    // leftMotor.Move(7000);
    // rightMotor.Move(7000);
    // ThisThread::sleep_for(1000);

    // leftMotor.Move(10000);
    // rightMotor.Move(10000);
    // ThisThread::sleep_for(3000);

    // leftMotor.Move(15000);
    // rightMotor.Move(15000);
    // ThisThread::sleep_for(3000);

    // leftMotor.Move(10000);
    // rightMotor.Move(-10000);
    // ThisThread::sleep_for(1000);

    // leftMotor.Move(-10000);
    // rightMotor.Move(-10000);
    // ThisThread::sleep_for(1000);

    // leftMotor.Move(0);
    // rightMotor.Move(0);
    


}