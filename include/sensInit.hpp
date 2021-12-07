#include <cmath>
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"


// External outputs (root outports fed by signals with default storage)
typedef struct {
  real_T X;                            // '<Root>/X'
  real_T Y;                            // '<Root>/Y'
  real_T psi;                          // '<Root>/psi '
  real_T Vx;                           // '<Root>/Vx '
  real_T Vy;                           // '<Root>/Vy '
} SensinitY_Variables;


typedef struct {
  real_T pos_l;                        // '<Root>/pos_l'
  real_T pos_r;                        // '<Root>/pos_r'
  real_T psi_mag;                      // '<Root>/psi_mag'
  real_T ax;                           // '<Root>/ax'
  real_T ay;                           // '<Root>/ay'
  real_T X_rs;                         // '<Root>/X_rs'
  real_T Y_rs;                         // '<Root>/Y_rs'
  real_T Vx_rs;                        // '<Root>/Vx_rs'
  real_T Vy_rs;                        // '<Root>/Vy_rs'
  real_T q0_rs;                        // '<Root>/q0_rs'
  real_T q1_rs;                        // '<Root>/q1_rs'
  real_T q2_rs;                        // '<Root>/q2_rs'
  real_T q3_rs;                        // '<Root>/q3_rs'
} SensinitU_Variables;

void sensInit(void);
void postSensorEvent(void);
void AccMagRead(SensinitU_Variables*VblesU);
void calib_irq_handle(void);
void calibration(void);
void readFromSD(void);
void refreshParamFileSD(void);
void EncoderRead(SensinitU_Variables*VblesU);
void AccImuRead(void);