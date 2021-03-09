#include <stddef.h>
#include <stdio.h>                // This ert_main.c example uses printf/fflush
#include "APF_conver.h"                // Model's header file
#include "rtwtypes.h"

#include "global_vars.hpp"
#include "global_msgs.hpp"
#include "mbed.h"
#include "TankMotor.hpp"

#include "apf_OneStep.hpp"

Timer apf_timer;
uint64_t apf_epoch;

TankMotor leftMotor(PTC10,PTB23,PTA2), rightMotor(PTC11,PTB9,PTA1);

void apf(RT_MODEL_APF_conver_T *const APF_conver_M)
{
    apf_timer.start();
    while (1)
    {
        apf_epoch = Kernel::get_ms_count();
        // static boolean_T OverrunFlag = false;

        // Disable interrupts here

        // Check for overrun
        // if (OverrunFlag) {
        //     rtmSetErrorStatus(APF_conver_M, "Overrun");
        //     return;
        // }

        // OverrunFlag = true;

        // Save FPU context here (if necessary)
        // Re-enable timer or interrupt here
        // Set model inputs here

        APF_conver_U.psi_est = Kalman_filter_conv_Y.psi;
        APF_conver_U.Vx_est = Kalman_filter_conv_Y.Vx;
        APF_conver_U.X_est = Kalman_filter_conv_Y.X;
        APF_conver_U.Y_est = Kalman_filter_conv_Y.Y;

        // Step the model
        APF_conver_step(APF_conver_M, &APF_conver_U, &APF_conver_Y);

        leftMotor.Move(APF_conver_Y.PWM_l);
        rightMotor.Move(APF_conver_Y.PWM_r);

        // Get model outputs here

        // Indicate task complete
        // OverrunFlag = false;

        // Disable interrupts here
        // Restore FPU context here (if necessary)
        // Enable interrupts here
        ThisThread::sleep_until(apf_epoch+100);
    }
}