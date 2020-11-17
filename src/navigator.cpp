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

        if(timerNav.read() < 5)
        {
            // printf("\033[1;1H");
            // printf("manovra 0");
            feedback_control_U.X_ref = 0;
            feedback_control_U.psi_ref = 0;
        }
        else if(timerNav.read() >= 5 && timerNav.read() < 10)
        {
            // printf("\033[1;1H");
            // printf("manovra 1");
            feedback_control_U.X_ref = 0;
            feedback_control_U.psi_ref = 0;
        }
        // else if(timerNav.read() >= 8 && timerNav.read() < 11)
        // {
        //     // printf("\033[1;1H");
        //     // printf("manovra 2");
        //     feedback_control_U.X_ref = 0;
        //     feedback_control_U.psi_ref = 180;
        // }
        // else if(timerNav.read() >= 11 && timerNav.read() < 14)
        // {
        //     // printf("\033[1;1H");
        //     // printf("manovra 3");
        //     feedback_control_U.X_ref = 0.5;
        //     feedback_control_U.psi_ref = 180;
        // }

        // else if(timerNav.read() >= 14 && timerNav.read() < 17)
        // {
        //     // printf("\033[1;1H");
        //     // printf("manovra 3");
        //     feedback_control_U.X_ref = -0.5;
        //     feedback_control_U.psi_ref = 0;
        // }

        // else if(timerNav.read() >= 17 && timerNav.read() < 20)
        // {
        //     // printf("\033[1;1H");
        //     // printf("manovra 3");
        //     feedback_control_U.X_ref = 0;
        //     feedback_control_U.psi_ref = 0;
        // }
        // else if(timerNav.read() >= 35 && timerNav.read() < 45)
        // {
        //     // printf("\033[1;1H");
        //     // printf("manovra 1");
        //     feedback_control_U.X_ref = 0;
        //     feedback_control_U.psi_ref = 90;
        // }
        // else if(timerNav.read() >= 45 && timerNav.read() < 55)
        // {
        //     // printf("\033[1;1H");
        //     // printf("manovra 2");
        //     feedback_control_U.X_ref = 0;
        //     feedback_control_U.psi_ref = 45;
        // }
        // else if(timerNav.read() >= 55 && timerNav.read() < 65)
        // {
        //     // printf("\033[1;1H");
        //     // printf("manovra 3");
        //     feedback_control_U.X_ref = 0;
        //     feedback_control_U.psi_ref = 0;
        // }

        else
        {
            timerNav.reset();
        }        

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