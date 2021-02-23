//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Kalman_filter_conv.cpp
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

// Model step function
void Kalman_filter_conv_step(RT_MODEL_Kalman_filter_conv_T *const
  Kalman_filter_conv_M, ExtU_Kalman_filter_conv_T *Kalman_filter_conv_U,
  ExtY_Kalman_filter_conv_T *Kalman_filter_conv_Y)
{
  DW_Kalman_filter_conv_T *Kalman_filter_conv_DW = ((DW_Kalman_filter_conv_T *)
    Kalman_filter_conv_M->dwork);
  real_T P_N_1_N[25];
  real_T K[15];
  real_T y[15];
  real_T B[9];
  int32_T r1;
  int32_T r2;
  int32_T r3;
  real_T maxval;
  real_T a21;
  int32_T rtemp;
  int8_T b_I[25];
  real_T rtb_Gain2;
  real_T rtb_w_l;
  real_T rtb_w_r;
  real_T rtb_x[5];
  real_T rtb_F[25];
  int8_T rtb_H[15];
  static const real_T tmp[25] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.2, 0.0, 0.0, 1.0, 0.0, 0.0, 0.2, 0.0, 0.0,
    1.0 };

  static const int8_T tmp_0[15] = { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1
  };

  real_T rtb_F_0[25];
  real_T rtb_H_0[15];
  real_T rtb_Gain2_0[3];
  real_T rtb_H_1[3];
  real_T rtb_Gain2_1[3];
  int32_T rtb_H_tmp;
  int32_T K_tmp;
  int32_T K_tmp_0;

  // Gain: '<S1>/Gain2' incorporates:
  //   Inport: '<Root>/psi'

  rtb_Gain2 = 0.017453292519943295 * Kalman_filter_conv_U->psi;

  // Gain: '<S1>/Gain' incorporates:
  //   Inport: '<Root>/pos_l'
  //   Sum: '<S1>/Sum1'
  //   UnitDelay: '<S1>/Unit Delay'

  rtb_w_l = (Kalman_filter_conv_U->pos_l -
             Kalman_filter_conv_DW->UnitDelay_DSTATE) * 0.3490658503988659;

  // Gain: '<S1>/Gain1' incorporates:
  //   Inport: '<Root>/pos_r'
  //   Sum: '<S1>/Sum'
  //   UnitDelay: '<S1>/Unit Delay1'

  rtb_w_r = (Kalman_filter_conv_U->pos_r -
             Kalman_filter_conv_DW->UnitDelay1_DSTATE) * 0.3490658503988659;

  // MATLAB Function: '<S2>/F'
  memcpy(&rtb_F[0], &tmp[0], 25U * sizeof(real_T));

  // MATLAB Function: '<S2>/H'
  for (r1 = 0; r1 < 15; r1++) {
    rtb_H[r1] = tmp_0[r1];
  }

  // End of MATLAB Function: '<S2>/H'

  // MATLAB Function: '<S2>/f' incorporates:
  //   UnitDelay: '<S2>/Unit Delay'
  //   UnitDelay: '<S2>/Unit Delay1'

  rtb_x[0] = Kalman_filter_conv_DW->UnitDelay_DSTATE_n[3] * 0.2 +
    Kalman_filter_conv_DW->UnitDelay_DSTATE_n[0];
  rtb_x[1] = Kalman_filter_conv_DW->UnitDelay_DSTATE_n[4] * 0.2 +
    Kalman_filter_conv_DW->UnitDelay_DSTATE_n[1];
  rtb_x[2] = Kalman_filter_conv_DW->UnitDelay1_DSTATE_e[1] * 0.2 +
    Kalman_filter_conv_DW->UnitDelay_DSTATE_n[2];
  rtb_x[3] = Kalman_filter_conv_DW->UnitDelay1_DSTATE_e[0] * 0.2 +
    Kalman_filter_conv_DW->UnitDelay_DSTATE_n[3];
  rtb_x[4] = Kalman_filter_conv_DW->UnitDelay1_DSTATE_e[1] * 0.2 +
    Kalman_filter_conv_DW->UnitDelay_DSTATE_n[4];

  // MATLAB Function: '<S2>/MATLAB Function' incorporates:
  //   Constant: '<S2>/Constant'
  //   Constant: '<S2>/Constant1'

  for (r1 = 0; r1 < 5; r1++) {
    for (r2 = 0; r2 < 5; r2++) {
      rtemp = r1 + 5 * r2;
      rtb_F_0[rtemp] = 0.0;
      for (r3 = 0; r3 < 5; r3++) {
        rtb_F_0[rtemp] += rtb_F[5 * r3 + r1] * Kalman_filter_conv_DW->P_N_N[5 *
          r2 + r3];
      }
    }

    for (r2 = 0; r2 < 5; r2++) {
      maxval = 0.0;
      for (r3 = 0; r3 < 5; r3++) {
        maxval += rtb_F_0[5 * r3 + r1] * rtb_F[5 * r3 + r2];
      }

      r3 = 5 * r2 + r1;
      P_N_1_N[r3] = Kalman_filter_conv_ConstP.Constant_Value[r3] + maxval;
    }
  }

  for (r1 = 0; r1 < 3; r1++) {
    for (r2 = 0; r2 < 5; r2++) {
      K[r2 + 5 * r1] = rtb_H[3 * r2 + r1];
    }
  }

  for (r1 = 0; r1 < 3; r1++) {
    for (r2 = 0; r2 < 5; r2++) {
      rtemp = r2 + 5 * r1;
      y[rtemp] = 0.0;
      rtb_H_tmp = r1 + 3 * r2;
      rtb_H_0[rtb_H_tmp] = 0.0;
      for (r3 = 0; r3 < 5; r3++) {
        y[rtemp] += P_N_1_N[5 * r3 + r2] * K[5 * r1 + r3];
        rtb_H_0[rtb_H_tmp] += static_cast<real_T>(rtb_H[3 * r3 + r1]) * P_N_1_N
          [5 * r2 + r3];
      }
    }

    for (r2 = 0; r2 < 3; r2++) {
      maxval = 0.0;
      for (r3 = 0; r3 < 5; r3++) {
        maxval += rtb_H_0[3 * r3 + r1] * K[5 * r2 + r3];
      }

      r3 = 3 * r2 + r1;
      B[r3] = Kalman_filter_conv_ConstP.Constant1_Value[r3] + maxval;
    }
  }

  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = std::abs(B[0]);
  a21 = std::abs(B[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if (std::abs(B[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  B[r2] /= B[r1];
  B[r3] /= B[r1];
  B[3 + r2] -= B[3 + r1] * B[r2];
  B[3 + r3] -= B[3 + r1] * B[r3];
  B[6 + r2] -= B[6 + r1] * B[r2];
  B[6 + r3] -= B[6 + r1] * B[r3];
  if (std::abs(B[3 + r3]) > std::abs(B[3 + r2])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  B[3 + r3] /= B[3 + r2];
  B[6 + r3] -= B[3 + r3] * B[6 + r2];
  for (rtemp = 0; rtemp < 5; rtemp++) {
    rtb_H_tmp = rtemp + 5 * r1;
    K[rtb_H_tmp] = y[rtemp] / B[r1];
    K_tmp = rtemp + 5 * r2;
    K[K_tmp] = y[5 + rtemp] - K[rtb_H_tmp] * B[3 + r1];
    K_tmp_0 = rtemp + 5 * r3;
    K[K_tmp_0] = y[10 + rtemp] - K[rtb_H_tmp] * B[6 + r1];
    K[K_tmp] /= B[3 + r2];
    K[K_tmp_0] -= K[K_tmp] * B[6 + r2];
    K[K_tmp_0] /= B[6 + r3];
    K[K_tmp] -= K[K_tmp_0] * B[3 + r3];
    K[rtb_H_tmp] -= K[K_tmp_0] * B[r3];
    K[rtb_H_tmp] -= K[K_tmp] * B[r2];
  }

  for (r1 = 0; r1 < 25; r1++) {
    b_I[r1] = 0;
  }

  for (r1 = 0; r1 < 5; r1++) {
    b_I[r1 + 5 * r1] = 1;
  }

  for (r1 = 0; r1 < 5; r1++) {
    for (r2 = 0; r2 < 5; r2++) {
      r3 = 5 * r2 + r1;
      rtb_F[r3] = static_cast<real_T>(b_I[r3]) - ((static_cast<real_T>(rtb_H[3 *
        r2 + 1]) * K[r1 + 5] + static_cast<real_T>(rtb_H[3 * r2]) * K[r1]) +
        static_cast<real_T>(rtb_H[3 * r2 + 2]) * K[r1 + 10]);
    }

    for (r2 = 0; r2 < 5; r2++) {
      rtemp = r1 + 5 * r2;
      Kalman_filter_conv_DW->P_N_N[rtemp] = 0.0;
      for (r3 = 0; r3 < 5; r3++) {
        Kalman_filter_conv_DW->P_N_N[rtemp] += rtb_F[5 * r3 + r1] * P_N_1_N[5 *
          r2 + r3];
      }
    }
  }

  // SignalConversion: '<S7>/TmpSignal ConversionAt SFunction Inport1' incorporates:
  //   MATLAB Function: '<S2>/MATLAB Function'

  rtb_Gain2_0[0] = rtb_Gain2;

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function'

  a21 = (rtb_w_r + rtb_w_l) * 0.01075;
  maxval = std::cos(rtb_Gain2);

  // SignalConversion: '<S7>/TmpSignal ConversionAt SFunction Inport1' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function1'
  //   MATLAB Function: '<S2>/MATLAB Function'

  rtb_Gain2_0[1] = a21 * maxval;

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function'

  rtb_Gain2 = std::sin(rtb_Gain2);

  // SignalConversion: '<S7>/TmpSignal ConversionAt SFunction Inport1' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function1'
  //   MATLAB Function: '<S2>/MATLAB Function'

  rtb_Gain2_0[2] = a21 * rtb_Gain2;

  // MATLAB Function: '<S2>/MATLAB Function' incorporates:
  //   UnitDelay: '<S2>/Unit Delay'

  for (r1 = 0; r1 < 3; r1++) {
    rtb_H_1[r1] = 0.0;
    for (r2 = 0; r2 < 5; r2++) {
      rtb_H_1[r1] += static_cast<real_T>(rtb_H[3 * r2 + r1]) * rtb_x[r2];
    }

    rtb_Gain2_1[r1] = rtb_Gain2_0[r1] - rtb_H_1[r1];
  }

  for (r1 = 0; r1 < 5; r1++) {
    Kalman_filter_conv_DW->UnitDelay_DSTATE_n[r1] = ((K[r1 + 5] * rtb_Gain2_1[1]
      + K[r1] * rtb_Gain2_1[0]) + K[r1 + 10] * rtb_Gain2_1[2]) + rtb_x[r1];
  }

  // Outport: '<Root>/X_est' incorporates:
  //   UnitDelay: '<S2>/Unit Delay'

  Kalman_filter_conv_Y->X_est = Kalman_filter_conv_DW->UnitDelay_DSTATE_n[0];

  // Outport: '<Root>/Y_est' incorporates:
  //   UnitDelay: '<S2>/Unit Delay'

  Kalman_filter_conv_Y->Y_est = Kalman_filter_conv_DW->UnitDelay_DSTATE_n[1];

  // Outport: '<Root>/Vx_est' incorporates:
  //   UnitDelay: '<S2>/Unit Delay'

  Kalman_filter_conv_Y->Vx_est = Kalman_filter_conv_DW->UnitDelay_DSTATE_n[3];

  // Outport: '<Root>/Vy_est' incorporates:
  //   UnitDelay: '<S2>/Unit Delay'

  Kalman_filter_conv_Y->Vy_est = Kalman_filter_conv_DW->UnitDelay_DSTATE_n[4];

  // Outport: '<Root>/psi_est' incorporates:
  //   Gain: '<S1>/Gain3'
  //   UnitDelay: '<S2>/Unit Delay'

  Kalman_filter_conv_Y->psi_est = 57.295779513082323 *
    Kalman_filter_conv_DW->UnitDelay_DSTATE_n[2];

  // Update for UnitDelay: '<S1>/Unit Delay' incorporates:
  //   Inport: '<Root>/pos_l'

  Kalman_filter_conv_DW->UnitDelay_DSTATE = Kalman_filter_conv_U->pos_l;

  // Update for UnitDelay: '<S1>/Unit Delay1' incorporates:
  //   Inport: '<Root>/pos_r'

  Kalman_filter_conv_DW->UnitDelay1_DSTATE = Kalman_filter_conv_U->pos_r;

  // Update for UnitDelay: '<S2>/Unit Delay1' incorporates:
  //   Inport: '<Root>/ax'
  //   Inport: '<Root>/ay'
  //   MATLAB Function: '<S1>/MATLAB Function'
  //   MATLAB Function: '<S1>/MATLAB Function1'

  Kalman_filter_conv_DW->UnitDelay1_DSTATE_e[0] = Kalman_filter_conv_U->ax *
    maxval - Kalman_filter_conv_U->ay * rtb_Gain2;
  Kalman_filter_conv_DW->UnitDelay1_DSTATE_e[1] = Kalman_filter_conv_U->ax *
    rtb_Gain2 + Kalman_filter_conv_U->ay * maxval;
  Kalman_filter_conv_DW->UnitDelay1_DSTATE_e[2] = (rtb_w_r - rtb_w_l) *
    0.11621621621621621;
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

    // InitializeConditions for UnitDelay: '<S2>/Unit Delay'
    for (i = 0; i < 5; i++) {
      Kalman_filter_conv_DW->UnitDelay_DSTATE_n[i] =
        Kalman_filter_conv_ConstP.UnitDelay_InitialCondition[i];
    }

    // End of InitializeConditions for UnitDelay: '<S2>/Unit Delay'

    // SystemInitialize for MATLAB Function: '<S2>/MATLAB Function'
    memset(&Kalman_filter_conv_DW->P_N_N[0], 0, 25U * sizeof(real_T));
    for (i = 0; i < 5; i++) {
      Kalman_filter_conv_DW->P_N_N[i + 5 * i] = 1.0;
    }

    // End of SystemInitialize for MATLAB Function: '<S2>/MATLAB Function'
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
