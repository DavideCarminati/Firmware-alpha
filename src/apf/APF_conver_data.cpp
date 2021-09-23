//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: APF_conver_data.cpp
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
#include "APF_conver.h"
#include "APF_conver_private.h"

// Block parameters (default storage)
P_APF_conver_T APF_conver_P = {
  // Variable: Kd_Vx
  //  Referenced by: '<S33>/Derivative Gain'

  0.0,

  // Variable: Kd_psi
  //  Referenced by: '<S77>/Derivative Gain'

  0.0,

  // Variable: Ki_Vx
  //  Referenced by: '<S36>/Integral Gain'

  1.85, // 1.85

  // Variable: Ki_psi
  //  Referenced by: '<S80>/Integral Gain'

  0.1,

  // Variable: Kp_Vx
  //  Referenced by: '<S44>/Proportional Gain'

  2, //2

  // Variable: Kp_psi
  //  Referenced by: '<S88>/Proportional Gain'

  0.4, // 0.4

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S34>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S78>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_o
  //  Referenced by: '<S39>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_d
  //  Referenced by: '<S83>/Integrator'

  0.0,

  // Mask Parameter: PIDController_N
  //  Referenced by: '<S42>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController1_N
  //  Referenced by: '<S86>/Filter Coefficient'

  100.0,

  // Expression: 1
  //  Referenced by: '<Root>/X_goal'

  1,

  // Expression: 0
  //  Referenced by: '<Root>/Y_goal'

  0,

  // Expression: 4
  //  Referenced by: '<Root>/ox'

  4.0,

  // Expression: 4
  //  Referenced by: '<Root>/oy'

  4.0,

  // Computed Parameter: Integrator_gainval
  //  Referenced by: '<S39>/Integrator'

  0.1,

  // Computed Parameter: Filter_gainval
  //  Referenced by: '<S34>/Filter'

  0.1,

  // Expression: 1
  //  Referenced by: '<S4>/Saturation1'

  1.0,

  // Expression: -1
  //  Referenced by: '<S4>/Saturation1'

  -1.0,

  // Expression: 0
  //  Referenced by: '<S6>/Constant'

  0.0,

  // Expression: 180/pi
  //  Referenced by: '<S4>/Gain'

  57.295779513082323,

  // Expression: 180/pi
  //  Referenced by: '<S4>/Gain2'

  57.295779513082323,

  // Computed Parameter: Integrator_gainval_m
  //  Referenced by: '<S83>/Integrator'

  0.1,

  // Computed Parameter: Filter_gainval_o
  //  Referenced by: '<S78>/Filter'

  0.1,

  // Expression: 1/180
  //  Referenced by: '<S4>/1//180'

  0.0055555555555555558,

  // Expression: 0.5
  //  Referenced by: '<S4>/Saturation'

  0.5,

  // Expression: -0.5
  //  Referenced by: '<S4>/Saturation'

  -0.5,

  // Expression: 20000
  //  Referenced by: '<S5>/   '

  20000.0,

  // Expression: 20000
  //  Referenced by: '<S5>/Saturation1'

  20000.0,

  // Expression: -20000
  //  Referenced by: '<S5>/Saturation1'

  -20000.0,

  // Expression: 20000
  //  Referenced by: '<S5>/ '

  20000.0,

  // Expression: 20000
  //  Referenced by: '<S5>/Saturation'

  20000.0,

  // Expression: -20000
  //  Referenced by: '<S5>/Saturation'

  -20000.0
};

//
// File trailer for generated code.
//
// [EOF]
//
