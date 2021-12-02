//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: APF_SMC_data.cpp
//
// Code generated for Simulink model 'APF_SMC'.
//
// Model version                  : 1.113
// Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
// C/C++ source code generated on : Thu Dec  2 12:23:48 2021
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "APF_SMC/APF_SMC.h"
#include "APF_SMC/APF_SMC_private.h"

// Block parameters (default storage)
P_APF_SMC_T APF_SMC_P = {
  // Mask Parameter: DiscreteDerivative2_ICPrevScale
  //  Referenced by: '<S3>/UD'

  0.0,

  // Mask Parameter: DiscreteDerivative3_ICPrevScale
  //  Referenced by: '<S4>/UD'

  0.0,

  // Mask Parameter: DiscreteDerivative_ICPrevScaled
  //  Referenced by: '<S1>/UD'

  0.0,

  // Mask Parameter: DiscreteDerivative1_ICPrevScale
  //  Referenced by: '<S2>/UD'

  0.0,

  // Expression: 0.1
  //  Referenced by: '<Root>/Constant'

  0.1,

  // Computed Parameter: TSamp_WtEt
  //  Referenced by: '<S3>/TSamp'

  10.0,

  // Computed Parameter: TSamp_WtEt_e
  //  Referenced by: '<S4>/TSamp'

  10.0,

  // Expression: 180/pi
  //  Referenced by: '<Root>/Gain'

  57.295779513082323,

  // Expression: 180/pi
  //  Referenced by: '<Root>/Gain2'

  57.295779513082323,

  // Computed Parameter: TSamp_WtEt_d
  //  Referenced by: '<S1>/TSamp'

  10.0,

  // Computed Parameter: TSamp_WtEt_o
  //  Referenced by: '<S2>/TSamp'

  10.0,

  // Expression: 0
  //  Referenced by: '<S6>/Constant'

  0.0,

  // Computed Parameter: Constant_Value_n
  //  Referenced by: '<S7>/Constant'

  0
};

//
// File trailer for generated code.
//
// [EOF]
//
