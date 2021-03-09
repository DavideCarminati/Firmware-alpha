//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: APF_conver.h
//
// Code generated for Simulink model 'APF_conver'.
//
// Model version                  : 1.107
// Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
// C/C++ source code generated on : Thu Mar  4 14:29:04 2021
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_APF_conver_h_
#define RTW_HEADER_APF_conver_h_
#include <cmath>
#include <math.h>
#include <string.h>
#ifndef APF_conver_COMMON_INCLUDES_
# define APF_conver_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 // APF_conver_COMMON_INCLUDES_

#include "APF_conver_types.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// Block states (default storage) for system '<Root>'
typedef struct {
  real_T Integrator_DSTATE;            // '<S38>/Integrator'
  real_T Filter_DSTATE;                // '<S33>/Filter'
  real_T Integrator_DSTATE_e;          // '<S82>/Integrator'
  real_T Filter_DSTATE_m;              // '<S77>/Filter'
} DW_APF_conver_T;

// External inputs (root inport signals with default storage)
typedef struct {
  real_T X_est;                        // '<Root>/X_est'
  real_T Y_est;                        // '<Root>/Y_est'
  real_T psi_est;                      // '<Root>/psi_est'
  real_T Vx_est;                       // '<Root>/Vx_est'
} ExtU_APF_conver_T;

// External outputs (root outports fed by signals with default storage)
typedef struct {
  real_T PWM_l;                        // '<Root>/PWM_l'
  real_T PWM_r;                        // '<Root>/PWM_r'
} ExtY_APF_conver_T;

// Parameters (default storage)
struct P_APF_conver_T_ {
  real_T Kd_Vx;                        // Variable: Kd_Vx
                                          //  Referenced by: '<S32>/Derivative Gain'

  real_T Kd_psi;                       // Variable: Kd_psi
                                          //  Referenced by: '<S76>/Derivative Gain'

  real_T Ki_Vx;                        // Variable: Ki_Vx
                                          //  Referenced by: '<S35>/Integral Gain'

  real_T Ki_psi;                       // Variable: Ki_psi
                                          //  Referenced by: '<S79>/Integral Gain'

  real_T Kp_Vx;                        // Variable: Kp_Vx
                                          //  Referenced by: '<S43>/Proportional Gain'

  real_T Kp_psi;                       // Variable: Kp_psi
                                          //  Referenced by: '<S87>/Proportional Gain'

  real_T X_goal;                       // Variable: X_goal
                                          //  Referenced by: '<Root>/Constant'

  real_T Y_goal;                       // Variable: Y_goal
                                          //  Referenced by: '<Root>/Constant1'

  real_T ox;                           // Variable: ox
                                          //  Referenced by: '<Root>/Constant2'

  real_T oy;                           // Variable: oy
                                          //  Referenced by: '<Root>/Constant3'

  real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S33>/Filter'

  real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S77>/Filter'

  real_T PIDController_InitialConditio_d;
                              // Mask Parameter: PIDController_InitialConditio_d
                                 //  Referenced by: '<S38>/Integrator'

  real_T PIDController1_InitialConditi_k;
                              // Mask Parameter: PIDController1_InitialConditi_k
                                 //  Referenced by: '<S82>/Integrator'

  real_T PIDController_N;              // Mask Parameter: PIDController_N
                                          //  Referenced by: '<S41>/Filter Coefficient'

  real_T PIDController1_N;             // Mask Parameter: PIDController1_N
                                          //  Referenced by: '<S85>/Filter Coefficient'

  real_T Integrator_gainval;           // Computed Parameter: Integrator_gainval
                                          //  Referenced by: '<S38>/Integrator'

  real_T Filter_gainval;               // Computed Parameter: Filter_gainval
                                          //  Referenced by: '<S33>/Filter'

  real_T Saturation1_UpperSat;         // Expression: 1
                                          //  Referenced by: '<S4>/Saturation1'

  real_T Saturation1_LowerSat;         // Expression: -1
                                          //  Referenced by: '<S4>/Saturation1'

  real_T Constant_Value;               // Expression: 0
                                          //  Referenced by: '<S6>/Constant'

  real_T Gain_Gain;                    // Expression: 180/pi
                                          //  Referenced by: '<S4>/Gain'

  real_T Gain2_Gain;                   // Expression: 180/pi
                                          //  Referenced by: '<S4>/Gain2'

  real_T Integrator_gainval_b;       // Computed Parameter: Integrator_gainval_b
                                        //  Referenced by: '<S82>/Integrator'

  real_T Filter_gainval_j;             // Computed Parameter: Filter_gainval_j
                                          //  Referenced by: '<S77>/Filter'

  real_T u180_Gain;                    // Expression: 1/180
                                          //  Referenced by: '<S4>/1//180'

  real_T Saturation_UpperSat;          // Expression: 0.5
                                          //  Referenced by: '<S4>/Saturation'

  real_T Saturation_LowerSat;          // Expression: -0.5
                                          //  Referenced by: '<S4>/Saturation'

  real_T _Gain;                        // Expression: 20000
                                          //  Referenced by: '<S5>/   '

  real_T Saturation1_UpperSat_m;       // Expression: 20000
                                          //  Referenced by: '<S5>/Saturation1'

  real_T Saturation1_LowerSat_n;       // Expression: -20000
                                          //  Referenced by: '<S5>/Saturation1'

  real_T _Gain_p;                      // Expression: 20000
                                          //  Referenced by: '<S5>/ '

  real_T Saturation_UpperSat_i;        // Expression: 20000
                                          //  Referenced by: '<S5>/Saturation'

  real_T Saturation_LowerSat_f;        // Expression: -20000
                                          //  Referenced by: '<S5>/Saturation'

};

// Real-time Model Data Structure
struct tag_RTM_APF_conver_T {
  const char_T * volatile errorStatus;
  DW_APF_conver_T *dwork;
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern P_APF_conver_T APF_conver_P;

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void APF_conver_initialize(RT_MODEL_APF_conver_T *const APF_conver_M,
    ExtU_APF_conver_T *APF_conver_U, ExtY_APF_conver_T *APF_conver_Y);
  extern void APF_conver_step(RT_MODEL_APF_conver_T *const APF_conver_M,
    ExtU_APF_conver_T *APF_conver_U, ExtY_APF_conver_T *APF_conver_Y);
  extern void APF_conver_terminate(RT_MODEL_APF_conver_T *const APF_conver_M);

#ifdef __cplusplus

}
#endif

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S98>/Scope' : Unused code path elimination
//  Block '<S98>/Scope1' : Unused code path elimination
//  Block '<S98>/Scope3' : Unused code path elimination
//  Block '<S98>/Scope4' : Unused code path elimination
//  Block '<S99>/Scope1' : Unused code path elimination


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
//  '<Root>' : 'APF_conver'
//  '<S1>'   : 'APF_conver/GUIDANCE & CONTROL'
//  '<S2>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK'
//  '<S3>'   : 'APF_conver/GUIDANCE & CONTROL/GUIDANCE BLOCK'
//  '<S4>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER'
//  '<S5>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/Command module'
//  '<S6>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/IsNonZero'
//  '<S7>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller'
//  '<S8>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1'
//  '<S9>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Anti-windup'
//  '<S10>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/D Gain'
//  '<S11>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Filter'
//  '<S12>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Filter ICs'
//  '<S13>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/I Gain'
//  '<S14>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Ideal P Gain'
//  '<S15>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Ideal P Gain Fdbk'
//  '<S16>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Integrator'
//  '<S17>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Integrator ICs'
//  '<S18>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/N Copy'
//  '<S19>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/N Gain'
//  '<S20>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/P Copy'
//  '<S21>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Parallel P Gain'
//  '<S22>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Reset Signal'
//  '<S23>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Saturation'
//  '<S24>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Saturation Fdbk'
//  '<S25>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Sum'
//  '<S26>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Sum Fdbk'
//  '<S27>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Tracking Mode'
//  '<S28>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Tracking Mode Sum'
//  '<S29>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/postSat Signal'
//  '<S30>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/preSat Signal'
//  '<S31>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Anti-windup/Passthrough'
//  '<S32>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/D Gain/Internal Parameters'
//  '<S33>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S34>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S35>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/I Gain/Internal Parameters'
//  '<S36>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Ideal P Gain/Passthrough'
//  '<S37>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S38>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Integrator/Discrete'
//  '<S39>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Integrator ICs/Internal IC'
//  '<S40>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/N Copy/Disabled'
//  '<S41>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/N Gain/Internal Parameters'
//  '<S42>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/P Copy/Disabled'
//  '<S43>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S44>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Reset Signal/Disabled'
//  '<S45>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Saturation/Passthrough'
//  '<S46>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Saturation Fdbk/Disabled'
//  '<S47>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Sum/Sum_PID'
//  '<S48>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Sum Fdbk/Disabled'
//  '<S49>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Tracking Mode/Disabled'
//  '<S50>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S51>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/postSat Signal/Forward_Path'
//  '<S52>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller/preSat Signal/Forward_Path'
//  '<S53>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Anti-windup'
//  '<S54>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/D Gain'
//  '<S55>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Filter'
//  '<S56>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Filter ICs'
//  '<S57>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/I Gain'
//  '<S58>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Ideal P Gain'
//  '<S59>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Ideal P Gain Fdbk'
//  '<S60>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Integrator'
//  '<S61>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Integrator ICs'
//  '<S62>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/N Copy'
//  '<S63>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/N Gain'
//  '<S64>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/P Copy'
//  '<S65>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Parallel P Gain'
//  '<S66>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Reset Signal'
//  '<S67>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Saturation'
//  '<S68>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Saturation Fdbk'
//  '<S69>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Sum'
//  '<S70>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Sum Fdbk'
//  '<S71>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Tracking Mode'
//  '<S72>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Tracking Mode Sum'
//  '<S73>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/postSat Signal'
//  '<S74>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/preSat Signal'
//  '<S75>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Anti-windup/Passthrough'
//  '<S76>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/D Gain/Internal Parameters'
//  '<S77>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Filter/Disc. Forward Euler Filter'
//  '<S78>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S79>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/I Gain/Internal Parameters'
//  '<S80>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Ideal P Gain/Passthrough'
//  '<S81>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S82>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Integrator/Discrete'
//  '<S83>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Integrator ICs/Internal IC'
//  '<S84>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/N Copy/Disabled'
//  '<S85>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/N Gain/Internal Parameters'
//  '<S86>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/P Copy/Disabled'
//  '<S87>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S88>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Reset Signal/Disabled'
//  '<S89>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Saturation/Passthrough'
//  '<S90>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Saturation Fdbk/Disabled'
//  '<S91>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Sum/Sum_PID'
//  '<S92>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Sum Fdbk/Disabled'
//  '<S93>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Tracking Mode/Disabled'
//  '<S94>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S95>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/postSat Signal/Forward_Path'
//  '<S96>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL BLOCK/CONTROLLER/PID Controller1/preSat Signal/Forward_Path'
//  '<S97>'  : 'APF_conver/GUIDANCE & CONTROL/GUIDANCE BLOCK/GUIDANCE BLOCK'
//  '<S98>'  : 'APF_conver/GUIDANCE & CONTROL/GUIDANCE BLOCK/GUIDANCE BLOCK/APF'
//  '<S99>'  : 'APF_conver/GUIDANCE & CONTROL/GUIDANCE BLOCK/GUIDANCE BLOCK/INITIAL ORIENTATION'
//  '<S100>' : 'APF_conver/GUIDANCE & CONTROL/GUIDANCE BLOCK/GUIDANCE BLOCK/APF/IAPF'
//  '<S101>' : 'APF_conver/GUIDANCE & CONTROL/GUIDANCE BLOCK/GUIDANCE BLOCK/INITIAL ORIENTATION/MATLAB Function'

#endif                                 // RTW_HEADER_APF_conver_h_

//
// File trailer for generated code.
//
// [EOF]
//
