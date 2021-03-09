//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: APF_conver.cpp
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
#include "global_vars.hpp"

#include "Kalman_filter_conv.h"

// Forward declaration for local functions
static real_T APF_conver_norm(const real_T x[2]);

int32_T rtb_eos = 0;

// Function for MATLAB Function: '<S98>/IAPF'
static real_T APF_conver_norm(const real_T x[2])
{
  real_T y;
  real_T scale;
  real_T absxk;
  real_T t;
  scale = 3.3121686421112381E-170;
  absxk = std::abs(x[0]);
  if (absxk > 3.3121686421112381E-170) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    y = t * t;
  }

  absxk = std::abs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * std::sqrt(y);
}

// real_T rt_atan2d_snf(real_T u0, real_T u1)
// {
//   real_T y;
//   int32_T u0_0;
//   int32_T u1_0;
//   if (rtIsNaN(u0) || rtIsNaN(u1)) {
//     y = (rtNaN);
//   } else if (rtIsInf(u0) && rtIsInf(u1)) {
//     if (u0 > 0.0) {
//       u0_0 = 1;
//     } else {
//       u0_0 = -1;
//     }

//     if (u1 > 0.0) {
//       u1_0 = 1;
//     } else {
//       u1_0 = -1;
//     }

//     y = atan2((real_T)u0_0, (real_T)u1_0);
//   } else if (u1 == 0.0) {
//     if (u0 > 0.0) {
//       y = RT_PI / 2.0;
//     } else if (u0 < 0.0) {
//       y = -(RT_PI / 2.0);
//     } else {
//       y = 0.0;
//     }
//   } else {
//     y = atan2(u0, u1);
//   }

//   return y;
// }

// Model step function
void APF_conver_step(RT_MODEL_APF_conver_T *const APF_conver_M,
                     ExtU_APF_conver_T *APF_conver_U, ExtY_APF_conver_T
                     *APF_conver_Y)
{
  DW_APF_conver_T *APF_conver_DW = ((DW_APF_conver_T *) APF_conver_M->dwork);
  real_T F_repy;
  real_T obst;
  real_T rho;
  real_T F_totx;
  real_T F_toty;
  int32_T enable_signal;
  real_T rtb_V_ref;
  real_T rtb_Vx_err;
  // int32_T rtb_eos;
  boolean_T rtb_Compare;
  real_T rtb_Product1_g;
  real_T rtb_psi_ref;
  real_T rtb_psiref;
  real_T q[2];
  real_T q_0[2];
  real_T q_tmp;
  boolean_T guard1 = false;

  // MATLAB Function: '<S98>/IAPF' incorporates:
  //   Constant: '<Root>/Constant'
  //   Constant: '<Root>/Constant1'
  //   Constant: '<Root>/Constant2'
  //   Constant: '<Root>/Constant3'
  //   Inport: '<Root>/X_est'
  //   Inport: '<Root>/Y_est'

  rtb_V_ref = APF_conver_U->X_est - APF_conver_P.X_goal;
  q_0[0] = rtb_V_ref;
  rtb_Product1_g = APF_conver_U->Y_est - APF_conver_P.Y_goal;
  q_0[1] = rtb_Product1_g;
  rtb_Vx_err = APF_conver_norm(q_0);
  if (rtb_Vx_err <= 2.0) {
    F_totx = (APF_conver_U->X_est - APF_conver_P.X_goal) * -0.15;
    F_toty = (APF_conver_U->Y_est - APF_conver_P.Y_goal) * -0.15;
  } else {
    F_totx = rtb_V_ref * -0.15 * 2.0 / rtb_Vx_err;
    F_toty = rtb_Product1_g * -0.15 * 2.0 / rtb_Vx_err;
  }

  rtb_psi_ref = 0.0;
  F_repy = 0.0;
  obst = 0.0;
  rtb_psiref = APF_conver_U->X_est - APF_conver_P.ox;
  q_0[0] = rtb_psiref;
  q_tmp = APF_conver_U->Y_est - APF_conver_P.oy;
  q_0[1] = q_tmp;
  if (10000.0 >= APF_conver_norm(q_0)) {
    q_0[0] = rtb_psiref;
    q_0[1] = q_tmp;
    rho = APF_conver_norm(q_0);
    if (rho <= 0.7) {
      q_0[0] = rtb_psiref;
      q[0] = rtb_psiref;
      q_0[1] = q_tmp;
      q[1] = q_tmp;
      obst = (1.0 / rho - 1.4285714285714286) / (rho * rho);
      rtb_psi_ref = obst * rtb_psiref / APF_conver_norm(q_0);
      F_repy = obst * q_tmp / APF_conver_norm(q);
      obst = 1.0 / rho;
    }
  }

  q_0[0] = APF_conver_P.X_goal - APF_conver_P.ox;
  q_0[1] = APF_conver_P.Y_goal - APF_conver_P.oy;
  guard1 = false;
  if (APF_conver_norm(q_0) <= 0.3) {
    q_0[0] = rtb_V_ref;
    q_0[1] = rtb_Product1_g;
    if (APF_conver_norm(q_0) <= 0.3) {
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    F_totx += rtb_psi_ref;
    F_toty += F_repy;
  }

  rtb_psi_ref = rt_atan2d_snf(F_toty, F_totx);
  rtb_V_ref = 0.6 / ((1.0 / rtb_Vx_err + obst) + 2.0);
  debug_psi_ref = rtb_psi_ref;
  debug_vel_ref = rtb_V_ref;
  if (std::abs(rtb_Vx_err) <= 0.10) {
    rtb_V_ref = 0.0;
    rtb_psi_ref = 0.0;
    rtb_eos = 1;
  } 
    
  

  // End of MATLAB Function: '<S98>/IAPF'

  // MATLAB Function: '<S99>/MATLAB Function' incorporates:
  //   Constant: '<Root>/Constant'
  //   Constant: '<Root>/Constant1'
  //   Inport: '<Root>/psi_est'

  enable_signal = 0;
  rtb_psiref = 0.0;
  if ((-3.1415926535897931 < APF_conver_U->psi_est) && (APF_conver_U->psi_est <=
       -1.5707963267948966)) {
    if ((APF_conver_P.X_goal > 0.0) && (APF_conver_P.Y_goal >= 0.0)) {
      rtb_psiref = -3.1415926535897931;
    }

    if ((APF_conver_P.X_goal > 0.0) && (APF_conver_P.Y_goal <= 0.0)) {
      rtb_psiref = -3.1415926535897931;
    }

    if ((APF_conver_P.X_goal < 0.0) && (APF_conver_P.Y_goal <= 0.0)) {
      enable_signal = 1;
      rtb_psiref = 0.0;
    }

    if ((APF_conver_P.X_goal < 0.0) && (APF_conver_P.Y_goal >= 0.0)) {
      enable_signal = 1;
      rtb_psiref = 0.0;
    }
  }

  if ((1.5707963267948966 < APF_conver_U->psi_est) && (APF_conver_U->psi_est <=
       3.1415926535897931)) {
    if ((APF_conver_P.X_goal > 0.0) && (APF_conver_P.Y_goal >= 0.0)) {
      enable_signal = 0;
      rtb_psiref = 0.0;
    }

    if ((APF_conver_P.X_goal > 0.0) && (APF_conver_P.Y_goal <= 0.0)) {
      enable_signal = 0;
      rtb_psiref = 0.0;
    }

    if ((APF_conver_P.X_goal < 0.0) && (APF_conver_P.Y_goal <= 0.0)) {
      enable_signal = 1;
      rtb_psiref = 0.0;
    }

    if ((APF_conver_P.X_goal < 0.0) && (APF_conver_P.Y_goal >= 0.0)) {
      enable_signal = 1;
      rtb_psiref = 0.0;
    }
  }

  if ((-1.5707963267948966 <= APF_conver_U->psi_est) && (APF_conver_U->psi_est <=
       1.5707963267948966)) {
    if ((APF_conver_P.X_goal > 0.0) && (APF_conver_P.Y_goal >= 0.0)) {
      enable_signal = 1;
      rtb_psiref = 0.0;
    }

    if ((APF_conver_P.X_goal > 0.0) && (APF_conver_P.Y_goal <= 0.0)) {
      enable_signal = 1;
      rtb_psiref = 0.0;
    }

    if ((APF_conver_P.X_goal < 0.0) && (APF_conver_P.Y_goal <= 0.0)) {
      enable_signal = 0;
      rtb_psiref = -3.1415926535897931;
    }

    if ((APF_conver_P.X_goal < 0.0) && (APF_conver_P.Y_goal >= 0.0)) {
      enable_signal = 0;
      rtb_psiref = 3.1415926535897931;
    }
  }

  if (enable_signal == 1) {
    rtb_psiref = 0.0;
  }

  // Sum: '<S4>/Sum' incorporates:
  //   Inport: '<Root>/Vx_est'
  //   MATLAB Function: '<S99>/MATLAB Function'
  //   Product: '<S97>/Product'

  rtb_Vx_err = rtb_V_ref * static_cast<real_T>(enable_signal) -
    APF_conver_U->Vx_est;

  // Gain: '<S41>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S33>/Filter'
  //   Gain: '<S32>/Derivative Gain'
  //   Sum: '<S33>/SumD'

  rtb_V_ref = (APF_conver_P.Kd_Vx * rtb_Vx_err - APF_conver_DW->Filter_DSTATE) *
    APF_conver_P.PIDController_N;

  // RelationalOperator: '<S6>/Compare' incorporates:
  //   Constant: '<S6>/Constant'
  //   MATLAB Function: '<S99>/MATLAB Function'
  //   Product: '<S97>/Product2'

  rtb_Compare = (rtb_eos * enable_signal == APF_conver_P.Constant_Value);

  // Sum: '<S47>/Sum' incorporates:
  //   DiscreteIntegrator: '<S38>/Integrator'
  //   Gain: '<S43>/Proportional Gain'

  obst = (APF_conver_P.Kp_Vx * rtb_Vx_err + APF_conver_DW->Integrator_DSTATE) +
    rtb_V_ref;

  // Saturate: '<S4>/Saturation1'
  if (obst > APF_conver_P.Saturation1_UpperSat) {
    obst = APF_conver_P.Saturation1_UpperSat;
  } else {
    if (obst < APF_conver_P.Saturation1_LowerSat) {
      obst = APF_conver_P.Saturation1_LowerSat;
    }
  }

  // End of Saturate: '<S4>/Saturation1'

  // Product: '<S4>/Product1'
  rtb_Product1_g = obst * static_cast<real_T>(rtb_Compare);

  // Sum: '<S4>/Sum2' incorporates:
  //   Gain: '<S4>/Gain'
  //   Gain: '<S4>/Gain2'
  //   Inport: '<Root>/psi_est'
  //   MATLAB Function: '<S99>/MATLAB Function'
  //   Product: '<S97>/Product1'
  //   Sum: '<S97>/Sum'

  rtb_psi_ref = (rtb_psi_ref * static_cast<real_T>(enable_signal) + rtb_psiref) *
    APF_conver_P.Gain_Gain - APF_conver_P.Gain2_Gain * APF_conver_U->psi_est;

  // Gain: '<S85>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S77>/Filter'
  //   Gain: '<S76>/Derivative Gain'
  //   Sum: '<S77>/SumD'

  rtb_psiref = (APF_conver_P.Kd_psi * rtb_psi_ref -
                APF_conver_DW->Filter_DSTATE_m) * APF_conver_P.PIDController1_N;

  // Gain: '<S4>/1//180' incorporates:
  //   DiscreteIntegrator: '<S82>/Integrator'
  //   Gain: '<S87>/Proportional Gain'
  //   Sum: '<S91>/Sum'

  obst = ((APF_conver_P.Kp_psi * rtb_psi_ref +
           APF_conver_DW->Integrator_DSTATE_e) + rtb_psiref) *
    APF_conver_P.u180_Gain;

  // Saturate: '<S4>/Saturation'
  if (obst > APF_conver_P.Saturation_UpperSat) {
    obst = APF_conver_P.Saturation_UpperSat;
  } else {
    if (obst < APF_conver_P.Saturation_LowerSat) {
      obst = APF_conver_P.Saturation_LowerSat;
    }
  }

  // End of Saturate: '<S4>/Saturation'

  // Product: '<S4>/Product'
  APF_conver_Y->PWM_r = obst * static_cast<real_T>(rtb_Compare);

  // Gain: '<S5>/   ' incorporates:
  //   Sum: '<S5>/Sum1'

  APF_conver_Y->PWM_l = (rtb_Product1_g - APF_conver_Y->PWM_r) *
    APF_conver_P._Gain;

  // Saturate: '<S5>/Saturation1'
  if (APF_conver_Y->PWM_l > APF_conver_P.Saturation1_UpperSat_m) {
    // Gain: '<S5>/   ' incorporates:
    //   Outport: '<Root>/PWM_l'

    APF_conver_Y->PWM_l = APF_conver_P.Saturation1_UpperSat_m;
  } else {
    if (APF_conver_Y->PWM_l < APF_conver_P.Saturation1_LowerSat_n) {
      // Gain: '<S5>/   ' incorporates:
      //   Outport: '<Root>/PWM_l'

      APF_conver_Y->PWM_l = APF_conver_P.Saturation1_LowerSat_n;
    }
  }

  // End of Saturate: '<S5>/Saturation1'

  // Gain: '<S5>/ ' incorporates:
  //   Sum: '<S5>/Sum'

  APF_conver_Y->PWM_r = (rtb_Product1_g + APF_conver_Y->PWM_r) *
    APF_conver_P._Gain_p;

  // Saturate: '<S5>/Saturation'
  if (APF_conver_Y->PWM_r > APF_conver_P.Saturation_UpperSat_i) {
    // Outport: '<Root>/PWM_r'
    APF_conver_Y->PWM_r = APF_conver_P.Saturation_UpperSat_i;
  } else {
    if (APF_conver_Y->PWM_r < APF_conver_P.Saturation_LowerSat_f) {
      // Outport: '<Root>/PWM_r'
      APF_conver_Y->PWM_r = APF_conver_P.Saturation_LowerSat_f;
    }
  }

  // End of Saturate: '<S5>/Saturation'

  // Update for DiscreteIntegrator: '<S38>/Integrator' incorporates:
  //   Gain: '<S35>/Integral Gain'

  APF_conver_DW->Integrator_DSTATE += APF_conver_P.Ki_Vx * rtb_Vx_err *
    APF_conver_P.Integrator_gainval;

  // Update for DiscreteIntegrator: '<S33>/Filter'
  APF_conver_DW->Filter_DSTATE += APF_conver_P.Filter_gainval * rtb_V_ref;

  // Update for DiscreteIntegrator: '<S82>/Integrator' incorporates:
  //   Gain: '<S79>/Integral Gain'

  APF_conver_DW->Integrator_DSTATE_e += APF_conver_P.Ki_psi * rtb_psi_ref *
    APF_conver_P.Integrator_gainval_b;

  // Update for DiscreteIntegrator: '<S77>/Filter'
  APF_conver_DW->Filter_DSTATE_m += APF_conver_P.Filter_gainval_j * rtb_psiref;
}

// Model initialize function
void APF_conver_initialize(RT_MODEL_APF_conver_T *const APF_conver_M,
  ExtU_APF_conver_T *APF_conver_U, ExtY_APF_conver_T *APF_conver_Y)
{
  DW_APF_conver_T *APF_conver_DW = ((DW_APF_conver_T *) APF_conver_M->dwork);

  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // states (dwork)
  (void) memset((void *)APF_conver_DW, 0,
                sizeof(DW_APF_conver_T));

  // external inputs
  (void)memset(APF_conver_U, 0, sizeof(ExtU_APF_conver_T));

  // external outputs
  (void) memset((void *)APF_conver_Y, 0,
                sizeof(ExtY_APF_conver_T));

  // InitializeConditions for DiscreteIntegrator: '<S38>/Integrator'
  APF_conver_DW->Integrator_DSTATE =
    APF_conver_P.PIDController_InitialConditio_d;

  // InitializeConditions for DiscreteIntegrator: '<S33>/Filter'
  APF_conver_DW->Filter_DSTATE = APF_conver_P.PIDController_InitialConditionF;

  // InitializeConditions for DiscreteIntegrator: '<S82>/Integrator'
  APF_conver_DW->Integrator_DSTATE_e =
    APF_conver_P.PIDController1_InitialConditi_k;

  // InitializeConditions for DiscreteIntegrator: '<S77>/Filter'
  APF_conver_DW->Filter_DSTATE_m = APF_conver_P.PIDController1_InitialCondition;
}

// Model terminate function
void APF_conver_terminate(RT_MODEL_APF_conver_T *const APF_conver_M)
{
  // (no terminate code required)
  UNUSED_PARAMETER(APF_conver_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
