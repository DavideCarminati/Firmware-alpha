#include <stddef.h>
#include <stdio.h>                // This ert_main.c example uses printf/fflush
#include "Kalman_filter_conv.h"        // Model's header file
#include "rtwtypes.h"

#include "global_vars.hpp"
#include "global_msgs.hpp"
#include "mbed.h"

#include "ekf_OneStep.hpp"

Timer ekf_timer;
uint64_t ekf_epoch;

void ekf(RT_MODEL_Kalman_filter_conv_T *const Kalman_filter_conv_M)
{
    ekf_timer.start();
    while (1)
    {
        ekf_epoch = Kernel::get_ms_count();
        // static boolean_T OverrunFlag = false;

        // Disable interrupts here

        // Check for overrun
        // if (OverrunFlag) {
        //     rtmSetErrorStatus(Kalman_filter_conv_M, "Overrun");
        //     return;
        // }

        // OverrunFlag = true;

        // Save FPU context here (if necessary)
        // Re-enable timer or interrupt here
        // Set model inputs here

        // Inputs defined in sensinit.cpp

        // Step the model
        Kalman_filter_conv_step(Kalman_filter_conv_M, &Kalman_filter_conv_U,
            &Kalman_filter_conv_Y);

        // Get model outputs here

        // Indicate task complete
        // OverrunFlag = false;

        // Disable interrupts here
        // Restore FPU context here (if necessary)
        // Enable interrupts here
        ThisThread::sleep_until(ekf_epoch+200);
    }
}