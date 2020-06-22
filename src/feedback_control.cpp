//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: feedback_control.cpp
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
#include "feedback_control.h"
#include "feedback_control_private.h"

// Model step function
void feedback_control_step(RT_MODEL_feedback_control_T *const feedback_control_M,
  ExtU_feedback_control_T *feedback_control_U, ExtY_feedback_control_T
  *feedback_control_Y)
{
  DW_feedback_control_T *feedback_control_DW = ((DW_feedback_control_T *)
    feedback_control_M->dwork);
  real32_T psi_error, v_error, v_cmd, psi_cmd;
  real32_T rtb_TSamp;

  // Sum: '<Root>/Sum' incorporates:
  //   Inport: '<Root>/est'
  //   Inport: '<Root>/ref'

  psi_error = feedback_control_U->psi_ref - feedback_control_U->psi_est;
  v_error = feedback_control_U->v_ref - feedback_control_U->v_est;

  psi_cmd = psi_error*10;
  v_cmd = v_error*1;

  psi_cmd = psi_error/180; // gradi
  v_cmd = v_cmd/1; // m/s

  if(psi_cmd > 1)     psi_cmd = 1;
  if(psi_cmd < -1)    psi_cmd = -1;
  if(v_cmd > 1)       v_cmd = 1;
  if(v_cmd < -1)      v_cmd = -1;

  feedback_control_Y->pwm_left = 20000*(v_cmd - psi_cmd);
  feedback_control_Y->pwm_right = 20000*(v_cmd + psi_cmd);


  // SampleTimeMath: '<S26>/TSamp' incorporates:
  //   Gain: '<S25>/Derivative Gain'
  //
  //  About '<S26>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )

  // rtb_TSamp = 0.2F * rtb_error * 20.0F;

  // // Outport: '<Root>/u' incorporates:
  // //   Delay: '<S26>/UD'
  // //   DiscreteIntegrator: '<S31>/Integrator'
  // //   Gain: '<S36>/Proportional Gain'
  // //   Sum: '<S26>/Diff'
  // //   Sum: '<S40>/Sum'

  // feedback_control_Y->u = (0.8F * rtb_error +
  //   feedback_control_DW->Integrator_DSTATE) + (rtb_TSamp -
  //   feedback_control_DW->UD_DSTATE);

  // feedback_control_Y->u = feedback_control_U->reference;

  // // Update for DiscreteIntegrator: '<S31>/Integrator' incorporates:
  // //   Gain: '<S28>/Integral Gain'

  // feedback_control_DW->Integrator_DSTATE += 7.0F * rtb_error * 0.05F;

  // // Update for Delay: '<S26>/UD'
  // feedback_control_DW->UD_DSTATE = rtb_TSamp;
}

// Model initialize function
void feedback_control_initialize(RT_MODEL_feedback_control_T *const
  feedback_control_M, ExtU_feedback_control_T *feedback_control_U,
  ExtY_feedback_control_T *feedback_control_Y)
{
  DW_feedback_control_T *feedback_control_DW = ((DW_feedback_control_T *)
    feedback_control_M->dwork);

  // Registration code

  // states (dwork)
  (void) memset((void *)feedback_control_DW, 0,
                sizeof(DW_feedback_control_T));

  // external inputs
  (void)memset(feedback_control_U, 0, sizeof(ExtU_feedback_control_T));

  // external outputs
  // feedback_control_Y->u = 0.0F;
}

// Model terminate function
void feedback_control_terminate(RT_MODEL_feedback_control_T *const
  feedback_control_M)
{
  // (no terminate code required)
  UNUSED_PARAMETER(feedback_control_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
