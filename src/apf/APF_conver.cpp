//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: APF_conver.cpp
//
// Code generated for Simulink model 'APF_conver'.
//
// Model version                  : 1.94
// Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
// C/C++ source code generated on : Tue Feb 23 18:34:32 2021
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "APF_conver.h"
#include "APF_conver_private.h"

// Forward declaration for local functions
static real_T APF_conver_norm(const real_T x[2]);

// Function for MATLAB Function: '<S4>/IAPF'
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
  real_T q[2];
  real_T rho_goal;
  real_T F_attx;
  real_T F_atty;
  real_T F_repx;
  real_T F_repy;
  real_T obst;
  real_T rho;
  real_T M[4];
  int32_T r2;
  int32_T rtb_eos;
  boolean_T rtb_Compare;
  real_T rtb_V_ref;
  real_T rtb_psi_ref;
  real_T q_0[2];
  real_T q_1[2];
  real_T q_tmp;
  real_T q_tmp_0;
  boolean_T guard1 = false;

  // MATLAB Function: '<S4>/IAPF' incorporates:
  //   Constant: '<Root>/Constant'
  //   Constant: '<Root>/Constant1'
  //   Constant: '<Root>/Constant2'
  //   Constant: '<Root>/Constant3'
  //   Inport: '<Root>/X_est'
  //   Inport: '<Root>/Y_est'

  rtb_psi_ref = APF_conver_U->X_est - APF_conver_P.X_goal;
  q_1[0] = rtb_psi_ref;
  rtb_V_ref = APF_conver_U->Y_est - APF_conver_P.Y_goal;
  q_1[1] = rtb_V_ref;
  rho_goal = APF_conver_norm(q_1);
  if (rho_goal <= 2.0) {
    F_attx = (APF_conver_U->X_est - APF_conver_P.X_goal) * -0.15;
    F_atty = (APF_conver_U->Y_est - APF_conver_P.Y_goal) * -0.15;
  } else {
    F_attx = rtb_psi_ref * -0.15 * 2.0 / rho_goal;
    F_atty = rtb_V_ref * -0.15 * 2.0 / rho_goal;
  }

  F_repx = 0.0;
  F_repy = 0.0;
  obst = 0.0;
  q_tmp = APF_conver_U->X_est - APF_conver_P.ox;
  q_1[0] = q_tmp;
  q_tmp_0 = APF_conver_U->Y_est - APF_conver_P.oy;
  q_1[1] = q_tmp_0;
  if (10000.0 >= APF_conver_norm(q_1)) {
    q_1[0] = q_tmp;
    q_1[1] = q_tmp_0;
    rho = APF_conver_norm(q_1);
    if (rho <= 0.5) {
      q_1[0] = q_tmp;
      q_0[0] = q_tmp;
      q_1[1] = q_tmp_0;
      q_0[1] = q_tmp_0;
      obst = (1.0 / rho - 2.0) * 0.05 / (rho * rho);
      F_repx = obst * q_tmp / APF_conver_norm(q_1);
      F_repy = obst * q_tmp_0 / APF_conver_norm(q_0);
      obst = 1.0 / rho;
    }
  }

  q_1[0] = APF_conver_P.X_goal - APF_conver_P.ox;
  q_1[1] = APF_conver_P.Y_goal - APF_conver_P.oy;
  guard1 = false;
  if (APF_conver_norm(q_1) <= 0.3) {
    q_1[0] = rtb_psi_ref;
    q_1[1] = rtb_V_ref;
    if (APF_conver_norm(q_1) <= 0.3) {
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    F_attx += F_repx;
    F_atty += F_repy;
  }

  rtb_psi_ref = rt_atan2d_snf(F_atty, F_attx);
  rtb_V_ref = 0.6 / ((1.0 / rho_goal + obst) + 2.0);
  if (std::abs(rho_goal) <= 0.05) {
    rtb_V_ref = 0.0;
    rtb_psi_ref = 0.0;
    rtb_eos = 1;
  } else {
    rtb_eos = 0;
  }

  // End of MATLAB Function: '<S4>/IAPF'

  // RelationalOperator: '<S7>/Compare' incorporates:
  //   Constant: '<S7>/Constant'

  rtb_Compare = (rtb_eos == APF_conver_P.Constant_Value);

  // MATLAB Function: '<Root>/MATLAB Function' incorporates:
  //   Inport: '<Root>/Vx_est'
  //   Inport: '<Root>/Vy_est'
  //   Inport: '<Root>/psi_est'

  rho_goal = std::cos(APF_conver_U->psi_est);
  M[0] = rho_goal;
  F_attx = std::sin(APF_conver_U->psi_est);
  M[2] = -F_attx;
  M[1] = F_attx;
  M[3] = rho_goal;
  q[0] = APF_conver_U->Vx_est;
  q[1] = APF_conver_U->Vy_est;
  if (std::abs(F_attx) > std::abs(rho_goal)) {
    rtb_eos = 1;
    r2 = 0;
  } else {
    rtb_eos = 0;
    r2 = 1;
  }

  rho_goal = M[r2] / M[rtb_eos];
  F_attx = M[2 + rtb_eos];

  // Sum: '<S5>/Sum' incorporates:
  //   MATLAB Function: '<Root>/MATLAB Function'

  rho_goal = rtb_V_ref - (q[rtb_eos] - (q[r2] - q[rtb_eos] * rho_goal) / (M[2 +
    r2] - F_attx * rho_goal) * F_attx) / M[rtb_eos];

  // Gain: '<S42>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S34>/Filter'
  //   Gain: '<S33>/Derivative Gain'
  //   Sum: '<S34>/SumD'

  rtb_V_ref = (APF_conver_P.Kd_Vx * rho_goal - APF_conver_DW->Filter_DSTATE) *
    APF_conver_P.PIDController_N;

  // Sum: '<S48>/Sum' incorporates:
  //   DiscreteIntegrator: '<S39>/Integrator'
  //   Gain: '<S44>/Proportional Gain'

  F_repx = (APF_conver_P.Kp_Vx * rho_goal + APF_conver_DW->Integrator_DSTATE) +
    rtb_V_ref;

  // Saturate: '<S5>/Saturation1'
  if (F_repx > APF_conver_P.Saturation1_UpperSat) {
    F_repx = APF_conver_P.Saturation1_UpperSat;
  } else {
    if (F_repx < APF_conver_P.Saturation1_LowerSat) {
      F_repx = APF_conver_P.Saturation1_LowerSat;
    }
  }

  // End of Saturate: '<S5>/Saturation1'

  // Product: '<S5>/Product1'
  F_attx = F_repx * static_cast<real_T>(rtb_Compare);

  // Sum: '<S5>/Sum2' incorporates:
  //   Gain: '<S5>/Gain'
  //   Gain: '<S5>/Gain2'
  //   Inport: '<Root>/psi_est'

  rtb_psi_ref = APF_conver_P.Gain_Gain * rtb_psi_ref - APF_conver_P.Gain2_Gain *
    APF_conver_U->psi_est;

  // Gain: '<S86>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S78>/Filter'
  //   Gain: '<S77>/Derivative Gain'
  //   Sum: '<S78>/SumD'

  F_atty = (APF_conver_P.Kd_psi * rtb_psi_ref - APF_conver_DW->Filter_DSTATE_k) *
    APF_conver_P.PIDController1_N;

  // Gain: '<S5>/1//180' incorporates:
  //   DiscreteIntegrator: '<S83>/Integrator'
  //   Gain: '<S88>/Proportional Gain'
  //   Sum: '<S92>/Sum'

  F_repx = ((APF_conver_P.Kp_psi * rtb_psi_ref +
             APF_conver_DW->Integrator_DSTATE_i) + F_atty) *
    APF_conver_P.u180_Gain;

  // Saturate: '<S5>/Saturation'
  if (F_repx > APF_conver_P.Saturation_UpperSat) {
    F_repx = APF_conver_P.Saturation_UpperSat;
  } else {
    if (F_repx < APF_conver_P.Saturation_LowerSat) {
      F_repx = APF_conver_P.Saturation_LowerSat;
    }
  }

  // End of Saturate: '<S5>/Saturation'

  // Product: '<S5>/Product'
  APF_conver_Y->PWM_r = F_repx * static_cast<real_T>(rtb_Compare);

  // Gain: '<S6>/   ' incorporates:
  //   Sum: '<S6>/Sum1'

  APF_conver_Y->PWM_l = (F_attx - APF_conver_Y->PWM_r) * APF_conver_P._Gain;

  // Saturate: '<S6>/Saturation1'
  if (APF_conver_Y->PWM_l > APF_conver_P.Saturation1_UpperSat_f) {
    // Gain: '<S6>/   ' incorporates:
    //   Outport: '<Root>/PWM_l'

    APF_conver_Y->PWM_l = APF_conver_P.Saturation1_UpperSat_f;
  } else {
    if (APF_conver_Y->PWM_l < APF_conver_P.Saturation1_LowerSat_h) {
      // Gain: '<S6>/   ' incorporates:
      //   Outport: '<Root>/PWM_l'

      APF_conver_Y->PWM_l = APF_conver_P.Saturation1_LowerSat_h;
    }
  }

  // End of Saturate: '<S6>/Saturation1'

  // Gain: '<S6>/ ' incorporates:
  //   Sum: '<S6>/Sum'

  APF_conver_Y->PWM_r = (F_attx + APF_conver_Y->PWM_r) * APF_conver_P._Gain_b;

  // Saturate: '<S6>/Saturation'
  if (APF_conver_Y->PWM_r > APF_conver_P.Saturation_UpperSat_a) {
    // Outport: '<Root>/PWM_r'
    APF_conver_Y->PWM_r = APF_conver_P.Saturation_UpperSat_a;
  } else {
    if (APF_conver_Y->PWM_r < APF_conver_P.Saturation_LowerSat_e) {
      // Outport: '<Root>/PWM_r'
      APF_conver_Y->PWM_r = APF_conver_P.Saturation_LowerSat_e;
    }
  }

  // End of Saturate: '<S6>/Saturation'

  // Update for DiscreteIntegrator: '<S39>/Integrator' incorporates:
  //   Gain: '<S36>/Integral Gain'

  APF_conver_DW->Integrator_DSTATE += APF_conver_P.Ki_Vx * rho_goal *
    APF_conver_P.Integrator_gainval;

  // Update for DiscreteIntegrator: '<S34>/Filter'
  APF_conver_DW->Filter_DSTATE += APF_conver_P.Filter_gainval * rtb_V_ref;

  // Update for DiscreteIntegrator: '<S83>/Integrator' incorporates:
  //   Gain: '<S80>/Integral Gain'

  APF_conver_DW->Integrator_DSTATE_i += APF_conver_P.Ki_psi * rtb_psi_ref *
    APF_conver_P.Integrator_gainval_b;

  // Update for DiscreteIntegrator: '<S78>/Filter'
  APF_conver_DW->Filter_DSTATE_k += APF_conver_P.Filter_gainval_i * F_atty;
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
    APF_conver_P.PIDController_InitialConditio_k;

  // InitializeConditions for DiscreteIntegrator: '<S34>/Filter'
  APF_conver_DW->Filter_DSTATE = APF_conver_P.PIDController_InitialConditionF;

  // InitializeConditions for DiscreteIntegrator: '<S83>/Integrator'
  APF_conver_DW->Integrator_DSTATE_i =
    APF_conver_P.PIDController1_InitialConditi_l;

  // InitializeConditions for DiscreteIntegrator: '<S78>/Filter'
  APF_conver_DW->Filter_DSTATE_k = APF_conver_P.PIDController1_InitialCondition;
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
