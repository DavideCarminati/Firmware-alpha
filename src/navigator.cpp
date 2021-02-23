#include <mbed.h>
#include "global_msgs.hpp"
#include "global_vars.hpp"
#include "math.h"

#include "navigator.hpp"

double V;

struct Angle
{
    double roll;
    double pitch;
    double yaw;
} angles;

struct Quaternion {
    double w, x, y, z;
} q;

float toll_pos = 0.05;
float toll_ang = 2.5;

Timer timerNav;

void navigator()
{
    
    timerNav.reset();
    timerNav.start();
    while(1)
    {
        // semUDPNav.acquire();
        // if(flagMavlink)
        // {
        //     feedback_control_U.X_est = sqrt(odom.x*odom.x + odom.y*odom.y); //sqrt(odom.vx*odom.vx + odom.vy*odom.vy + odom.vz*odom.vz);
        //     // for(int ii=0; ii<4; ii++) feedback_control_U.q_est[ii] = odom.q[ii];
        
        //     q.x = odom.q[0];
        //     q.y = odom.q[1];
        //     q.z = odom.q[2];
        //     q.w = odom.q[3];
        // }

        // // roll (x-axis rotation)
        // double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
        // double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
        // angles.roll = atan2(sinr_cosp, cosr_cosp);

        // // pitch (y-axis rotation)
        // double sinp = 2 * (q.w * q.y - q.z * q.x);
        // if (abs(sinp) >= 1)
        //     angles.pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
        // else
        //     angles.pitch = asin(sinp);

        // // yaw (z-axis rotation)
        // double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
        // double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
        // angles.yaw = atan2(siny_cosp, cosy_cosp)*180/M_PI;

        // feedback_control_U.psi_est = angles.yaw;

        // printf("\033[3;1H");
        // printf("yaw: %f x_est: %f",feedback_control_U.psi_est,feedback_control_U.X_est);

        // semNavContr.release();

        // feedback_control_U.X_ref = 1;
        // feedback_control_U.psi_ref = 0;


        // while (abs(feedback_control_U.X_ref - feedback_control_U.X_est)>toll_pos)
        // {
        //     feedback_control_U.X_ref = 1;
        //     feedback_control_U.psi_ref = 0;
        // }
        
        // while (abs(feedback_control_U.psi_ref - feedback_control_U.psi_est)>toll_ang)
        // {
        //     feedback_control_U.X_ref = 1;
        //     feedback_control_U.psi_ref = 180;
        // }

        // while (abs(feedback_control_U.X_ref - feedback_control_U.X_est)>toll_pos)
        // {
        //     feedback_control_U.X_ref = 0;
        //     feedback_control_U.psi_ref = 180;
        // }
        
        // printf("Timer: %f\n",timerNav.read());

        if(timerNav.read() < 10)
        {
            // printf("\033[1;1H");
            // printf("manovra 0");
            PI_contr_Y.pwm_left = 0;
            PI_contr_Y.pwm_right = 0;
        }
        else if(timerNav.read() >= 10 && timerNav.read() < 17)
        {
            // printf("\033[1;1H");
            // printf("manovra 1");
            PI_contr_Y.pwm_left = 7000;
            PI_contr_Y.pwm_right = 7000;
        }
        else if(timerNav.read() >= 17 && timerNav.read() < 18)
        {
            // printf("\033[1;1H");
            // printf("manovra 2");
            PI_contr_Y.pwm_left = 0;
            PI_contr_Y.pwm_right = 0;
        }
           else if(timerNav.read() >= 18 && timerNav.read() < 21)
           {
               // printf("\033[1;1H");
               // printf("manovra 3");
               PI_contr_Y.pwm_left = 12000;
               PI_contr_Y.pwm_right = -12000;
           }

           else if(timerNav.read() >= 21 && timerNav.read() < 22)
           {
               // printf("\033[1;1H");
               // printf("manovra 3");
               PI_contr_Y.pwm_left = 0;
               PI_contr_Y.pwm_right = 0;
           }

           else if(timerNav.read() >= 22 && timerNav.read() < 25)
           {
               // printf("\033[1;1H");
               // printf("manovra 3");
               PI_contr_Y.pwm_left = 15000;
               PI_contr_Y.pwm_right = 15000;
           }

           else if(timerNav.read() >= 25 && timerNav.read() < 28)
           {
               // printf("\033[1;1H");
               // printf("manovra 1");
               PI_contr_Y.pwm_left = 0;
               PI_contr_Y.pwm_right = 0;
           }
        //   else if(timerNav.read() >= 28 && timerNav.read() < 31)
        //   {
        //       // printf("\033[1;1H");
        //       // printf("manovra 2");
        //       PI_contr_Y.pwm_left = 12000;
        //       PI_contr_Y.pwm_right = -12000;
        //   }
        //   else if(timerNav.read() >= 31 && timerNav.read() < 33)
        //   {
        //       // printf("\033[1;1H");
        //       // printf("manovra 3");
        //       PI_contr_Y.pwm_left = 0;
        //       PI_contr_Y.pwm_right = 0;
        //   }
        //    else if(timerNav.read() >= 33 && timerNav.read() < 36)
        //   {
        //       // printf("\033[1;1H");
        //       // printf("manovra 3");
        //       PI_contr_Y.pwm_left = 13000;
        //       PI_contr_Y.pwm_right = 13000;
        //   }
        //  else if(timerNav.read() >= 36 && timerNav.read() < 41)
        //   {
        //       // printf("\033[1;1H");
        //       // printf("manovra 2");
        //       PI_contr_Y.pwm_left = 0;
        //       PI_contr_Y.pwm_right = 0;
        //   }
        //  else if(timerNav.read() >= 41 && timerNav.read() < 44)
        //  {
        //      // printf("\033[1;1H");
        //      // printf("manovra 3");
        //      PI_contr_Y.pwm_left = -19000;
        //      PI_contr_Y.pwm_right = 19000;
        //  }
        //   else if(timerNav.read() >= 44 && timerNav.read() < 47)
        //  {
        //      // printf("\033[1;1H");
        //      // printf("manovra 3");
        //      PI_contr_Y.pwm_left = 0;
        //      PI_contr_Y.pwm_right = 0;
        //  }
        //  else if(timerNav.read() >= 47 && timerNav.read() < 50)
        //  {
        //      // printf("\033[1;1H");
        //      // printf("manovra 2");
        //      PI_contr_Y.pwm_left =20000;
        //      PI_contr_Y.pwm_right = -20000;
        //  }
        //  else if(timerNav.read() >= 50 && timerNav.read() < 53)
        //  {
        //      // printf("\033[1;1H");
        //      // printf("manovra 3");
        //      PI_contr_Y.pwm_left = 0;
        //      PI_contr_Y.pwm_right = 0;
        //  }
        //   else if(timerNav.read() >= 53 && timerNav.read() < 56)
        //  {
        //      // printf("\033[1;1H");
        //      // printf("manovra 3");
        //      PI_contr_Y.pwm_left = -20000;
        //      PI_contr_Y.pwm_right = 20000;
        //  }
        //   else if(timerNav.read() >= 56 && timerNav.read() < 59)
        //  {
        //      // printf("\033[1;1H");
        //      // printf("manovra 3");
        //      PI_contr_Y.pwm_left = 0;
        //      PI_contr_Y.pwm_right = 0;
        //  }
        // else
        // {
        //     timerNav.reset();
        // }        

        // feedback_control_U.X_ref = 0;
        // feedback_control_U.psi_ref = timerNav.read()*36;
        // if(feedback_control_U.psi_ref > 360)
        // {
        //     feedback_control_U.X_ref = 0;
        //     feedback_control_U.psi_ref = 0;
        // }
        // else
        // {
        //     // printf("\033[1;1H");
        //     // printf("manovra 4");
        //     feedback_control_U.X_ref = 0;
        //     feedback_control_U.psi_ref = 0;
            
        // }
        
    }



}