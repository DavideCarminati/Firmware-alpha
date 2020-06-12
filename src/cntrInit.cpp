#include <mbed.h>
#include "cntrInit.hpp"
#include "rt_OneStep.hpp"
#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "feedback_control.h"          /* Model's header file */
#include "rtwtypes.h"
#include "global_vars.hpp"

#define CONTROLLER_STACK_SIZE 8092

#ifndef CONTROLLER_IO // TODO not needed in realta'
#define CONTROLLER_IO
static RT_MODEL_feedback_control_T feedback_control_M_;
static RT_MODEL_feedback_control_T *const feedback_control_MPtr =
  &feedback_control_M_;                /* Real-time model */
static DW_feedback_control_T feedback_control_DW;/* Observable states */

#endif

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