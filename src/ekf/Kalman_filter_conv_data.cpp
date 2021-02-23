//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Kalman_filter_conv_data.cpp
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
#include "Kalman_filter_conv.h"
#include "Kalman_filter_conv_private.h"

// Constant parameters (default storage)
const ConstP_Kalman_filter_conv_T Kalman_filter_conv_ConstP = {
  // Expression: Q
  //  Referenced by: '<S2>/Constant'

  { 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 86700.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0066, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0086 },

  // Expression: x0
  //  Referenced by: '<S2>/Unit Delay'

  { 0.0, 0.0, -0.010074313846620008, 0.0, 0.0 },

  // Expression: R
  //  Referenced by: '<S2>/Constant1'

  { 86700.0, 0.0, 0.0, 0.0, 0.0137, 0.0, 0.0, 0.0, 0.0147 }
};

//
// File trailer for generated code.
//
// [EOF]
//
