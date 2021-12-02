#include <stddef.h>
#include <stdio.h>                // This ert_main.c example uses printf/fflush
#include "APF_SMC/APF_SMC.h"                // Model's header file
#include "rtwtypes.h"
#include "mbed.h"

#include "global_vars.hpp"

#include "APF_SMC/APF_SMC_Init.hpp"
#include "APF_SMC/APF_SMC_OneStep.hpp"

static RT_MODEL_APF_SMC_T APF_SMC_M_;
static RT_MODEL_APF_SMC_T *const APF_SMC_MPtr = &APF_SMC_M_;// Real-time model 
static DW_APF_SMC_T APF_SMC_DW;  // Observable states

const char* apf_thread_name = "APF";

Thread APF(osPriorityNormal,8096,nullptr,apf_thread_name);

void APF_SMC_Init(void)
{
    RT_MODEL_APF_SMC_T *const APF_SMC_M = APF_SMC_MPtr;

    // Pack model data into RTM
    APF_SMC_M->dwork = &APF_SMC_DW;

    // Initialize model
    APF_SMC_initialize(APF_SMC_M, &APF_SMC_U, &APF_SMC_Y);

    APF.start(callback(apf, APF_SMC_M));

}