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
#include "rt_OneStep.hpp"

// Semaphore semDecode(0), semEncode(0);


DigitalOut led(LED3,1);

uint64_t epoch;
uint32_t wdgTime;

Timer timer;

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

void rt_OneStep(RT_MODEL_feedback_control_T *const feedback_control_M)
{
  
  Watchdog &watchdog = Watchdog::get_instance();
  watchdog.start(200);
  timer.start();
  while (1)
  {
    epoch = Kernel::get_ms_count();
    timer.reset();
    // static boolean_T OverrunFlag = false;

    /* Disable interrupts here */
    // __disable_irq();

    /* Check for overrun */
    // if (OverrunFlag) {
    //   rtmSetErrorStatus(feedback_control_M, "Overrun");
    //   return;
    // }

    // OverrunFlag = true;
    
    led = !led;

    /* Save FPU context here (if necessary) */
    /* Re-enable timer or interrupt here */
    /* Set model inputs here */
    
    #if PIL_MODE
      semDecode.acquire(); 
    #endif

    // CRITICAL: Includo la codifica e decodifica dei msg mavlink nel controllore anche se forse sarebbe piu' comodo metterla in UDPComm!

    // /* Step the model for base rate */
    feedback_control_step(feedback_control_M, &feedback_control_U,
                          &feedback_control_Y);

    // /* Get model outputs here */

    #if PIL_MODE
      semEncode.release();
    #endif

    /* Indicate task complete */
    // OverrunFlag = false;

    /* Disable interrupts here */
    /* Restore FPU context here (if necessary) */
    /* Enable interrupts here */
    // __enable_irq();

    int elapsed = timer.read_us();
    wdgTime = watchdog.get_timeout();
    printf("\033[3;1Hwdg: %lu (timer: %d)",wdgTime,elapsed);
    watchdog.kick();
    
    ThisThread::sleep_until(epoch+50); // 50ms is the step time!!
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