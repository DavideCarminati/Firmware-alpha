//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: feedback_control.h
//
// Code generated for Simulink model 'feedback_control'.
//
// Model version                  : 1.85
// Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
// C/C++ source code generated on : Thu May 21 16:56:39 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_feedback_control_h_
#define RTW_HEADER_feedback_control_h_
#include <string.h>
#ifndef feedback_control_COMMON_INCLUDES_
# define feedback_control_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 // feedback_control_COMMON_INCLUDES_

#include "feedback_control_types.h"
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
  real32_T Integrator_DSTATE;          // '<S31>/Integrator'
  real32_T UD_DSTATE;                  // '<S26>/UD'
} DW_feedback_control_T;

// External inputs (root inport signals with default storage)
typedef struct {
  real32_T psi_ref;                  // '<Root>/ref'
  real32_T X_ref;                     // reference velocity
  real32_T psi_est;                  // '<Root>/est'
  real32_T X_est;
} ExtU_feedback_control_T;

// External outputs (root outports fed by signals with default storage)
typedef struct {
  real32_T pwm_left;                          // '<Root>/u'
  real32_T pwm_right;
} ExtY_feedback_control_T;

// Real-time Model Data Structure
struct tag_RTM_feedback_control_T {
  const char_T * volatile errorStatus;
  DW_feedback_control_T *dwork;
};

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void feedback_control_initialize(RT_MODEL_feedback_control_T *const
    feedback_control_M, ExtU_feedback_control_T *feedback_control_U,
    ExtY_feedback_control_T *feedback_control_Y);
  extern void feedback_control_step(RT_MODEL_feedback_control_T *const
    feedback_control_M, ExtU_feedback_control_T *feedback_control_U,
    ExtY_feedback_control_T *feedback_control_Y);
  extern void feedback_control_terminate(RT_MODEL_feedback_control_T *const
    feedback_control_M);

#ifdef __cplusplus

}
#endif

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S26>/DTDup' : Unused code path elimination
//  Block '<Root>/Data Type Conversion' : Eliminate redundant data type conversion


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
//  '<Root>' : 'feedback_control'
//  '<S1>'   : 'feedback_control/PID_cntr'
//  '<S2>'   : 'feedback_control/PID_cntr/Anti-windup'
//  '<S3>'   : 'feedback_control/PID_cntr/D Gain'
//  '<S4>'   : 'feedback_control/PID_cntr/Filter'
//  '<S5>'   : 'feedback_control/PID_cntr/Filter ICs'
//  '<S6>'   : 'feedback_control/PID_cntr/I Gain'
//  '<S7>'   : 'feedback_control/PID_cntr/Ideal P Gain'
//  '<S8>'   : 'feedback_control/PID_cntr/Ideal P Gain Fdbk'
//  '<S9>'   : 'feedback_control/PID_cntr/Integrator'
//  '<S10>'  : 'feedback_control/PID_cntr/Integrator ICs'
//  '<S11>'  : 'feedback_control/PID_cntr/N Copy'
//  '<S12>'  : 'feedback_control/PID_cntr/N Gain'
//  '<S13>'  : 'feedback_control/PID_cntr/P Copy'
//  '<S14>'  : 'feedback_control/PID_cntr/Parallel P Gain'
//  '<S15>'  : 'feedback_control/PID_cntr/Reset Signal'
//  '<S16>'  : 'feedback_control/PID_cntr/Saturation'
//  '<S17>'  : 'feedback_control/PID_cntr/Saturation Fdbk'
//  '<S18>'  : 'feedback_control/PID_cntr/Sum'
//  '<S19>'  : 'feedback_control/PID_cntr/Sum Fdbk'
//  '<S20>'  : 'feedback_control/PID_cntr/Tracking Mode'
//  '<S21>'  : 'feedback_control/PID_cntr/Tracking Mode Sum'
//  '<S22>'  : 'feedback_control/PID_cntr/postSat Signal'
//  '<S23>'  : 'feedback_control/PID_cntr/preSat Signal'
//  '<S24>'  : 'feedback_control/PID_cntr/Anti-windup/Passthrough'
//  '<S25>'  : 'feedback_control/PID_cntr/D Gain/Internal Parameters'
//  '<S26>'  : 'feedback_control/PID_cntr/Filter/Differentiator'
//  '<S27>'  : 'feedback_control/PID_cntr/Filter ICs/Internal IC - Differentiator'
//  '<S28>'  : 'feedback_control/PID_cntr/I Gain/Internal Parameters'
//  '<S29>'  : 'feedback_control/PID_cntr/Ideal P Gain/Passthrough'
//  '<S30>'  : 'feedback_control/PID_cntr/Ideal P Gain Fdbk/Disabled'
//  '<S31>'  : 'feedback_control/PID_cntr/Integrator/Discrete'
//  '<S32>'  : 'feedback_control/PID_cntr/Integrator ICs/Internal IC'
//  '<S33>'  : 'feedback_control/PID_cntr/N Copy/Disabled wSignal Specification'
//  '<S34>'  : 'feedback_control/PID_cntr/N Gain/Passthrough'
//  '<S35>'  : 'feedback_control/PID_cntr/P Copy/Disabled'
//  '<S36>'  : 'feedback_control/PID_cntr/Parallel P Gain/Internal Parameters'
//  '<S37>'  : 'feedback_control/PID_cntr/Reset Signal/Disabled'
//  '<S38>'  : 'feedback_control/PID_cntr/Saturation/Passthrough'
//  '<S39>'  : 'feedback_control/PID_cntr/Saturation Fdbk/Disabled'
//  '<S40>'  : 'feedback_control/PID_cntr/Sum/Sum_PID'
//  '<S41>'  : 'feedback_control/PID_cntr/Sum Fdbk/Disabled'
//  '<S42>'  : 'feedback_control/PID_cntr/Tracking Mode/Disabled'
//  '<S43>'  : 'feedback_control/PID_cntr/Tracking Mode Sum/Passthrough'
//  '<S44>'  : 'feedback_control/PID_cntr/postSat Signal/Forward_Path'
//  '<S45>'  : 'feedback_control/PID_cntr/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_feedback_control_h_

//
// File trailer for generated code.
//
// [EOF]
//
