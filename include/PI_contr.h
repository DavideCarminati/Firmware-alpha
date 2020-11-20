//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: PI_contr.h
//
// Code generated for Simulink model 'PI_contr'.
//
// Model version                  : 1.6
// Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
// C/C++ source code generated on : Tue Nov 17 15:54:12 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_PI_contr_h_
#define RTW_HEADER_PI_contr_h_
#include <cmath>
#include <string.h>
#ifndef PI_contr_COMMON_INCLUDES_
# define PI_contr_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 // PI_contr_COMMON_INCLUDES_

#include "PI_contr_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rt_defines.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// Block states (default storage) for system '<Root>'
typedef struct {
  real_T Integrator_psi_DSTATE;        // '<Root>/Integrator_psi'
} DW_PI_contr_T;

// External inputs (root inport signals with default storage)
typedef struct {
  real_T vel_ref;                      // '<Root>/vel_ref'
  real_T px_goal;                      // '<Root>/px_goal'
  real_T psi_ref;                      // '<Root>/psi_ref'
  real_T vel_odom;                     // '<Root>/vel_odom'
  real_T psi_odom;                     // '<Root>/psi_odom'
  real_T py_goal;                      // '<Root>/py_goal'
  real_T px_start;                     // '<Root>/px_start'
  real_T py_start;                     // '<Root>/py_start'
  real_T py_odom;                      // '<Root>/py_odom'
  real_T px_odom;                      // '<Root>/px_odom'
} ExtU_PI_contr_T;

// External outputs (root outports fed by signals with default storage)
typedef struct {
  real_T pwm_right;                    // '<Root>/pwm_right'
  real_T pwm_left;                     // '<Root>/pwm_left'
} ExtY_PI_contr_T;

// Real-time Model Data Structure
struct tag_RTM_PI_contr_T {
  const char_T * volatile errorStatus;
  DW_PI_contr_T *dwork;
};

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void PI_contr_initialize(RT_MODEL_PI_contr_T *const PI_contr_M,
    ExtU_PI_contr_T *PI_contr_U, ExtY_PI_contr_T *PI_contr_Y);
  extern void PI_contr_step(RT_MODEL_PI_contr_T *const PI_contr_M,
    ExtU_PI_contr_T *PI_contr_U, ExtY_PI_contr_T *PI_contr_Y);
  extern void PI_contr_terminate(RT_MODEL_PI_contr_T *const PI_contr_M);

#ifdef __cplusplus

}
#endif

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Ki_psi' : Eliminated nontunable gain of 1
//  Block '<Root>/Ki_x' : Eliminated nontunable gain of 1
//  Block '<Root>/Kp_psi' : Eliminated nontunable gain of 1
//  Block '<Root>/Kp_x' : Eliminated nontunable gain of 1
//  Block '<Root>/normlz_vel' : Eliminated nontunable gain of 1


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'PI_contr'

#endif                                 // RTW_HEADER_PI_contr_h_

//
// File trailer for generated code.
//
// [EOF]
//
