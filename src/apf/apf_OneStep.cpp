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

        APF_conver_U.psi_est = atan2(2*odom.q[0]*odom.q[3],1-2*odom.q[3]*odom.q[3]);
        APF_conver_U.Vx_est = odom.vx*cos(atan2(2*odom.q[0]*odom.q[3],1-2*odom.q[3]*odom.q[3]))+odom.vy*sin(atan2(2*odom.q[0]*odom.q[3],1-2*odom.q[3]*odom.q[3])); // Vx in body frame
        APF_conver_U.X_est = odom.x;
        APF_conver_U.Y_est = odom.y;

        // Step the model
        APF_conver_step(APF_conver_M, &APF_conver_U, &APF_conver_Y);

        leftMotor.Move(APF_conver_Y.PWM_l/3);
        rightMotor.Move(APF_conver_Y.PWM_r/3);
        //printf("PWM: %f, %f pos: %f %f ang: %f \n", APF_conver_Y.PWM_l, APF_conver_Y.PWM_r, odom.x, odom.y, APF_conver_U.psi_est);
        // Get model outputs here

        // Indicate task complete
        // OverrunFlag = false;

        // Disable interrupts here
        // Restore FPU context here (if necessary)
        // Enable interrupts here
        ThisThread::sleep_until(apf_epoch+100);
    }
}