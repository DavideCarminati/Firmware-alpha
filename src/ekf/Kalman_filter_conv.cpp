//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Kalman_filter_conv.cpp
//
// Code generated for Simulink model 'Kalman_filter_conv'.
//
// Model version                  : 1.11
// Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
// C/C++ source code generated on : Thu Mar 25 17:05:55 2021
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "Kalman_filter_conv.h"
#include "Kalman_filter_conv_private.h"


// Forward declaration for local functions
static void Kalman_filter_c_mrdivide_helper(real_T A[40], const real_T B[64],
  B_Kalman_filter_conv_T *Kalman_filter_conv_B);

// Function for MATLAB Function: '<S1>/MATLAB Function'
static void Kalman_filter_c_mrdivide_helper(real_T A[40], const real_T B[64],
  B_Kalman_filter_conv_T *Kalman_filter_conv_B)
{
  int32_T j;
  int32_T c;
  int32_T ix;
  real_T smax;
  real_T s;
  int32_T k;
  int32_T b_ix;
  int32_T c_ix;
  int32_T d;
  int32_T ijA;
  memcpy(&Kalman_filter_conv_B->b_A[0], &B[0], sizeof(real_T) << 6U);
  for (j = 0; j < 8; j++) {
    Kalman_filter_conv_B->ipiv[j] = static_cast<int8_T>((1 + j));
  }

  for (j = 0; j < 7; j++) {
    c = j * 9;
    b_ix = 0;
    ix = c;
    smax = std::abs(Kalman_filter_conv_B->b_A[c]);
    for (k = 2; k <= 8 - j; k++) {
      ix++;
      s = std::abs(Kalman_filter_conv_B->b_A[ix]);
      if (s > smax) {
        b_ix = k - 1;
        smax = s;
      }
    }

    if (Kalman_filter_conv_B->b_A[c + b_ix] != 0.0) {
      if (b_ix != 0) {
        ix = j + b_ix;
        Kalman_filter_conv_B->ipiv[j] = static_cast<int8_T>((ix + 1));
        b_ix = j;
        for (k = 0; k < 8; k++) {
          smax = Kalman_filter_conv_B->b_A[b_ix];
          Kalman_filter_conv_B->b_A[b_ix] = Kalman_filter_conv_B->b_A[ix];
          Kalman_filter_conv_B->b_A[ix] = smax;
          b_ix += 8;
          ix += 8;
        }
      }

      b_ix = (c - j) + 8;
      for (ix = c + 1; ix < b_ix; ix++) {
        Kalman_filter_conv_B->b_A[ix] /= Kalman_filter_conv_B->b_A[c];
      }
    }

    b_ix = c;
    ix = c + 8;
    for (k = 0; k <= 6 - j; k++) {
      if (Kalman_filter_conv_B->b_A[ix] != 0.0) {
        smax = -Kalman_filter_conv_B->b_A[ix];
        c_ix = c + 1;
        d = (b_ix - j) + 16;
        for (ijA = 9 + b_ix; ijA < d; ijA++) {
          Kalman_filter_conv_B->b_A[ijA] += Kalman_filter_conv_B->b_A[c_ix] *
            smax;
          c_ix++;
        }
      }

      ix += 8;
      b_ix += 8;
    }
  }

  for (c = 0; c < 8; c++) {
    b_ix = 5 * c;
    ix = c << 3;
    for (k = 0; k < c; k++) {
      c_ix = 5 * k;
      smax = Kalman_filter_conv_B->b_A[k + ix];
      if (smax != 0.0) {
        for (d = 0; d < 5; d++) {
          j = d + b_ix;
          A[j] -= smax * A[d + c_ix];
        }
      }
    }

    smax = 1.0 / Kalman_filter_conv_B->b_A[c + ix];
    for (ix = 0; ix < 5; ix++) {
      j = ix + b_ix;
      A[j] *= smax;
    }
  }

  for (c = 7; c >= 0; c--) {
    b_ix = 5 * c;
    ix = (c << 3) - 1;
    for (k = c + 2; k < 9; k++) {
      c_ix = (k - 1) * 5;
      smax = Kalman_filter_conv_B->b_A[k + ix];
      if (smax != 0.0) {
        for (d = 0; d < 5; d++) {
          j = d + b_ix;
          A[j] -= smax * A[d + c_ix];
        }
      }
    }
  }

  for (c = 6; c >= 0; c--) {
    if (c + 1 != Kalman_filter_conv_B->ipiv[c]) {
      b_ix = Kalman_filter_conv_B->ipiv[c] - 1;
      for (ix = 0; ix < 5; ix++) {
        k = 5 * c + ix;
        smax = A[k];
        j = 5 * b_ix + ix;
        A[k] = A[j];
        A[j] = smax;
      }
    }
  }
}

 real_T rt_atan2d2_snf(real_T u0, real_T u1)
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
void Kalman_filter_conv_step(RT_MODEL_Kalman_filter_conv_T *const
  Kalman_filter_conv_M, ExtU_Kalman_filter_conv_T *Kalman_filter_conv_U,
  ExtY_Kalman_filter_conv_T *Kalman_filter_conv_Y)
{
  B_Kalman_filter_conv_T *Kalman_filter_conv_B = ((B_Kalman_filter_conv_T *)
    Kalman_filter_conv_M->blockIO);
  DW_Kalman_filter_conv_T *Kalman_filter_conv_DW = ((DW_Kalman_filter_conv_T *)
    Kalman_filter_conv_M->dwork);
  int32_T k;
  static const int8_T b[5] = { 0, 0, 0, 0, 1 };

  static const int8_T tmp[40] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1 };

  int32_T i;
  int32_T rtb_F_tmp;
  int32_T b_I_tmp;

  // MATLAB Function: '<Root>/MATLAB Function2' incorporates:
  //   Constant: '<Root>/Cov_Y_rs'
  //   Constant: '<Root>/cov_Vx_enc'
  //   Constant: '<Root>/cov_Vx_rs'
  //   Constant: '<Root>/cov_Vy_rs'
  //   Constant: '<Root>/cov_X_rs'
  //   Constant: '<Root>/cov_psi_enc'
  //   Constant: '<Root>/cov_psi_mag'
  //   Constant: '<Root>/cov_psi_rs'

  memset(&Kalman_filter_conv_B->R[0], 0, sizeof(real_T) << 6U);
  for (k = 0; k < 8; k++) {
    Kalman_filter_conv_B->R[k + (k << 3)] = 1.0;
  }

  Kalman_filter_conv_B->R[0] = Kalman_filter_conv_P.cov_X_rs_Value;
  Kalman_filter_conv_B->R[9] = Kalman_filter_conv_P.Cov_Y_rs_Value;
  Kalman_filter_conv_B->R[18] = Kalman_filter_conv_P.cov_Vx_rs_Value;
  Kalman_filter_conv_B->R[27] = Kalman_filter_conv_P.cov_Vy_rs_Value;
  Kalman_filter_conv_B->R[36] = Kalman_filter_conv_P.cov_psi_rs_Value;
  Kalman_filter_conv_B->R[45] = Kalman_filter_conv_P.cov_Vx_enc_Value;
  Kalman_filter_conv_B->R[54] = Kalman_filter_conv_P.cov_psi_enc_Value;
  Kalman_filter_conv_B->R[63] = Kalman_filter_conv_P.cov_psi_mag_Value;

  // End of MATLAB Function: '<Root>/MATLAB Function2'

  // MATLAB Function: '<S1>/H'
  for (k = 0; k < 40; k++) {
    Kalman_filter_conv_B->H[k] = tmp[k];
  }

  // End of MATLAB Function: '<S1>/H'

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
  Kalman_filter_conv_B->psidot_enc = (Kalman_filter_conv_B->w_r -
    Kalman_filter_conv_B->w_l) * 0.11621621621621621;

  // MATLAB Function: '<S1>/F' incorporates:
  //   MATLAB Function: '<S1>/f'
  //   SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport2'
  //   UnitDelay: '<S1>/Unit Delay'

  Kalman_filter_conv_B->F[0] = 1.0;
  Kalman_filter_conv_B->F[5] = 0.0;
  Kalman_filter_conv_B->rtb_F_tmp_p = std::cos
    (Kalman_filter_conv_DW->UnitDelay_DSTATE[4]);
  Kalman_filter_conv_B->rtb_F_tmp_c = 0.2 * Kalman_filter_conv_B->rtb_F_tmp_p;
  Kalman_filter_conv_B->F[10] = Kalman_filter_conv_B->rtb_F_tmp_c;
  Kalman_filter_conv_B->rtb_F_tmp = std::sin
    (Kalman_filter_conv_DW->UnitDelay_DSTATE[4]);
  Kalman_filter_conv_B->F[15] = 0.2 * -Kalman_filter_conv_B->rtb_F_tmp;
  Kalman_filter_conv_B->rtb_F_tmp_f = Kalman_filter_conv_B->rtb_F_tmp_p *
    Kalman_filter_conv_DW->UnitDelay_DSTATE[3];
  Kalman_filter_conv_B->F[20] = (-Kalman_filter_conv_DW->UnitDelay_DSTATE[2] *
    Kalman_filter_conv_B->rtb_F_tmp - Kalman_filter_conv_B->rtb_F_tmp_f) * 0.2;
  Kalman_filter_conv_B->F[1] = 0.0;
  Kalman_filter_conv_B->F[6] = 1.0;
  Kalman_filter_conv_B->F[11] = 0.2 * Kalman_filter_conv_B->rtb_F_tmp;
  Kalman_filter_conv_B->F[16] = Kalman_filter_conv_B->rtb_F_tmp_c;
  Kalman_filter_conv_B->rtb_F_tmp_p = (Kalman_filter_conv_B->rtb_F_tmp_p *
    Kalman_filter_conv_DW->UnitDelay_DSTATE[2] - Kalman_filter_conv_B->rtb_F_tmp
    * Kalman_filter_conv_DW->UnitDelay_DSTATE[3]) * 0.2;
  Kalman_filter_conv_B->F[21] = Kalman_filter_conv_B->rtb_F_tmp_p;
  Kalman_filter_conv_B->F[2] = 0.0;
  Kalman_filter_conv_B->F[7] = 0.0;
  Kalman_filter_conv_B->F[12] = 1.0;
  Kalman_filter_conv_B->F[17] = Kalman_filter_conv_B->psidot_enc * 0.2;
  Kalman_filter_conv_B->F[22] = 0.0;
  Kalman_filter_conv_B->F[3] = 0.0;
  Kalman_filter_conv_B->F[8] = 0.0;
  Kalman_filter_conv_B->F[13] = -Kalman_filter_conv_B->psidot_enc * 0.2;
  Kalman_filter_conv_B->F[18] = 1.0;
  Kalman_filter_conv_B->F[23] = 0.0;
  for (k = 0; k < 5; k++) {
    Kalman_filter_conv_B->F[4 + 5 * k] = b[k];
  }

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
  Kalman_filter_conv_DW->DiscreteTimeIntegrator_DSTATE +=
    Kalman_filter_conv_P.DiscreteTimeIntegrator_gainval *
    Kalman_filter_conv_B->psidot_enc;

  // MATLAB Function: '<S1>/f' incorporates:
  //   Inport: '<Root>/ax'
  //   Inport: '<Root>/ay'
  //   MATLAB Function: '<S1>/F'
  //   SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport2'
  //   UnitDelay: '<S1>/Unit Delay'

  Kalman_filter_conv_B->x[0] = Kalman_filter_conv_B->rtb_F_tmp_p +
    Kalman_filter_conv_DW->UnitDelay_DSTATE[0];
  Kalman_filter_conv_B->x[1] = (Kalman_filter_conv_B->rtb_F_tmp *
    Kalman_filter_conv_DW->UnitDelay_DSTATE[2] +
    Kalman_filter_conv_B->rtb_F_tmp_f) * 0.2 +
    Kalman_filter_conv_DW->UnitDelay_DSTATE[1];
  Kalman_filter_conv_B->x[2] = (Kalman_filter_conv_B->psidot_enc *
    Kalman_filter_conv_DW->UnitDelay_DSTATE[3] + Kalman_filter_conv_U->ax) * 0.2
    + Kalman_filter_conv_DW->UnitDelay_DSTATE[2];
  Kalman_filter_conv_B->x[3] = (Kalman_filter_conv_U->ay -
    Kalman_filter_conv_B->psidot_enc * Kalman_filter_conv_DW->UnitDelay_DSTATE[2])
    * 0.2 + Kalman_filter_conv_DW->UnitDelay_DSTATE[3];
  Kalman_filter_conv_B->x[4] = Kalman_filter_conv_B->psidot_enc * 0.2 +
    Kalman_filter_conv_DW->UnitDelay_DSTATE[4];

  // MATLAB Function: '<S1>/MATLAB Function'
  for (k = 0; k < 5; k++) {
    for (i = 0; i < 5; i++) {
      rtb_F_tmp = k + 5 * i;
      Kalman_filter_conv_B->rtb_F_k[rtb_F_tmp] = 0.0;
      for (b_I_tmp = 0; b_I_tmp < 5; b_I_tmp++) {
        Kalman_filter_conv_B->rtb_F_k[rtb_F_tmp] += Kalman_filter_conv_B->F[5 *
          b_I_tmp + k] * Kalman_filter_conv_DW->P_N_N[5 * i + b_I_tmp];
      }
    }

    for (i = 0; i < 5; i++) {
      rtb_F_tmp = k + 5 * i;
      Kalman_filter_conv_B->rtb_F_c[rtb_F_tmp] = 0.0;
      for (b_I_tmp = 0; b_I_tmp < 5; b_I_tmp++) {
        Kalman_filter_conv_B->rtb_F_c[rtb_F_tmp] +=
          Kalman_filter_conv_B->rtb_F_k[5 * b_I_tmp + k] *
          Kalman_filter_conv_B->F[5 * b_I_tmp + i];
      }
    }
  }

  // MATLAB Function: '<Root>/MATLAB Function1' incorporates:
  //   Constant: '<Root>/cov_Vx'
  //   Constant: '<Root>/cov_Vy'
  //   Constant: '<Root>/cov_X'
  //   Constant: '<Root>/cov_Y'
  //   Constant: '<Root>/cov_psi'

  Kalman_filter_conv_B->rtb_F_k[0] = Kalman_filter_conv_P.cov_X_Value;
  Kalman_filter_conv_B->rtb_F_k[5] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[10] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[15] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[20] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[1] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[6] = Kalman_filter_conv_P.cov_Y_Value;
  Kalman_filter_conv_B->rtb_F_k[11] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[16] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[21] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[2] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[7] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[12] = Kalman_filter_conv_P.cov_Vx_Value;
  Kalman_filter_conv_B->rtb_F_k[17] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[22] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[3] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[8] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[13] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[18] = Kalman_filter_conv_P.cov_Vy_Value;
  Kalman_filter_conv_B->rtb_F_k[23] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[4] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[9] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[14] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[19] = 0.0;
  Kalman_filter_conv_B->rtb_F_k[24] = Kalman_filter_conv_P.cov_psi_Value;

  // MATLAB Function: '<S1>/MATLAB Function'
  for (k = 0; k < 25; k++) {
    Kalman_filter_conv_B->F[k] = Kalman_filter_conv_B->rtb_F_c[k] +
      Kalman_filter_conv_B->rtb_F_k[k];
  }

  for (k = 0; k < 5; k++) {
    for (i = 0; i < 8; i++) {
      rtb_F_tmp = k + 5 * i;
      Kalman_filter_conv_B->K[rtb_F_tmp] = 0.0;
      for (b_I_tmp = 0; b_I_tmp < 5; b_I_tmp++) {
        Kalman_filter_conv_B->K[rtb_F_tmp] += Kalman_filter_conv_B->F[5 *
          b_I_tmp + k] * static_cast<real_T>(Kalman_filter_conv_B->H[(b_I_tmp <<
          3) + i]);
      }
    }
  }

  for (k = 0; k < 8; k++) {
    for (i = 0; i < 5; i++) {
      rtb_F_tmp = k + (i << 3);
      Kalman_filter_conv_B->rtb_H_c[rtb_F_tmp] = 0.0;
      for (b_I_tmp = 0; b_I_tmp < 5; b_I_tmp++) {
        Kalman_filter_conv_B->rtb_H_c[rtb_F_tmp] += static_cast<real_T>
          (Kalman_filter_conv_B->H[(b_I_tmp << 3) + k]) *
          Kalman_filter_conv_B->F[5 * i + b_I_tmp];
      }
    }

    for (i = 0; i < 8; i++) {
      Kalman_filter_conv_B->psidot_enc = 0.0;
      for (b_I_tmp = 0; b_I_tmp < 5; b_I_tmp++) {
        rtb_F_tmp = b_I_tmp << 3;
        Kalman_filter_conv_B->psidot_enc += Kalman_filter_conv_B->
          rtb_H_c[rtb_F_tmp + k] * static_cast<real_T>(Kalman_filter_conv_B->
          H[rtb_F_tmp + i]);
      }

      rtb_F_tmp = (i << 3) + k;
      Kalman_filter_conv_B->rtb_H_m[rtb_F_tmp] = Kalman_filter_conv_B->
        R[rtb_F_tmp] + Kalman_filter_conv_B->psidot_enc;
    }
  }

  Kalman_filter_c_mrdivide_helper(Kalman_filter_conv_B->K,
    Kalman_filter_conv_B->rtb_H_m, Kalman_filter_conv_B);
  for (k = 0; k < 25; k++) {
    Kalman_filter_conv_B->b_I[k] = 0;
  }

  for (k = 0; k < 5; k++) {
    Kalman_filter_conv_B->b_I[k + 5 * k] = 1;
  }

  for (k = 0; k < 5; k++) {
    for (i = 0; i < 5; i++) {
      Kalman_filter_conv_B->psidot_enc = 0.0;
      for (b_I_tmp = 0; b_I_tmp < 8; b_I_tmp++) {
        Kalman_filter_conv_B->psidot_enc += Kalman_filter_conv_B->K[5 * b_I_tmp
          + k] * static_cast<real_T>(Kalman_filter_conv_B->H[(i << 3) + b_I_tmp]);
      }

      b_I_tmp = 5 * i + k;
      Kalman_filter_conv_B->rtb_F_c[b_I_tmp] = static_cast<real_T>
        (Kalman_filter_conv_B->b_I[b_I_tmp]) - Kalman_filter_conv_B->psidot_enc;
    }

    for (i = 0; i < 5; i++) {
      rtb_F_tmp = k + 5 * i;
      Kalman_filter_conv_DW->P_N_N[rtb_F_tmp] = 0.0;
      for (b_I_tmp = 0; b_I_tmp < 5; b_I_tmp++) {
        Kalman_filter_conv_DW->P_N_N[rtb_F_tmp] += Kalman_filter_conv_B->
          rtb_F_c[5 * b_I_tmp + k] * Kalman_filter_conv_B->F[5 * i + b_I_tmp];
      }
    }
  }

  // SignalConversion: '<S8>/TmpSignal ConversionAt SFunction Inport1' incorporates:
  //   Inport: '<Root>/Vx_rs'
  //   Inport: '<Root>/Vy_rs'
  //   Inport: '<Root>/X_rs'
  //   Inport: '<Root>/Y_rs'
  //   Inport: '<Root>/psi_mag'
  //   Inport: '<Root>/q0_rs'
  //   Inport: '<Root>/q1_rs'
  //   Inport: '<Root>/q2_rs'
  //   Inport: '<Root>/q3_rs'
  //   MATLAB Function: '<Root>/MATLAB Function'
  //   MATLAB Function: '<Root>/MATLAB Function3'
  //   MATLAB Function: '<S1>/MATLAB Function'

  Kalman_filter_conv_B->dv0[0] = Kalman_filter_conv_U->X_rs;
  Kalman_filter_conv_B->dv0[1] = Kalman_filter_conv_U->Y_rs;
  Kalman_filter_conv_B->dv0[2] = Kalman_filter_conv_U->Vx_rs;
  Kalman_filter_conv_B->dv0[3] = Kalman_filter_conv_U->Vy_rs;
  Kalman_filter_conv_B->dv0[4] = rt_atan2d2_snf((Kalman_filter_conv_U->q0_rs *
    Kalman_filter_conv_U->q3_rs + Kalman_filter_conv_U->q1_rs *
    Kalman_filter_conv_U->q2_rs) * 2.0, 1.0 - (Kalman_filter_conv_U->q2_rs *
    Kalman_filter_conv_U->q2_rs + Kalman_filter_conv_U->q3_rs *
    Kalman_filter_conv_U->q3_rs) * 2.0);
  Kalman_filter_conv_B->dv0[5] = (Kalman_filter_conv_B->w_r +
    Kalman_filter_conv_B->w_l) * 0.01075;
  Kalman_filter_conv_B->dv0[6] =
    Kalman_filter_conv_DW->DiscreteTimeIntegrator_DSTATE;
  Kalman_filter_conv_B->dv0[7] = Kalman_filter_conv_U->psi_mag;

  // MATLAB Function: '<S1>/MATLAB Function' incorporates:
  //   UnitDelay: '<S1>/Unit Delay'

  for (k = 0; k < 8; k++) {
    Kalman_filter_conv_B->rtb_H_b[k] = 0.0;
    for (i = 0; i < 5; i++) {
      Kalman_filter_conv_B->rtb_H_b[k] += static_cast<real_T>
        (Kalman_filter_conv_B->H[(i << 3) + k]) * Kalman_filter_conv_B->x[i];
    }

    Kalman_filter_conv_B->dv1[k] = Kalman_filter_conv_B->dv0[k] -
      Kalman_filter_conv_B->rtb_H_b[k];
  }

  for (k = 0; k < 5; k++) {
    Kalman_filter_conv_B->psidot_enc = 0.0;
    for (i = 0; i < 8; i++) {
      Kalman_filter_conv_B->psidot_enc += Kalman_filter_conv_B->K[5 * i + k] *
        Kalman_filter_conv_B->dv1[i];
    }

    Kalman_filter_conv_DW->UnitDelay_DSTATE[k] = Kalman_filter_conv_B->x[k] +
      Kalman_filter_conv_B->psidot_enc;
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

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

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
