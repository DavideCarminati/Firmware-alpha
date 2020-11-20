#include <mbed.h>
#include "cntrInit.hpp"
#include "rt_OneStep.hpp"
#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "PI_contr.h"          /* Model's header file */
#include "rtwtypes.h"
#include "global_vars.hpp"

#define CONTROLLER_STACK_SIZE 8092

#ifndef CONTROLLER_IO // TODO not needed in realta'
#define CONTROLLER_IO
static RT_MODEL_PI_contr_T PI_contr_M_;
static RT_MODEL_PI_contr_T *const PI_contr_MPtr = &PI_contr_M_;// Real-time model 
static DW_PI_contr_T PI_contr_DW;      // Observable states

#endif

DigitalOut initLED(LED1,1);

const char* Controller_thread_name = "controller";

Thread Controller(osPriorityRealtime,CONTROLLER_STACK_SIZE,nullptr,Controller_thread_name);

void cntrInit(void)
{
    led_lock.lock();
    initLED = 0;
    RT_MODEL_PI_contr_T *const PI_contr_M = PI_contr_MPtr;
    // Pack model data into RTM
    PI_contr_M->dwork = &PI_contr_DW;

    // Initialize model
    PI_contr_initialize(PI_contr_M, &PI_contr_U, &PI_contr_Y);
    
    ThisThread::sleep_for(2000);
    // Spawn controller task
    Controller.start(callback(rt_OneStep,PI_contr_M));
    
    initLED = !initLED;
    led_lock.unlock();

}