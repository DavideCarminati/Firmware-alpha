//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: APF_conver.cpp
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
#include "global_vars.hpp"

// Forward declaration for local functions
static real_T APF_conver_norm(const real_T x[2]);

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

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2((real_T)u0_0, (real_T)u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

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
  real_T F_tot;
  real_T scale;
  real_T absxk;
  real_T t;
  int32_T rtb_enable_signal;
  real_T rtb_Vx_err;
  int32_T rtb_eos;
  boolean_T rtb_Compare;
  real_T q[2];
  real_T q_0[2];
  real_T q_tmp;
  boolean_T guard1 = false;

  // MATLAB Function: '<S98>/IAPF' incorporates:
  //   Constant: '<Root>/X_goal'
  //   Constant: '<Root>/Y_goal'
  //   Constant: '<Root>/ox'
  //   Constant: '<Root>/oy'
  //   Inport: '<Root>/X_est'
  //   Inport: '<Root>/Y_est'

  F_tot = APF_conver_U->X_est - APF_conver_P.X_goal_Value;
  q_0[0] = F_tot;
  scale = APF_conver_U->Y_est - APF_conver_P.Y_goal_Value;
  q_0[1] = scale;
  rtb_Vx_err = APF_conver_norm(q_0);
  if (rtb_Vx_err <= 2.0) {
    F_totx = (APF_conver_U->X_est - APF_conver_P.X_goal_Value) * -0.15;
    F_toty = (APF_conver_U->Y_est - APF_conver_P.Y_goal_Value) * -0.15;
  } else {
    F_totx = F_tot * -0.15 * 2.0 / rtb_Vx_err;
    F_toty = scale * -0.15 * 2.0 / rtb_Vx_err;
  }

  absxk = 0.0;
  F_repy = 0.0;
  obst = 0.0;
  t = APF_conver_U->X_est - APF_conver_P.ox_Value;
  q_0[0] = t;
  q_tmp = APF_conver_U->Y_est - APF_conver_P.oy_Value;
  q_0[1] = q_tmp;
  if (10000.0 >= APF_conver_norm(q_0)) {
    q_0[0] = t;
    q_0[1] = q_tmp;
    rho = APF_conver_norm(q_0);
    if (rho <= 0.7) {
      q_0[0] = t;
      q[0] = t;
      q_0[1] = q_tmp;
      q[1] = q_tmp;
      obst = (1.0 / rho - 1.4285714285714286) * 0.05 / (rho * rho);
      absxk = obst * t / APF_conver_norm(q_0);
      F_repy = obst * q_tmp / APF_conver_norm(q);
      obst = 1.0 / rho;
    }
  }

  q_0[0] = APF_conver_P.X_goal_Value - APF_conver_P.ox_Value;
  q_0[1] = APF_conver_P.Y_goal_Value - APF_conver_P.oy_Value;
  guard1 = false;
  if (APF_conver_norm(q_0) <= 0.3) {
    q_0[0] = F_tot;
    q_0[1] = scale;
    if (APF_conver_norm(q_0) <= 0.3) {
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    F_totx += absxk;
    F_toty += F_repy;
  }

  scale = 3.3121686421112381E-170;
  absxk = std::abs(F_totx);
  if (absxk > 3.3121686421112381E-170) {
    F_tot = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    F_tot = t * t;
  }

  absxk = std::abs(F_toty);
  if (absxk > scale) {
    t = scale / absxk;
    F_tot = F_tot * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    F_tot += t * t;
  }

  F_tot = scale * std::sqrt(F_tot);
  F_toty = rt_atan2d_snf(F_toty, F_totx);
  obst = 0.6 / ((0.2 / rtb_Vx_err + obst) + 2.0);

  debug_vel_ref= obst;
  debug_psi_ref=F_toty;


  if (std::abs(rtb_Vx_err) <= 0.2) {
    obst = 0.0;
    rtb_eos = 1;
  } else {
    rtb_eos = 0;
  }

  // printf("End of sm: %d \n", rtb_eos);
  // End of MATLAB Function: '<S98>/IAPF'

  // MATLAB Function: '<S99>/MATLAB Function' incorporates:
  //   Constant: '<Root>/X_goal'
  //   Constant: '<Root>/Y_goal'
  //   Inport: '<Root>/psi_est'

  scale = 0.0;
  rtb_enable_signal = 0;
  if (APF_conver_DW->en == 0.0) {
    if ((-3.1415926535897931 < APF_conver_U->psi_est) && (APF_conver_U->psi_est <=
         -1.5707963267948966)) {
      if ((APF_conver_P.X_goal_Value >= 0.0) && (APF_conver_P.Y_goal_Value >=
           0.0)) {
        APF_conver_DW->en = 0.0;
      }

      if ((APF_conver_P.X_goal_Value > 0.0) && (APF_conver_P.Y_goal_Value < 0.0))
      {
        APF_conver_DW->en = 0.0;
      }

      if ((APF_conver_P.X_goal_Value <= 0.0) && (APF_conver_P.Y_goal_Value <=
           0.0)) {
        rtb_enable_signal = 1;
        APF_conver_DW->en = 1.0;
      }

      if ((APF_conver_P.X_goal_Value < 0.0) && (APF_conver_P.Y_goal_Value > 0.0))
      {
        rtb_enable_signal = 1;
        APF_conver_DW->en = 1.0;
      }
    }

    if ((1.5707963267948966 < APF_conver_U->psi_est) && (APF_conver_U->psi_est <=
         3.1415926535897931)) {
      if ((APF_conver_P.X_goal_Value >= 0.0) && (APF_conver_P.Y_goal_Value >=
           0.0)) {
        rtb_enable_signal = 0;
        APF_conver_DW->en = 0.0;
      }

      if ((APF_conver_P.X_goal_Value > 0.0) && (APF_conver_P.Y_goal_Value < 0.0))
      {
        rtb_enable_signal = 0;
        APF_conver_DW->en = 0.0;
      }

      if ((APF_conver_P.X_goal_Value <= 0.0) && (APF_conver_P.Y_goal_Value <=
           0.0)) {
        rtb_enable_signal = 1;
        APF_conver_DW->en = 1.0;
      }

      if ((APF_conver_P.X_goal_Value < 0.0) && (APF_conver_P.Y_goal_Value > 0.0))
      {
        rtb_enable_signal = 1;
        APF_conver_DW->en = 1.0;
      }
    }

    if ((-1.5707963267948966 <= APF_conver_U->psi_est) && (APF_conver_U->psi_est
         <= 1.5707963267948966)) {
      if ((APF_conver_P.X_goal_Value >= 0.0) && (APF_conver_P.Y_goal_Value >=
           0.0)) {
        rtb_enable_signal = 1;
        APF_conver_DW->en = 1.0;
      }

      if ((APF_conver_P.X_goal_Value > 0.0) && (APF_conver_P.Y_goal_Value < 0.0))
      {
        rtb_enable_signal = 1;
        APF_conver_DW->en = 1.0;
      }

      if ((APF_conver_P.X_goal_Value <= 0.0) && (APF_conver_P.Y_goal_Value <=
           0.0)) {
        rtb_enable_signal = 0;
        scale = -3.1415926535897931;
        APF_conver_DW->en = 0.0;
      }

      if ((APF_conver_P.X_goal_Value < 0.0) && (APF_conver_P.Y_goal_Value > 0.0))
      {
        rtb_enable_signal = 0;
        scale = 3.1415926535897931;
        APF_conver_DW->en = 0.0;
      }
    }
  } else {
    rtb_enable_signal = 1;
  }

  // End of MATLAB Function: '<S99>/MATLAB Function'

  // Sum: '<S4>/Sum' incorporates:
  //   Inport: '<Root>/Vx_est'
  //   Product: '<S3>/Product'

  rtb_Vx_err = obst * static_cast<real_T>(rtb_enable_signal) -
    APF_conver_U->Vx_est;
   

  // Gain: '<S42>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S34>/Filter'
  //   Gain: '<S33>/Derivative Gain'
  //   Sum: '<S34>/SumD'

  obst = (APF_conver_P.Kd_Vx * rtb_Vx_err - APF_conver_DW->Filter_DSTATE) *
    APF_conver_P.PIDController_N;

  // RelationalOperator: '<S6>/Compare' incorporates:
  //   Constant: '<S6>/Constant'

  rtb_Compare = (rtb_eos == APF_conver_P.Constant_Value);

  // Sum: '<S48>/Sum' incorporates:
  //   DiscreteIntegrator: '<S39>/Integrator'
  //   Gain: '<S44>/Proportional Gain'

  F_tot = (APF_conver_P.Kp_Vx * rtb_Vx_err + APF_conver_DW->Integrator_DSTATE) +
    obst;

  // Saturate: '<S4>/Saturation1'
  if (F_tot > APF_conver_P.Saturation1_UpperSat) {
    F_tot = APF_conver_P.Saturation1_UpperSat;
  } else {
    if (F_tot < APF_conver_P.Saturation1_LowerSat) {
      F_tot = APF_conver_P.Saturation1_LowerSat;
    }
  }

  // End of Saturate: '<S4>/Saturation1'

  // Product: '<S4>/Product1'
  F_totx = F_tot * static_cast<real_T>(rtb_Compare);

  // MATLAB Function: '<S4>/MATLAB Function' incorporates:
  //   Gain: '<S4>/Gain'
  //   Gain: '<S4>/Gain2'
  //   Inport: '<Root>/psi_est'
  //   Product: '<S3>/Product1'
  //   Sum: '<S3>/Sum'

  F_toty = (F_toty * static_cast<real_T>(rtb_enable_signal) + scale) *
    APF_conver_P.Gain_Gain - APF_conver_P.Gain2_Gain * APF_conver_U->psi_est;
  if (std::abs(F_toty) > 180.0) {
    if (F_toty < 0.0) {
      F_tot = -1.0;
    } else if (F_toty > 0.0) {
      F_tot = 1.0;
    } else if (F_toty == 0.0) {
      F_tot = 0.0;
    } else {
      F_tot = (rtNaN);
    }

    F_toty -= 360.0 * F_tot;
  }

  // End of MATLAB Function: '<S4>/MATLAB Function'

  // Gain: '<S86>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S78>/Filter'
  //   Gain: '<S77>/Derivative Gain'
  //   Sum: '<S78>/SumD'

  scale = (APF_conver_P.Kd_psi * F_toty - APF_conver_DW->Filter_DSTATE_f) *
    APF_conver_P.PIDController1_N;

  // Gain: '<S4>/1//180' incorporates:
  //   DiscreteIntegrator: '<S83>/Integrator'
  //   Gain: '<S88>/Proportional Gain'
  //   Sum: '<S92>/Sum'

  F_tot = ((APF_conver_P.Kp_psi * F_toty + APF_conver_DW->Integrator_DSTATE_m) +
           scale) * APF_conver_P.u180_Gain;

  // Saturate: '<S4>/Saturation'
  if (F_tot > APF_conver_P.Saturation_UpperSat) {
    F_tot = APF_conver_P.Saturation_UpperSat;
  } else {
    if (F_tot < APF_conver_P.Saturation_LowerSat) {
      F_tot = APF_conver_P.Saturation_LowerSat;
    }
  }

  // End of Saturate: '<S4>/Saturation'

  // Product: '<S4>/Product'
  APF_conver_Y->PWM_r = F_tot * static_cast<real_T>(rtb_Compare);

  // Gain: '<S5>/   ' incorporates:
  //   Sum: '<S5>/Sum1'

  APF_conver_Y->PWM_l = (F_totx - APF_conver_Y->PWM_r) * APF_conver_P._Gain;

  // Saturate: '<S5>/Saturation1'
  if (APF_conver_Y->PWM_l > APF_conver_P.Saturation1_UpperSat_h) {
    // Gain: '<S5>/   ' incorporates:
    //   Outport: '<Root>/PWM_l'

    APF_conver_Y->PWM_l = APF_conver_P.Saturation1_UpperSat_h;
  } else {
    if (APF_conver_Y->PWM_l < APF_conver_P.Saturation1_LowerSat_k) {
      // Gain: '<S5>/   ' incorporates:
      //   Outport: '<Root>/PWM_l'

      APF_conver_Y->PWM_l = APF_conver_P.Saturation1_LowerSat_k;
    }
  }

  // End of Saturate: '<S5>/Saturation1'

  // Gain: '<S5>/ ' incorporates:
  //   Sum: '<S5>/Sum'

  APF_conver_Y->PWM_r = (F_totx + APF_conver_Y->PWM_r) * APF_conver_P._Gain_g;

  // Saturate: '<S5>/Saturation'
  if (APF_conver_Y->PWM_r > APF_conver_P.Saturation_UpperSat_p) {
    // Outport: '<Root>/PWM_r'
    APF_conver_Y->PWM_r = APF_conver_P.Saturation_UpperSat_p;
  } else {
    if (APF_conver_Y->PWM_r < APF_conver_P.Saturation_LowerSat_a) {
      // Outport: '<Root>/PWM_r'
      APF_conver_Y->PWM_r = APF_conver_P.Saturation_LowerSat_a;
    }
  }

  // End of Saturate: '<S5>/Saturation'

  // Update for DiscreteIntegrator: '<S39>/Integrator' incorporates:
  //   Gain: '<S36>/Integral Gain'

  APF_conver_DW->Integrator_DSTATE += APF_conver_P.Ki_Vx * rtb_Vx_err *
    APF_conver_P.Integrator_gainval;

  // Update for DiscreteIntegrator: '<S34>/Filter'
  APF_conver_DW->Filter_DSTATE += APF_conver_P.Filter_gainval * obst;

  // Update for DiscreteIntegrator: '<S83>/Integrator' incorporates:
  //   Gain: '<S80>/Integral Gain'

  APF_conver_DW->Integrator_DSTATE_m += APF_conver_P.Ki_psi * F_toty *
    APF_conver_P.Integrator_gainval_m;

  // Update for DiscreteIntegrator: '<S78>/Filter'
  APF_conver_DW->Filter_DSTATE_f += APF_conver_P.Filter_gainval_o * scale;
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

  // InitializeConditions for DiscreteIntegrator: '<S39>/Integrator'
  APF_conver_DW->Integrator_DSTATE =
    APF_conver_P.PIDController_InitialConditio_o;

  // InitializeConditions for DiscreteIntegrator: '<S34>/Filter'
  APF_conver_DW->Filter_DSTATE = APF_conver_P.PIDController_InitialConditionF;

  // InitializeConditions for DiscreteIntegrator: '<S83>/Integrator'
  APF_conver_DW->Integrator_DSTATE_m =
    APF_conver_P.PIDController1_InitialConditi_d;

  // InitializeConditions for DiscreteIntegrator: '<S78>/Filter'
  APF_conver_DW->Filter_DSTATE_f = APF_conver_P.PIDController1_InitialCondition;

  // SystemInitialize for MATLAB Function: '<S99>/MATLAB Function'
  APF_conver_DW->en = 0.0;
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
