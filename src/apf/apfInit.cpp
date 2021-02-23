#include <stddef.h>
#include <stdio.h>                // This ert_main.c example uses printf/fflush
#include "APF_conver.h"                // Model's header file
#include "rtwtypes.h"
#include "mbed.h"

#include "global_vars.hpp"

#include "apfInit.hpp"
#include "apf_OneStep.hpp"

static RT_MODEL_APF_conver_T APF_conver_M_;
static RT_MODEL_APF_conver_T *const APF_conver_MPtr = &APF_conver_M_;// Real-time model 
static DW_APF_conver_T APF_conver_DW;  // Observable states

const char* apf_thread_name = "APF";

Thread APF(osPriorityNormal,8096,nullptr,apf_thread_name);

void apfInit(void)
{
    RT_MODEL_APF_conver_T *const APF_conver_M = APF_conver_MPtr;

    // Pack model data into RTM
    APF_conver_M->dwork = &APF_conver_DW;

    // Initialize model
    APF_conver_initialize(APF_conver_M, &APF_conver_U, &APF_conver_Y);

    APF.start(callback(apf, APF_conver_M));

}