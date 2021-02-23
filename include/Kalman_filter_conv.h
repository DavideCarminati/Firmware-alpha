//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Kalman_filter_conv.h
//
// Code generated for Simulink model 'Kalman_filter_conv'.
//
// Model version                  : 1.51
// Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
// C/C++ source code generated on : Tue Feb 23 17:56:43 2021
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_Kalman_filter_conv_h_
#define RTW_HEADER_Kalman_filter_conv_h_
#include <cmath>
#include <string.h>
#ifndef Kalman_filter_conv_COMMON_INCLUDES_
# define Kalman_filter_conv_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 // Kalman_filter_conv_COMMON_INCLUDES_

#include "Kalman_filter_conv_types.h"
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
  real_T UnitDelay_DSTATE;             // '<S1>/Unit Delay'
  real_T UnitDelay1_DSTATE;            // '<S1>/Unit Delay1'
  real_T UnitDelay_DSTATE_n[5];        // '<S2>/Unit Delay'
  real_T UnitDelay1_DSTATE_e[3];       // '<S2>/Unit Delay1'
  real_T P_N_N[25];                    // '<S2>/MATLAB Function'
} DW_Kalman_filter_conv_T;

// Constant parameters (default storage)
typedef struct {
  // Expression: Q
  //  Referenced by: '<S2>/Constant'

  real_T Constant_Value[25];

  // Expression: x0
  //  Referenced by: '<S2>/Unit Delay'

  real_T UnitDelay_InitialCondition[5];

  // Expression: R
  //  Referenced by: '<S2>/Constant1'

  real_T Constant1_Value[9];
} ConstP_Kalman_filter_conv_T;

// External inputs (root inport signals with default storage)
typedef struct {
  real_T pos_l;                        // '<Root>/pos_l'
  real_T pos_r;                        // '<Root>/pos_r'
  real_T psi;                          // '<Root>/psi'
  real_T ax;                           // '<Root>/ax'
  real_T ay;                           // '<Root>/ay'
} ExtU_Kalman_filter_conv_T;

// External outputs (root outports fed by signals with default storage)
typedef struct {
  real_T X_est;                        // '<Root>/X_est'
  real_T Y_est;                        // '<Root>/Y_est'
  real_T psi_est;                      // '<Root>/psi_est'
  real_T Vx_est;                       // '<Root>/Vx_est'
  real_T Vy_est;                       // '<Root>/Vy_est'
} ExtY_Kalman_filter_conv_T;

// Real-time Model Data Structure
struct tag_RTM_Kalman_filter_conv_T {
  const char_T * volatile errorStatus;
  DW_Kalman_filter_conv_T *dwork;
};

// Constant parameters (default storage)
extern const ConstP_Kalman_filter_conv_T Kalman_filter_conv_ConstP;

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void Kalman_filter_conv_initialize(RT_MODEL_Kalman_filter_conv_T *const
    Kalman_filter_conv_M, ExtU_Kalman_filter_conv_T *Kalman_filter_conv_U,
    ExtY_Kalman_filter_conv_T *Kalman_filter_conv_Y);
  extern void Kalman_filter_conv_step(RT_MODEL_Kalman_filter_conv_T *const
    Kalman_filter_conv_M, ExtU_Kalman_filter_conv_T *Kalman_filter_conv_U,
    ExtY_Kalman_filter_conv_T *Kalman_filter_conv_Y);
  extern void Kalman_filter_conv_terminate(RT_MODEL_Kalman_filter_conv_T *const
    Kalman_filter_conv_M);

#ifdef __cplusplus

}
#endif

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
//  '<Root>' : 'Kalman_filter_conv'
//  '<S1>'   : 'Kalman_filter_conv/EKF'
//  '<S2>'   : 'Kalman_filter_conv/EKF/EKF'
//  '<S3>'   : 'Kalman_filter_conv/EKF/MATLAB Function'
//  '<S4>'   : 'Kalman_filter_conv/EKF/MATLAB Function1'
//  '<S5>'   : 'Kalman_filter_conv/EKF/EKF/F'
//  '<S6>'   : 'Kalman_filter_conv/EKF/EKF/H'
//  '<S7>'   : 'Kalman_filter_conv/EKF/EKF/MATLAB Function'
//  '<S8>'   : 'Kalman_filter_conv/EKF/EKF/f'

#endif                                 // RTW_HEADER_Kalman_filter_conv_h_

//
// File trailer for generated code.
//
// [EOF]
//
