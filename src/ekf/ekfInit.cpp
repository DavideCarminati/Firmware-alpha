#include <stddef.h>
#include <stdio.h>                // This ert_main.c example uses printf/fflush
#include "Kalman_filter_conv.h"        // Model's header file
#include "rtwtypes.h"

#include "global_vars.hpp"
#include "global_msgs.hpp"

#include "ekfInit.hpp"
#include "ekf_OneStep.hpp"

static RT_MODEL_Kalman_filter_conv_T Kalman_filter_conv_M_;
static RT_MODEL_Kalman_filter_conv_T *const Kalman_filter_conv_MPtr =
  &Kalman_filter_conv_M_;              // Real-time model
static DW_Kalman_filter_conv_T Kalman_filter_conv_DW;// Observable states

const char* ekf_thread_name = "EKF";

Thread EKF(osPriorityNormal,8096,nullptr,ekf_thread_name);

void ekfInit(void)
{
    RT_MODEL_Kalman_filter_conv_T *const Kalman_filter_conv_M =
    Kalman_filter_conv_MPtr;

    // Pack model data into RTM
    Kalman_filter_conv_M->dwork = &Kalman_filter_conv_DW;

    // Initialize model
    Kalman_filter_conv_initialize(Kalman_filter_conv_M, &Kalman_filter_conv_U,
      &Kalman_filter_conv_Y);

    EKF.start(callback(ekf, Kalman_filter_conv_M));
}