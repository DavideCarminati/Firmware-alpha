#include <mbed.h>
#include "cntrInit.hpp"
#include "rt_OneStep.hpp"

#define CONTROLLER_STACK_SIZE 8092

DigitalOut initLED(LED1);

const char* Controller_thread_name = "controller";

Thread Controller(osPriorityRealtime,CONTROLLER_STACK_SIZE,nullptr,Controller_thread_name);

void cntrInit(void)
{
    initLED = 0;
    RT_MODEL_feedback_control_T *const feedback_control_M = feedback_control_MPtr;

    /* Pack model data into RTM */
    feedback_control_M->dwork = &feedback_control_DW;

    /* Initialize model */
    feedback_control_initialize(feedback_control_M, &feedback_control_U,
        &feedback_control_Y);
    
    ThisThread::sleep_for(2000);
    // Spawn controller task
    Controller.start(callback(rt_OneStep,feedback_control_M));
    
    initLED = !initLED;

}