//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: APF_conver.h
//
// Code generated for Simulink model 'APF_conver'.
//
// Model version                  : 1.114
// Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
// C/C++ source code generated on : Thu Mar 25 15:20:53 2021
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
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
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
  real_T Integrator_DSTATE;            // '<S39>/Integrator'
  real_T Filter_DSTATE;                // '<S34>/Filter'
  real_T Integrator_DSTATE_m;          // '<S83>/Integrator'
  real_T Filter_DSTATE_f;              // '<S78>/Filter'
  real_T en;                           // '<S99>/MATLAB Function'
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
                                          //  Referenced by: '<S33>/Derivative Gain'

  real_T Kd_psi;                       // Variable: Kd_psi
                                          //  Referenced by: '<S77>/Derivative Gain'

  real_T Ki_Vx;                        // Variable: Ki_Vx
                                          //  Referenced by: '<S36>/Integral Gain'

  real_T Ki_psi;                       // Variable: Ki_psi
                                          //  Referenced by: '<S80>/Integral Gain'

  real_T Kp_Vx;                        // Variable: Kp_Vx
                                          //  Referenced by: '<S44>/Proportional Gain'

  real_T Kp_psi;                       // Variable: Kp_psi
                                          //  Referenced by: '<S88>/Proportional Gain'

  real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S34>/Filter'

  real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S78>/Filter'

  real_T PIDController_InitialConditio_o;
                              // Mask Parameter: PIDController_InitialConditio_o
                                 //  Referenced by: '<S39>/Integrator'

  real_T PIDController1_InitialConditi_d;
                              // Mask Parameter: PIDController1_InitialConditi_d
                                 //  Referenced by: '<S83>/Integrator'

  real_T PIDController_N;              // Mask Parameter: PIDController_N
                                          //  Referenced by: '<S42>/Filter Coefficient'

  real_T PIDController1_N;             // Mask Parameter: PIDController1_N
                                          //  Referenced by: '<S86>/Filter Coefficient'

  real_T X_goal_Value;                 // Expression: 1
                                          //  Referenced by: '<Root>/X_goal'

  real_T Y_goal_Value;                 // Expression: 0
                                          //  Referenced by: '<Root>/Y_goal'

  real_T ox_Value;                     // Expression: 4
                                          //  Referenced by: '<Root>/ox'

  real_T oy_Value;                     // Expression: 4
                                          //  Referenced by: '<Root>/oy'

  real_T Integrator_gainval;           // Computed Parameter: Integrator_gainval
                                          //  Referenced by: '<S39>/Integrator'

  real_T Filter_gainval;               // Computed Parameter: Filter_gainval
                                          //  Referenced by: '<S34>/Filter'

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

  real_T Integrator_gainval_m;       // Computed Parameter: Integrator_gainval_m
                                        //  Referenced by: '<S83>/Integrator'

  real_T Filter_gainval_o;             // Computed Parameter: Filter_gainval_o
                                          //  Referenced by: '<S78>/Filter'

  real_T u180_Gain;                    // Expression: 1/180
                                          //  Referenced by: '<S4>/1//180'

  real_T Saturation_UpperSat;          // Expression: 0.5
                                          //  Referenced by: '<S4>/Saturation'

  real_T Saturation_LowerSat;          // Expression: -0.5
                                          //  Referenced by: '<S4>/Saturation'

  real_T _Gain;                        // Expression: 20000
                                          //  Referenced by: '<S5>/   '

  real_T Saturation1_UpperSat_h;       // Expression: 20000
                                          //  Referenced by: '<S5>/Saturation1'

  real_T Saturation1_LowerSat_k;       // Expression: -20000
                                          //  Referenced by: '<S5>/Saturation1'

  real_T _Gain_g;                      // Expression: 20000
                                          //  Referenced by: '<S5>/ '

  real_T Saturation_UpperSat_p;        // Expression: 20000
                                          //  Referenced by: '<S5>/Saturation'

  real_T Saturation_LowerSat_a;        // Expression: -20000
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
//  Block '<S4>/Rate Transition' : Unused code path elimination
//  Block '<S4>/Rate Transition1' : Unused code path elimination
//  Block '<S4>/Scope' : Unused code path elimination
//  Block '<S4>/Scope1' : Unused code path elimination
//  Block '<S4>/Scope2' : Unused code path elimination
//  Block '<S4>/To Workspace1' : Unused code path elimination
//  Block '<S4>/To Workspace5' : Unused code path elimination
//  Block '<S5>/Scope' : Unused code path elimination
//  Block '<S98>/Scope1' : Unused code path elimination
//  Block '<S98>/Scope3' : Unused code path elimination
//  Block '<S98>/Scope4' : Unused code path elimination


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
//  '<S2>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL '
//  '<S3>'   : 'APF_conver/GUIDANCE & CONTROL/GUIDANCE '
//  '<S4>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER'
//  '<S5>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL /Command module'
//  '<S6>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/IsNonZero'
//  '<S7>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/MATLAB Function'
//  '<S8>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller'
//  '<S9>'   : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1'
//  '<S10>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Anti-windup'
//  '<S11>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/D Gain'
//  '<S12>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Filter'
//  '<S13>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Filter ICs'
//  '<S14>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/I Gain'
//  '<S15>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Ideal P Gain'
//  '<S16>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Ideal P Gain Fdbk'
//  '<S17>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Integrator'
//  '<S18>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Integrator ICs'
//  '<S19>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/N Copy'
//  '<S20>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/N Gain'
//  '<S21>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/P Copy'
//  '<S22>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Parallel P Gain'
//  '<S23>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Reset Signal'
//  '<S24>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Saturation'
//  '<S25>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Saturation Fdbk'
//  '<S26>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Sum'
//  '<S27>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Sum Fdbk'
//  '<S28>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Tracking Mode'
//  '<S29>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Tracking Mode Sum'
//  '<S30>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/postSat Signal'
//  '<S31>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/preSat Signal'
//  '<S32>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Anti-windup/Passthrough'
//  '<S33>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/D Gain/Internal Parameters'
//  '<S34>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S35>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S36>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/I Gain/Internal Parameters'
//  '<S37>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Ideal P Gain/Passthrough'
//  '<S38>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S39>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Integrator/Discrete'
//  '<S40>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Integrator ICs/Internal IC'
//  '<S41>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/N Copy/Disabled'
//  '<S42>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/N Gain/Internal Parameters'
//  '<S43>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/P Copy/Disabled'
//  '<S44>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S45>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Reset Signal/Disabled'
//  '<S46>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Saturation/Passthrough'
//  '<S47>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Saturation Fdbk/Disabled'
//  '<S48>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Sum/Sum_PID'
//  '<S49>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Sum Fdbk/Disabled'
//  '<S50>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Tracking Mode/Disabled'
//  '<S51>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S52>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/postSat Signal/Forward_Path'
//  '<S53>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller/preSat Signal/Forward_Path'
//  '<S54>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Anti-windup'
//  '<S55>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/D Gain'
//  '<S56>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Filter'
//  '<S57>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Filter ICs'
//  '<S58>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/I Gain'
//  '<S59>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Ideal P Gain'
//  '<S60>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Ideal P Gain Fdbk'
//  '<S61>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Integrator'
//  '<S62>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Integrator ICs'
//  '<S63>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/N Copy'
//  '<S64>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/N Gain'
//  '<S65>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/P Copy'
//  '<S66>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Parallel P Gain'
//  '<S67>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Reset Signal'
//  '<S68>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Saturation'
//  '<S69>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Saturation Fdbk'
//  '<S70>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Sum'
//  '<S71>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Sum Fdbk'
//  '<S72>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Tracking Mode'
//  '<S73>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Tracking Mode Sum'
//  '<S74>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/postSat Signal'
//  '<S75>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/preSat Signal'
//  '<S76>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Anti-windup/Passthrough'
//  '<S77>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/D Gain/Internal Parameters'
//  '<S78>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Filter/Disc. Forward Euler Filter'
//  '<S79>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S80>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/I Gain/Internal Parameters'
//  '<S81>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Ideal P Gain/Passthrough'
//  '<S82>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S83>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Integrator/Discrete'
//  '<S84>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Integrator ICs/Internal IC'
//  '<S85>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/N Copy/Disabled'
//  '<S86>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/N Gain/Internal Parameters'
//  '<S87>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/P Copy/Disabled'
//  '<S88>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S89>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Reset Signal/Disabled'
//  '<S90>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Saturation/Passthrough'
//  '<S91>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Saturation Fdbk/Disabled'
//  '<S92>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Sum/Sum_PID'
//  '<S93>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Sum Fdbk/Disabled'
//  '<S94>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Tracking Mode/Disabled'
//  '<S95>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S96>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/postSat Signal/Forward_Path'
//  '<S97>'  : 'APF_conver/GUIDANCE & CONTROL/CONTROL /CONTROLLER/PID Controller1/preSat Signal/Forward_Path'
//  '<S98>'  : 'APF_conver/GUIDANCE & CONTROL/GUIDANCE /APF'
//  '<S99>'  : 'APF_conver/GUIDANCE & CONTROL/GUIDANCE /INITIAL ORIENTATION'
//  '<S100>' : 'APF_conver/GUIDANCE & CONTROL/GUIDANCE /APF/IAPF'
//  '<S101>' : 'APF_conver/GUIDANCE & CONTROL/GUIDANCE /INITIAL ORIENTATION/MATLAB Function'

#endif                                 // RTW_HEADER_APF_conver_h_

//
// File trailer for generated code.
//
// [EOF]
//
