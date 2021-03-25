//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Kalman_filter_conv.h
//
// Code generated for Simulink model 'Kalman_filter_conv'.
//
// Model version                  : 1.14
// Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
// C/C++ source code generated on : Tue Mar  9 15:55:55 2021
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

// Block signals (default storage)
typedef struct {
  real_T F[25];                        // '<S1>/F'
  real_T rtb_F_m[25];
  real_T rtb_F_c[25];
  real_T K[15];
  real_T y[15];
  real_T rtb_H_k[15];
  real_T B[9];
  real_T R[9];                         // '<Root>/MATLAB Function2'
  real_T x[5];                         // '<S1>/f'
  int8_T b_I[25];
  real_T dv0[3];
  real_T rtb_H_c[3];
  real_T dv1[3];
  int8_T H[15];                        // '<S1>/H'
  real_T a21;
  real_T w_l;                          // '<Root>/Gain3'
  real_T w_r;                          // '<Root>/Gain4'
} B_Kalman_filter_conv_T;

// Block states (default storage) for system '<Root>'
typedef struct {
  real_T UnitDelay2_DSTATE;            // '<Root>/Unit Delay2'
  real_T UnitDelay3_DSTATE;            // '<Root>/Unit Delay3'
  real_T UnitDelay_DSTATE[5];          // '<S1>/Unit Delay'
  real_T DiscreteTimeIntegrator_DSTATE;// '<Root>/Discrete-Time Integrator'
  real_T P_N_N[25];                    // '<S1>/MATLAB Function'
} DW_Kalman_filter_conv_T;

// External inputs (root inport signals with default storage)
typedef struct {
  real_T pos_l;                        // '<Root>/pos_l'
  real_T pos_r;                        // '<Root>/pos_r'
  real_T psi_mag;                      // '<Root>/psi_mag'
  real_T ax;                           // '<Root>/ax'
  real_T ay;                           // '<Root>/ay'
} ExtU_Kalman_filter_conv_T;

// External outputs (root outports fed by signals with default storage)
typedef struct {
  real_T X;                            // '<Root>/X'
  real_T Y;                            // '<Root>/Y'
  real_T psi;                          // '<Root>/psi '
  real_T Vx;                           // '<Root>/Vx '
  real_T Vy;                           // '<Root>/Vy '
} ExtY_Kalman_filter_conv_T;

// Parameters (default storage)
struct P_Kalman_filter_conv_T_ {
  real_T cov_X_Value;                  // Expression: 1e-12
                                          //  Referenced by: '<Root>/cov_X'

  real_T cov_Y_Value;                  // Expression: 1e-12
                                          //  Referenced by: '<Root>/cov_Y'

  real_T cov_Vx_Value;                 // Expression: 1e-6
                                          //  Referenced by: '<Root>/cov_Vx'

  real_T cov_Vy_Value;                 // Expression: 1e-3
                                          //  Referenced by: '<Root>/cov_Vy'

  real_T cov_psi_Value;                // Expression: 1e-2
                                          //  Referenced by: '<Root>/cov_psi'

  real_T UnitDelay2_InitialCondition;  // Expression: 0
                                          //  Referenced by: '<Root>/Unit Delay2'

  real_T Gain3_Gain;                   // Expression: 2*pi*1920*2/360/1920/0.2
                                          //  Referenced by: '<Root>/Gain3'

  real_T UnitDelay3_InitialCondition;  // Expression: 0
                                          //  Referenced by: '<Root>/Unit Delay3'

  real_T Gain4_Gain;                   // Expression: 2*pi*2/360/0.2
                                          //  Referenced by: '<Root>/Gain4'

  real_T UnitDelay_InitialCondition[5];// Expression: [0 0 0 0 0]
                                          //  Referenced by: '<S1>/Unit Delay'

  real_T cov_Vx_enc_Value;             // Expression: 1e-3
                                          //  Referenced by: '<Root>/cov_Vx_enc'

  real_T cov_psi_enc_Value;            // Expression: 1e-3
                                          //  Referenced by: '<Root>/cov_psi_enc'

  real_T cov_psi_mag_Value;            // Expression: 0.01
                                          //  Referenced by: '<Root>/cov_psi_mag'

  real_T DiscreteTimeIntegrator_gainval;
                           // Computed Parameter: DiscreteTimeIntegrator_gainval
                              //  Referenced by: '<Root>/Discrete-Time Integrator'

  real_T DiscreteTimeIntegrator_IC;    // Expression: 0
                                          //  Referenced by: '<Root>/Discrete-Time Integrator'

};

// Real-time Model Data Structure
struct tag_RTM_Kalman_filter_conv_T {
  const char_T * volatile errorStatus;
  B_Kalman_filter_conv_T *blockIO;
  DW_Kalman_filter_conv_T *dwork;
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern P_Kalman_filter_conv_T Kalman_filter_conv_P;

#ifdef __cplusplus

}
#endif

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
//  '<S1>'   : 'Kalman_filter_conv/EKF1'
//  '<S2>'   : 'Kalman_filter_conv/MATLAB Function1'
//  '<S3>'   : 'Kalman_filter_conv/MATLAB Function2'
//  '<S4>'   : 'Kalman_filter_conv/MATLAB Function3'
//  '<S5>'   : 'Kalman_filter_conv/EKF1/F'
//  '<S6>'   : 'Kalman_filter_conv/EKF1/H'
//  '<S7>'   : 'Kalman_filter_conv/EKF1/MATLAB Function'
//  '<S8>'   : 'Kalman_filter_conv/EKF1/f'

#endif                                 // RTW_HEADER_Kalman_filter_conv_h_

//
// File trailer for generated code.
//
// [EOF]
//
