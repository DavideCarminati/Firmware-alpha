//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: APF_conver_data.cpp
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
#include "APF_conver.h"
#include "APF_conver_private.h"

// Block parameters (default storage)
P_APF_conver_T APF_conver_P = {
  // Variable: Kd_Vx
  //  Referenced by: '<S32>/Derivative Gain'

  0.0,

  // Variable: Kd_psi
  //  Referenced by: '<S76>/Derivative Gain'

  0.0,

  // Variable: Ki_Vx
  //  Referenced by: '<S35>/Integral Gain'

  1.85,

  // Variable: Ki_psi
  //  Referenced by: '<S79>/Integral Gain'

  0.0,

  // Variable: Kp_Vx
  //  Referenced by: '<S43>/Proportional Gain'

  2.0,

  // Variable: Kp_psi
  //  Referenced by: '<S87>/Proportional Gain'

  1,

  // Variable: X_goal
  //  Referenced by: '<Root>/Constant'

  1.0,

  // Variable: Y_goal
  //  Referenced by: '<Root>/Constant1'

  0.0,

  // Variable: ox
  //  Referenced by: '<Root>/Constant2'

  5.0,

  // Variable: oy
  //  Referenced by: '<Root>/Constant3'

  5.0,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S33>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S77>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_d
  //  Referenced by: '<S38>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_k
  //  Referenced by: '<S82>/Integrator'

  0.0,

  // Mask Parameter: PIDController_N
  //  Referenced by: '<S41>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController1_N
  //  Referenced by: '<S85>/Filter Coefficient'

  100.0,

  // Computed Parameter: Integrator_gainval
  //  Referenced by: '<S38>/Integrator'

  0.1,

  // Computed Parameter: Filter_gainval
  //  Referenced by: '<S33>/Filter'

  0.1,

  // Expression: 1
  //  Referenced by: '<S4>/Saturation1'

  0.8,

  // Expression: -1
  //  Referenced by: '<S4>/Saturation1'

  -0.8,

  // Expression: 0
  //  Referenced by: '<S6>/Constant'

  0.0,

  // Expression: 180/pi
  //  Referenced by: '<S4>/Gain'

  57.295779513082323,

  // Expression: 180/pi
  //  Referenced by: '<S4>/Gain2'

  57.295779513082323,

  // Computed Parameter: Integrator_gainval_b
  //  Referenced by: '<S82>/Integrator'

  0.1,

  // Computed Parameter: Filter_gainval_j
  //  Referenced by: '<S77>/Filter'

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
