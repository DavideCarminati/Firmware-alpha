/*! @file rt_OneStep.cpp
    
    @brief It performs a time step of the controller algorithm checking whether it respects the Real-Time deadline.

*/

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'feedback_control'.
 *
 * Model version                  : 1.76
 * Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
 * C/C++ source code generated on : Tue Apr 14 12:36:57 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "PI_contr.h"          /* Model's header file */
#include "rtwtypes.h"
#include "math.h"

#include "global_vars.hpp"
#include "global_msgs.hpp"
#include "common/mavlink.h"
#include "TankMotor.hpp"


#include "rt_OneStep.hpp"

// Semaphore semDecode(0), semEncode(0);


DigitalOut led(LED3,1);

uint64_t epoch;
uint32_t wdgTime;
// float pitch, roll;

Timer timer;

TankMotor leftMotor(PTC10,PTB23,PTA2), rightMotor(PTC11,PTB9,PTA1);
/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */

void rt_OneStep(RT_MODEL_PI_contr_T *const PI_contr_M)
{
  
  // Start watchdog
  Watchdog &watchdog = Watchdog::get_instance();
  watchdog.start(500); //350
  timer.start();
  while (1)
  {
    epoch = Kernel::get_ms_count();
    // timer.reset();
    // static boolean_T OverrunFlag = false;

    /* Disable interrupts here */
    // __disable_irq();

    /* Check for overrun */
    // if (OverrunFlag) {
    //   rtmSetErrorStatus(feedback_control_M, "Overrun");
    //   return;
    // }

    // OverrunFlag = true;
    
    if(led_lock.trylock())
    {
      led = !led;
      led_lock.unlock();
    }

    /* Save FPU context here (if necessary) */
    /* Re-enable timer or interrupt here */
    /* Set model inputs here */
    
    // UNCOMMENT THIS TO USE MAVLINK MSGS
    PI_contr_U.vel_ref = sqrt(pow(setpointsTrajectoryPlanner.vx,2) + pow(setpointsTrajectoryPlanner.vy,2));
    PI_contr_U.px_goal = setpointsTrajectoryPlanner.x;
    PI_contr_U.psi_ref = setpointsTrajectoryPlanner.yaw;
    PI_contr_U.vel_odom = sqrt(pow(odom.vx,2) + pow(odom.vy,2));
    // PI_contr_U.psi_odom
    PI_contr_U.py_goal = setpointsTrajectoryPlanner.y;
    PI_contr_U.px_start = setpointsTrajectoryPlanner.afx;
    PI_contr_U.py_start = setpointsTrajectoryPlanner.afy;
    PI_contr_U.py_odom = odom.y;
    PI_contr_U.px_odom = odom.x;
    printf("\033[1;1H");
    printf("vel ref: %f, vel odom: %f, odom x: %f, psi ref: %f\n", PI_contr_U.vel_ref, PI_contr_U.vel_odom, PI_contr_U.px_odom, PI_contr_U.psi_ref);
    
    #if PIL_MODE
      semDecode.acquire(); 
    #endif
    // semNavContr.acquire();

    // /* Step the model for base rate */
    PI_contr_step(PI_contr_M, &PI_contr_U, &PI_contr_Y);

    // /* Get model outputs here */

    #if PIL_MODE
      semEncode.release();
    #endif
    // semContrPWM.release();

    leftMotor.Move(PI_contr_Y.pwm_left);
    rightMotor.Move(PI_contr_Y.pwm_right);
    printf("\033[12;1H");
    printf("pwm: %f, %f\n", PI_contr_Y.pwm_left, PI_contr_Y.pwm_right);

    /* Indicate task complete */
    // OverrunFlag = false;

    /* Disable interrupts here */
    /* Restore FPU context here (if necessary) */
    /* Enable interrupts here */
    // __enable_irq();

    // int elapsed = timer.read_us();
    // wdgTime = watchdog.get_timeout();
    // wdgTime = 0;
    // printf("\033[3;1Hwdg: %lu (timer: %d)",wdgTime,elapsed);
    watchdog.kick();
    
    ThisThread::sleep_until(epoch+350); // 50ms is the step time!!
  }
  
//   /* Disable rt_OneStep() here */

//   /* Terminate model */
//   feedback_control_terminate(feedback_control_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */