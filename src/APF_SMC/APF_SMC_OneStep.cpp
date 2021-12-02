#include <stddef.h>
#include <stdio.h>                // This ert_main.c example uses printf/fflush
#include "APF_SMC/APF_SMC.h"                // Model's header file
#include "rtwtypes.h"

#include "global_vars.hpp"
#include "global_msgs.hpp"
#include "mbed.h"
#include "TankMotor.hpp"

#include "APF_SMC/APF_SMC_OneStep.hpp"

Timer apf_timer;
uint64_t apf_epoch, PWM_r, PWM_l;

TankMotor leftMotor(PTC10,PTB23,PTA2), rightMotor(PTC11,PTB9,PTA1);

void apf(RT_MODEL_APF_SMC_T *const APF_SMC_M)
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
        // TODO AZZERARE POSIZIONE QUANDO SI SPEGNE IL ROBOT
        APF_SMC_U.X_goal = 1;
        APF_SMC_U.Y_goal = 0;
        APF_SMC_U.ox = 10;
        APF_SMC_U.oy = 10;

        APF_SMC_U.psi_est = atan2(2*odom.q[0]*odom.q[3],1-2*odom.q[3]*odom.q[3]);
        APF_SMC_U.Vx_est = odom.vx*cos(atan2(2*odom.q[0]*odom.q[3],1-2*odom.q[3]*odom.q[3]))+odom.vy*sin(atan2(2*odom.q[0]*odom.q[3],1-2*odom.q[3]*odom.q[3])); // Vx in body frame
        APF_SMC_U.X_est = odom.x;
        APF_SMC_U.Y_est = odom.y;

        // Step the model
        APF_SMC_step(APF_SMC_M, &APF_SMC_U, &APF_SMC_Y);
        // printf("%f %f \n", APF_conver_Y.PWM_l/2, APF_conver_Y.PWM_r/2);

        PWM_r = (APF_SMC_Y.Vx_cmd + APF_SMC_Y.psi_cmd) *20000;

        // Saturate: '<S4>/Saturation1'
        if (PWM_r > 20000) {
            PWM_r = 20000;
        } else {
            if (PWM_r < -20000) {
            PWM_r = -20000;
            }
        }
         
        PWM_l = (APF_SMC_Y.Vx_cmd - APF_SMC_Y.psi_cmd) *20000;

        // Saturate: '<S4>/Saturation1'
        if (PWM_l > 20000) {
            PWM_l = 20000;
        } else {
            if (PWM_l < -20000) {
            PWM_l = -20000;
            }
        }

        leftMotor.Move(PWM_l/3);  //TODO this is a limit for speed. Change to have fast dynamics
        rightMotor.Move(PWM_r/3); 

        // //printf("PWM: %f, %f pos: %f %f ang: %f \n", APF_conver_Y.PWM_l, APF_conver_Y.PWM_r, odom.x, odom.y, APF_conver_U.psi_est);
        // Get model outputs here

        // Indicate task complete
        // OverrunFlag = false;

        // Disable interrupts here
        // Restore FPU context here (if necessary)
        // Enable interrupts here
        ThisThread::sleep_until(apf_epoch+100);
    }
}