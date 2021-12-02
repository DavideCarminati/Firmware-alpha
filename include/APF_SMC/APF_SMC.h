//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: APF_SMC.h
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
#ifndef RTW_HEADER_APF_SMC_h_
#define RTW_HEADER_APF_SMC_h_
#include <cmath>
#include <math.h>
#include <string.h>
#ifndef APF_SMC_COMMON_INCLUDES_
# define APF_SMC_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 // APF_SMC_COMMON_INCLUDES_

#include "APF_SMC_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rtGetInf.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

// Block states (default storage) for system '<Root>'
typedef struct {
  real_T UD_DSTATE;                    // '<S3>/UD'
  real_T UD_DSTATE_o;                  // '<S4>/UD'
  real_T UD_DSTATE_d;                  // '<S1>/UD'
  real_T UD_DSTATE_p;                  // '<S2>/UD'
  real_T en;                           // '<S12>/MATLAB Function'
} DW_APF_SMC_T;

// External inputs (root inport signals with default storage)
typedef struct {
  real_T psi;                          // '<Root>/psi'
  real_T Vx;                           // '<Root>/Vx'
  real_T X_est;                        // '<Root>/X_est'
  real_T Y_est;                        // '<Root>/Y_est'
  real_T X_goal;                       // '<Root>/X_goal'
  real_T Y_goal;                       // '<Root>/Y_goal'
  real_T ox;                           // '<Root>/ox'
  real_T oy;                           // '<Root>/oy'
} ExtU_APF_SMC_T;

// External outputs (root outports fed by signals with default storage)
typedef struct {
  real_T Vx_cmd;                       // '<Root>/Vx_cmd'
  real_T psi_cmd;                      // '<Root>/psi_cmd'
} ExtY_APF_SMC_T;

// Parameters (default storage)
struct P_APF_SMC_T_ {
  real_T DiscreteDerivative2_ICPrevScale;
                              // Mask Parameter: DiscreteDerivative2_ICPrevScale
                                 //  Referenced by: '<S3>/UD'

  real_T DiscreteDerivative3_ICPrevScale;
                              // Mask Parameter: DiscreteDerivative3_ICPrevScale
                                 //  Referenced by: '<S4>/UD'

  real_T DiscreteDerivative_ICPrevScaled;
                              // Mask Parameter: DiscreteDerivative_ICPrevScaled
                                 //  Referenced by: '<S1>/UD'

  real_T DiscreteDerivative1_ICPrevScale;
                              // Mask Parameter: DiscreteDerivative1_ICPrevScale
                                 //  Referenced by: '<S2>/UD'

  real_T Constant_Value;               // Expression: 0.1
                                          //  Referenced by: '<Root>/Constant'

  real_T TSamp_WtEt;                   // Computed Parameter: TSamp_WtEt
                                          //  Referenced by: '<S3>/TSamp'

  real_T TSamp_WtEt_e;                 // Computed Parameter: TSamp_WtEt_e
                                          //  Referenced by: '<S4>/TSamp'

  real_T Gain_Gain;                    // Expression: 180/pi
                                          //  Referenced by: '<Root>/Gain'

  real_T Gain2_Gain;                   // Expression: 180/pi
                                          //  Referenced by: '<Root>/Gain2'

  real_T TSamp_WtEt_d;                 // Computed Parameter: TSamp_WtEt_d
                                          //  Referenced by: '<S1>/TSamp'

  real_T TSamp_WtEt_o;                 // Computed Parameter: TSamp_WtEt_o
                                          //  Referenced by: '<S2>/TSamp'

  real_T Constant_Value_f;             // Expression: 0
                                          //  Referenced by: '<S6>/Constant'

  boolean_T Constant_Value_n;          // Computed Parameter: Constant_Value_n
                                          //  Referenced by: '<S7>/Constant'

};

// Real-time Model Data Structure
struct tag_RTM_APF_SMC_T {
  const char_T * volatile errorStatus;
  DW_APF_SMC_T *dwork;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    boolean_T stopRequestedFlag;
  } Timing;
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern P_APF_SMC_T APF_SMC_P;

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void APF_SMC_initialize(RT_MODEL_APF_SMC_T *const APF_SMC_M,
    ExtU_APF_SMC_T *APF_SMC_U, ExtY_APF_SMC_T *APF_SMC_Y);
  extern void APF_SMC_step(RT_MODEL_APF_SMC_T *const APF_SMC_M, ExtU_APF_SMC_T
    *APF_SMC_U, ExtY_APF_SMC_T *APF_SMC_Y);
  extern void APF_SMC_terminate(RT_MODEL_APF_SMC_T *const APF_SMC_M);

#ifdef __cplusplus

}
#endif

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S1>/Data Type Duplicate' : Unused code path elimination
//  Block '<S2>/Data Type Duplicate' : Unused code path elimination
//  Block '<S3>/Data Type Duplicate' : Unused code path elimination
//  Block '<S4>/Data Type Duplicate' : Unused code path elimination
//  Block '<S11>/Scope1' : Unused code path elimination
//  Block '<S11>/Scope3' : Unused code path elimination
//  Block '<S11>/Scope4' : Unused code path elimination
//  Block '<Root>/Rate Transition' : Unused code path elimination
//  Block '<Root>/Rate Transition1' : Unused code path elimination
//  Block '<Root>/Scope' : Unused code path elimination
//  Block '<Root>/Scope1' : Unused code path elimination
//  Block '<Root>/Scope2' : Unused code path elimination
//  Block '<Root>/To Workspace1' : Unused code path elimination
//  Block '<Root>/To Workspace5' : Unused code path elimination


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'APF_SMC'
//  '<S1>'   : 'APF_SMC/Discrete Derivative'
//  '<S2>'   : 'APF_SMC/Discrete Derivative1'
//  '<S3>'   : 'APF_SMC/Discrete Derivative2'
//  '<S4>'   : 'APF_SMC/Discrete Derivative3'
//  '<S5>'   : 'APF_SMC/GUIDANCE '
//  '<S6>'   : 'APF_SMC/IsNonZero'
//  '<S7>'   : 'APF_SMC/IsZero'
//  '<S8>'   : 'APF_SMC/MATLAB Function'
//  '<S9>'   : 'APF_SMC/MATLAB Function1'
//  '<S10>'  : 'APF_SMC/MATLAB Function2'
//  '<S11>'  : 'APF_SMC/GUIDANCE /APF'
//  '<S12>'  : 'APF_SMC/GUIDANCE /INITIAL ORIENTATION'
//  '<S13>'  : 'APF_SMC/GUIDANCE /APF/IAPF'
//  '<S14>'  : 'APF_SMC/GUIDANCE /INITIAL ORIENTATION/MATLAB Function'

#endif                                 // RTW_HEADER_APF_SMC_h_

//
// File trailer for generated code.
//
// [EOF]
//
