#include "outportInit.hpp"

float pos = 0.0;

// PwmOut servo2(PTC10); ///< The PIN enable for PWM is PTC10.

// EventQueue queue;
Event<void(void)> servowriteEvent(&queue,Servo1Write);

Thread ServoWrite(osPriorityNormal,8092,nullptr,"servoWrite");

// CRITICAL Also in here I have to protect the read of the output of the controller algorithm with a mutex!!!
void outportInit()
{
    servo1.calibrate(0.0005,90); // 0.0005 s from center (1.5ms) to max/min
    ServoWrite.start(postServoEvent);
    queue.dispatch();
}

void postServoEvent(void)
{
    servowriteEvent.period(50);
    servowriteEvent.delay(500);
    servowriteEvent.post();
}

void Servo1Write(void)
{
    // TODO add semaphore in here!
    pos = feedback_control_Y.u;//*180;
    servo1.write(pos);
    printf("\033[1;1H");
    printf("pos given to pwm port: %f\n",pos);
}