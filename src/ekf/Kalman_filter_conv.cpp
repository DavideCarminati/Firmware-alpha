//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Kalman_filter_conv.cpp
//
// Code generated for Simulink model 'Kalman_filter_conv'.
//
// Model version                  : 1.14
// Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
// C/C++ source code generated on : Tue Mar  9 15:55:55 2021
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "Kalman_filter_conv.h"
#include "Kalman_filter_conv_private.h"

// Model step function
void Kalman_filter_conv_step(RT_MODEL_Kalman_filter_conv_T *const
  Kalman_filter_conv_M, ExtU_Kalman_filter_conv_T *Kalman_filter_conv_U,
  ExtY_Kalman_filter_conv_T *Kalman_filter_conv_Y)
{
  B_Kalman_filter_conv_T *Kalman_filter_conv_B = ((B_Kalman_filter_conv_T *)
    Kalman_filter_conv_M->blockIO);
  DW_Kalman_filter_conv_T *Kalman_filter_conv_DW = ((DW_Kalman_filter_conv_T *)
    Kalman_filter_conv_M->dwork);
  static const int8_T b[5] = { 0, 0, 0, 0, 1 };

  int32_T r1;
  int32_T r2;
  int32_T r3;
  int32_T rtemp;
  real_T rtb_psidot_enc;
  static const int8_T tmp[15] = { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1 };

  real_T rtb_F_tmp;
  real_T rtb_F_tmp_0;
  real_T rtb_F_tmp_1;
  int32_T rtb_H_tmp;
  int32_T K_tmp;
  int32_T K_tmp_0;

  // Gain: '<Root>/Gain3' incorporates:
  //   Inport: '<Root>/pos_l'
  //   Sum: '<Root>/Sum3'
  //   UnitDelay: '<Root>/Unit Delay2'

  Kalman_filter_conv_B->w_l = (Kalman_filter_conv_U->pos_l -
    Kalman_filter_conv_DW->UnitDelay2_DSTATE) * Kalman_filter_conv_P.Gain3_Gain;

  // Gain: '<Root>/Gain4' incorporates:
  //   Inport: '<Root>/pos_r'
  //   Sum: '<Root>/Sum2'
  //   UnitDelay: '<Root>/Unit Delay3'

  Kalman_filter_conv_B->w_r = (Kalman_filter_conv_U->pos_r -
    Kalman_filter_conv_DW->UnitDelay3_DSTATE) * Kalman_filter_conv_P.Gain4_Gain;

  // MATLAB Function: '<Root>/MATLAB Function3'
  rtb_psidot_enc = (Kalman_filter_conv_B->w_r - Kalman_filter_conv_B->w_l) *
    0.11621621621621621;

  // MATLAB Function: '<S1>/F' incorporates:
  //   MATLAB Function: '<S1>/f'
  //   SignalConversion: '<S5>/TmpSignal ConversionAt SFunction Inport2'
  //   UnitDelay: '<S1>/Unit Delay'

  Kalman_filter_conv_B->F[0] = 1.0;
  Kalman_filter_conv_B->F[5] = 0.0;
  Kalman_filter_conv_B->a21 = std::cos(Kalman_filter_conv_DW->UnitDelay_DSTATE[4]);
  rtb_F_tmp_0 = 0.2 * Kalman_filter_conv_B->a21;
  Kalman_filter_conv_B->F[10] = rtb_F_tmp_0;
  rtb_F_tmp = std::sin(Kalman_filter_conv_DW->UnitDelay_DSTATE[4]);
  Kalman_filter_conv_B->F[15] = 0.2 * -rtb_F_tmp;
  rtb_F_tmp_1 = Kalman_filter_conv_B->a21 *
    Kalman_filter_conv_DW->UnitDelay_DSTATE[3];
  Kalman_filter_conv_B->F[20] = (-Kalman_filter_conv_DW->UnitDelay_DSTATE[2] *
    rtb_F_tmp - rtb_F_tmp_1) * 0.2;
  Kalman_filter_conv_B->F[1] = 0.0;
  Kalman_filter_conv_B->F[6] = 1.0;
  Kalman_filter_conv_B->F[11] = 0.2 * rtb_F_tmp;
  Kalman_filter_conv_B->F[16] = rtb_F_tmp_0;
  Kalman_filter_conv_B->a21 = (Kalman_filter_conv_B->a21 *
    Kalman_filter_conv_DW->UnitDelay_DSTATE[2] - rtb_F_tmp *
    Kalman_filter_conv_DW->UnitDelay_DSTATE[3]) * 0.2;
  Kalman_filter_conv_B->F[21] = Kalman_filter_conv_B->a21;
  Kalman_filter_conv_B->F[2] = 0.0;
  Kalman_filter_conv_B->F[7] = 0.0;
  Kalman_filter_conv_B->F[12] = 1.0;
  Kalman_filter_conv_B->F[17] = rtb_psidot_enc * 0.2;
  Kalman_filter_conv_B->F[22] = 0.0;
  Kalman_filter_conv_B->F[3] = 0.0;
  Kalman_filter_conv_B->F[8] = 0.0;
  Kalman_filter_conv_B->F[13] = -rtb_psidot_enc * 0.2;
  Kalman_filter_conv_B->F[18] = 1.0;
  Kalman_filter_conv_B->F[23] = 0.0;
  for (r1 = 0; r1 < 5; r1++) {
    Kalman_filter_conv_B->F[4 + 5 * r1] = b[r1];
  }

  // MATLAB Function: '<S1>/H'
  for (r1 = 0; r1 < 15; r1++) {
    Kalman_filter_conv_B->H[r1] = tmp[r1];
  }

  // End of MATLAB Function: '<S1>/H'

  // MATLAB Function: '<Root>/MATLAB Function2' incorporates:
  //   Constant: '<Root>/cov_Vx_enc'
  //   Constant: '<Root>/cov_psi_enc'
  //   Constant: '<Root>/cov_psi_mag'

  memset(&Kalman_filter_conv_B->R[0], 0, 9U * sizeof(real_T));
  Kalman_filter_conv_B->R[0] = Kalman_filter_conv_P.cov_Vx_enc_Value;
  Kalman_filter_conv_B->R[4] = Kalman_filter_conv_P.cov_psi_enc_Value;
  Kalman_filter_conv_B->R[8] = Kalman_filter_conv_P.cov_psi_mag_Value;

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
  Kalman_filter_conv_DW->DiscreteTimeIntegrator_DSTATE +=
    Kalman_filter_conv_P.DiscreteTimeIntegrator_gainval * rtb_psidot_enc;

  // MATLAB Function: '<S1>/f' incorporates:
  //   Inport: '<Root>/ax'
  //   Inport: '<Root>/ay'
  //   MATLAB Function: '<S1>/F'
  //   SignalConversion: '<S5>/TmpSignal ConversionAt SFunction Inport2'
  //   UnitDelay: '<S1>/Unit Delay'

  Kalman_filter_conv_B->x[0] = Kalman_filter_conv_B->a21 +
    Kalman_filter_conv_DW->UnitDelay_DSTATE[0];
  Kalman_filter_conv_B->x[1] = (rtb_F_tmp *
    Kalman_filter_conv_DW->UnitDelay_DSTATE[2] + rtb_F_tmp_1) * 0.2 +
    Kalman_filter_conv_DW->UnitDelay_DSTATE[1];
  Kalman_filter_conv_B->x[2] = (rtb_psidot_enc *
    Kalman_filter_conv_DW->UnitDelay_DSTATE[3] + Kalman_filter_conv_U->ax) * 0.2
    + Kalman_filter_conv_DW->UnitDelay_DSTATE[2];
  Kalman_filter_conv_B->x[3] = (Kalman_filter_conv_U->ay - rtb_psidot_enc *
    Kalman_filter_conv_DW->UnitDelay_DSTATE[2]) * 0.2 +
    Kalman_filter_conv_DW->UnitDelay_DSTATE[3];
  Kalman_filter_conv_B->x[4] = rtb_psidot_enc * 0.2 +
    Kalman_filter_conv_DW->UnitDelay_DSTATE[4];

  // MATLAB Function: '<S1>/MATLAB Function'
  for (r1 = 0; r1 < 5; r1++) {
    for (r2 = 0; r2 < 5; r2++) {
      rtemp = r1 + 5 * r2;
      Kalman_filter_conv_B->rtb_F_m[rtemp] = 0.0;
      for (r3 = 0; r3 < 5; r3++) {
        Kalman_filter_conv_B->rtb_F_m[rtemp] += Kalman_filter_conv_B->F[5 * r3 +
          r1] * Kalman_filter_conv_DW->P_N_N[5 * r2 + r3];
      }
    }

    for (r2 = 0; r2 < 5; r2++) {
      rtemp = r1 + 5 * r2;
      Kalman_filter_conv_B->rtb_F_c[rtemp] = 0.0;
      for (r3 = 0; r3 < 5; r3++) {
        Kalman_filter_conv_B->rtb_F_c[rtemp] += Kalman_filter_conv_B->rtb_F_m[5 *
          r3 + r1] * Kalman_filter_conv_B->F[5 * r3 + r2];
      }
    }
  }

  // MATLAB Function: '<Root>/MATLAB Function1' incorporates:
  //   Constant: '<Root>/cov_Vx'
  //   Constant: '<Root>/cov_Vy'
  //   Constant: '<Root>/cov_X'
  //   Constant: '<Root>/cov_Y'
  //   Constant: '<Root>/cov_psi'

  Kalman_filter_conv_B->rtb_F_m[0] = Kalman_filter_conv_P.cov_X_Value;
  Kalman_filter_conv_B->rtb_F_m[5] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[10] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[15] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[20] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[1] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[6] = Kalman_filter_conv_P.cov_Y_Value;
  Kalman_filter_conv_B->rtb_F_m[11] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[16] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[21] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[2] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[7] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[12] = Kalman_filter_conv_P.cov_Vx_Value;
  Kalman_filter_conv_B->rtb_F_m[17] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[22] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[3] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[8] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[13] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[18] = Kalman_filter_conv_P.cov_Vy_Value;
  Kalman_filter_conv_B->rtb_F_m[23] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[4] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[9] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[14] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[19] = 0.0;
  Kalman_filter_conv_B->rtb_F_m[24] = Kalman_filter_conv_P.cov_psi_Value;

  // MATLAB Function: '<S1>/MATLAB Function'
  for (r1 = 0; r1 < 25; r1++) {
    Kalman_filter_conv_B->F[r1] = Kalman_filter_conv_B->rtb_F_c[r1] +
      Kalman_filter_conv_B->rtb_F_m[r1];
  }

  for (r1 = 0; r1 < 3; r1++) {
    for (r2 = 0; r2 < 5; r2++) {
      Kalman_filter_conv_B->K[r2 + 5 * r1] = Kalman_filter_conv_B->H[3 * r2 + r1];
    }
  }

  for (r1 = 0; r1 < 3; r1++) {
    for (r2 = 0; r2 < 5; r2++) {
      rtemp = r2 + 5 * r1;
      Kalman_filter_conv_B->y[rtemp] = 0.0;
      rtb_H_tmp = r1 + 3 * r2;
      Kalman_filter_conv_B->rtb_H_k[rtb_H_tmp] = 0.0;
      for (r3 = 0; r3 < 5; r3++) {
        Kalman_filter_conv_B->y[rtemp] += Kalman_filter_conv_B->F[5 * r3 + r2] *
          Kalman_filter_conv_B->K[5 * r1 + r3];
        Kalman_filter_conv_B->rtb_H_k[rtb_H_tmp] += static_cast<real_T>
          (Kalman_filter_conv_B->H[3 * r3 + r1]) * Kalman_filter_conv_B->F[5 *
          r2 + r3];
      }
    }

    for (r2 = 0; r2 < 3; r2++) {
      rtb_psidot_enc = 0.0;
      for (r3 = 0; r3 < 5; r3++) {
        rtb_psidot_enc += Kalman_filter_conv_B->rtb_H_k[3 * r3 + r1] *
          Kalman_filter_conv_B->K[5 * r2 + r3];
      }

      r3 = 3 * r2 + r1;
      Kalman_filter_conv_B->B[r3] = Kalman_filter_conv_B->R[r3] + rtb_psidot_enc;
    }
  }

  r1 = 0;
  r2 = 1;
  r3 = 2;
  rtb_psidot_enc = std::abs(Kalman_filter_conv_B->B[0]);
  Kalman_filter_conv_B->a21 = std::abs(Kalman_filter_conv_B->B[1]);
  if (Kalman_filter_conv_B->a21 > rtb_psidot_enc) {
    rtb_psidot_enc = Kalman_filter_conv_B->a21;
    r1 = 1;
    r2 = 0;
  }

  if (std::abs(Kalman_filter_conv_B->B[2]) > rtb_psidot_enc) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  Kalman_filter_conv_B->B[r2] /= Kalman_filter_conv_B->B[r1];
  Kalman_filter_conv_B->B[r3] /= Kalman_filter_conv_B->B[r1];
  Kalman_filter_conv_B->B[3 + r2] -= Kalman_filter_conv_B->B[3 + r1] *
    Kalman_filter_conv_B->B[r2];
  Kalman_filter_conv_B->B[3 + r3] -= Kalman_filter_conv_B->B[3 + r1] *
    Kalman_filter_conv_B->B[r3];
  Kalman_filter_conv_B->B[6 + r2] -= Kalman_filter_conv_B->B[6 + r1] *
    Kalman_filter_conv_B->B[r2];
  Kalman_filter_conv_B->B[6 + r3] -= Kalman_filter_conv_B->B[6 + r1] *
    Kalman_filter_conv_B->B[r3];
  if (std::abs(Kalman_filter_conv_B->B[3 + r3]) > std::abs
      (Kalman_filter_conv_B->B[3 + r2])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  Kalman_filter_conv_B->B[3 + r3] /= Kalman_filter_conv_B->B[3 + r2];
  Kalman_filter_conv_B->B[6 + r3] -= Kalman_filter_conv_B->B[3 + r3] *
    Kalman_filter_conv_B->B[6 + r2];
  for (rtemp = 0; rtemp < 5; rtemp++) {
    rtb_H_tmp = rtemp + 5 * r1;
    Kalman_filter_conv_B->K[rtb_H_tmp] = Kalman_filter_conv_B->y[rtemp] /
      Kalman_filter_conv_B->B[r1];
    K_tmp = rtemp + 5 * r2;
    Kalman_filter_conv_B->K[K_tmp] = Kalman_filter_conv_B->y[5 + rtemp] -
      Kalman_filter_conv_B->K[rtb_H_tmp] * Kalman_filter_conv_B->B[3 + r1];
    K_tmp_0 = rtemp + 5 * r3;
    Kalman_filter_conv_B->K[K_tmp_0] = Kalman_filter_conv_B->y[10 + rtemp] -
      Kalman_filter_conv_B->K[rtb_H_tmp] * Kalman_filter_conv_B->B[6 + r1];
    Kalman_filter_conv_B->K[K_tmp] /= Kalman_filter_conv_B->B[3 + r2];
    Kalman_filter_conv_B->K[K_tmp_0] -= Kalman_filter_conv_B->K[K_tmp] *
      Kalman_filter_conv_B->B[6 + r2];
    Kalman_filter_conv_B->K[K_tmp_0] /= Kalman_filter_conv_B->B[6 + r3];
    Kalman_filter_conv_B->K[K_tmp] -= Kalman_filter_conv_B->K[K_tmp_0] *
      Kalman_filter_conv_B->B[3 + r3];
    Kalman_filter_conv_B->K[rtb_H_tmp] -= Kalman_filter_conv_B->K[K_tmp_0] *
      Kalman_filter_conv_B->B[r3];
    Kalman_filter_conv_B->K[rtb_H_tmp] -= Kalman_filter_conv_B->K[K_tmp] *
      Kalman_filter_conv_B->B[r2];
  }

  for (r1 = 0; r1 < 25; r1++) {
    Kalman_filter_conv_B->b_I[r1] = 0;
  }

  for (r1 = 0; r1 < 5; r1++) {
    Kalman_filter_conv_B->b_I[r1 + 5 * r1] = 1;
  }

  for (r1 = 0; r1 < 5; r1++) {
    for (r2 = 0; r2 < 5; r2++) {
      r3 = 5 * r2 + r1;
      Kalman_filter_conv_B->rtb_F_c[r3] = static_cast<real_T>
        (Kalman_filter_conv_B->b_I[r3]) - ((static_cast<real_T>
        (Kalman_filter_conv_B->H[3 * r2 + 1]) * Kalman_filter_conv_B->K[r1 + 5]
        + static_cast<real_T>(Kalman_filter_conv_B->H[3 * r2]) *
        Kalman_filter_conv_B->K[r1]) + static_cast<real_T>
        (Kalman_filter_conv_B->H[3 * r2 + 2]) * Kalman_filter_conv_B->K[r1 + 10]);
    }

    for (r2 = 0; r2 < 5; r2++) {
      rtemp = r1 + 5 * r2;
      Kalman_filter_conv_DW->P_N_N[rtemp] = 0.0;
      for (r3 = 0; r3 < 5; r3++) {
        Kalman_filter_conv_DW->P_N_N[rtemp] += Kalman_filter_conv_B->rtb_F_c[5 *
          r3 + r1] * Kalman_filter_conv_B->F[5 * r2 + r3];
      }
    }
  }

  // SignalConversion: '<S7>/TmpSignal ConversionAt SFunction Inport1' incorporates:
  //   Inport: '<Root>/psi_mag'
  //   MATLAB Function: '<Root>/MATLAB Function3'
  //   MATLAB Function: '<S1>/MATLAB Function'

  Kalman_filter_conv_B->dv0[0] = (Kalman_filter_conv_B->w_r +
    Kalman_filter_conv_B->w_l) * 0.01075;
  Kalman_filter_conv_B->dv0[1] =
    Kalman_filter_conv_DW->DiscreteTimeIntegrator_DSTATE;
  Kalman_filter_conv_B->dv0[2] = Kalman_filter_conv_U->psi_mag;

  // MATLAB Function: '<S1>/MATLAB Function' incorporates:
  //   UnitDelay: '<S1>/Unit Delay'

  for (r1 = 0; r1 < 3; r1++) {
    Kalman_filter_conv_B->rtb_H_c[r1] = 0.0;
    for (r2 = 0; r2 < 5; r2++) {
      Kalman_filter_conv_B->rtb_H_c[r1] += static_cast<real_T>
        (Kalman_filter_conv_B->H[3 * r2 + r1]) * Kalman_filter_conv_B->x[r2];
    }

    Kalman_filter_conv_B->dv1[r1] = Kalman_filter_conv_B->dv0[r1] -
      Kalman_filter_conv_B->rtb_H_c[r1];
  }

  for (r1 = 0; r1 < 5; r1++) {
    Kalman_filter_conv_DW->UnitDelay_DSTATE[r1] = ((Kalman_filter_conv_B->K[r1 +
      5] * Kalman_filter_conv_B->dv1[1] + Kalman_filter_conv_B->K[r1] *
      Kalman_filter_conv_B->dv1[0]) + Kalman_filter_conv_B->K[r1 + 10] *
      Kalman_filter_conv_B->dv1[2]) + Kalman_filter_conv_B->x[r1];
  }

  // Outport: '<Root>/X' incorporates:
  //   UnitDelay: '<S1>/Unit Delay'

  Kalman_filter_conv_Y->X = Kalman_filter_conv_DW->UnitDelay_DSTATE[0];

  // Outport: '<Root>/Y' incorporates:
  //   UnitDelay: '<S1>/Unit Delay'

  Kalman_filter_conv_Y->Y = Kalman_filter_conv_DW->UnitDelay_DSTATE[1];

  // Outport: '<Root>/psi ' incorporates:
  //   UnitDelay: '<S1>/Unit Delay'

  Kalman_filter_conv_Y->psi = Kalman_filter_conv_DW->UnitDelay_DSTATE[4];

  // Outport: '<Root>/Vx ' incorporates:
  //   UnitDelay: '<S1>/Unit Delay'

  Kalman_filter_conv_Y->Vx = Kalman_filter_conv_DW->UnitDelay_DSTATE[2];

  // Outport: '<Root>/Vy ' incorporates:
  //   UnitDelay: '<S1>/Unit Delay'

  Kalman_filter_conv_Y->Vy = Kalman_filter_conv_DW->UnitDelay_DSTATE[3];

  // Update for UnitDelay: '<Root>/Unit Delay2' incorporates:
  //   Inport: '<Root>/pos_l'

  Kalman_filter_conv_DW->UnitDelay2_DSTATE = Kalman_filter_conv_U->pos_l;

  // Update for UnitDelay: '<Root>/Unit Delay3' incorporates:
  //   Inport: '<Root>/pos_r'

  Kalman_filter_conv_DW->UnitDelay3_DSTATE = Kalman_filter_conv_U->pos_r;
}

// Model initialize function
void Kalman_filter_conv_initialize(RT_MODEL_Kalman_filter_conv_T *const
  Kalman_filter_conv_M, ExtU_Kalman_filter_conv_T *Kalman_filter_conv_U,
  ExtY_Kalman_filter_conv_T *Kalman_filter_conv_Y)
{
  DW_Kalman_filter_conv_T *Kalman_filter_conv_DW = ((DW_Kalman_filter_conv_T *)
    Kalman_filter_conv_M->dwork);

  // Registration code

  // states (dwork)
  (void) memset((void *)Kalman_filter_conv_DW, 0,
                sizeof(DW_Kalman_filter_conv_T));

  // external inputs
  (void)memset(Kalman_filter_conv_U, 0, sizeof(ExtU_Kalman_filter_conv_T));

  // external outputs
  (void) memset((void *)Kalman_filter_conv_Y, 0,
                sizeof(ExtY_Kalman_filter_conv_T));

  {
    int32_T i;

    // InitializeConditions for UnitDelay: '<Root>/Unit Delay2'
    Kalman_filter_conv_DW->UnitDelay2_DSTATE =
      Kalman_filter_conv_P.UnitDelay2_InitialCondition;

    // InitializeConditions for UnitDelay: '<Root>/Unit Delay3'
    Kalman_filter_conv_DW->UnitDelay3_DSTATE =
      Kalman_filter_conv_P.UnitDelay3_InitialCondition;

    // InitializeConditions for UnitDelay: '<S1>/Unit Delay'
    for (i = 0; i < 5; i++) {
      Kalman_filter_conv_DW->UnitDelay_DSTATE[i] =
        Kalman_filter_conv_P.UnitDelay_InitialCondition[i];
    }

    // End of InitializeConditions for UnitDelay: '<S1>/Unit Delay'

    // InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' 
    Kalman_filter_conv_DW->DiscreteTimeIntegrator_DSTATE =
      Kalman_filter_conv_P.DiscreteTimeIntegrator_IC;

    // SystemInitialize for MATLAB Function: '<S1>/MATLAB Function'
    memset(&Kalman_filter_conv_DW->P_N_N[0], 0, 25U * sizeof(real_T));
    for (i = 0; i < 5; i++) {
      Kalman_filter_conv_DW->P_N_N[i + 5 * i] = 1.0;
    }

    // End of SystemInitialize for MATLAB Function: '<S1>/MATLAB Function'
  }
}

// Model terminate function
void Kalman_filter_conv_terminate(RT_MODEL_Kalman_filter_conv_T *const
  Kalman_filter_conv_M)
{
  // (no terminate code required)
  UNUSED_PARAMETER(Kalman_filter_conv_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
