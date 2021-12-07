/*! \file sensInit.cpp 
    \brief Thread initializing sensors read at the given frequency

    Creates a timer that calls an interrupt with the given frequency
*/
#include <cstdio>
#include <mbed.h>
#include "FXOS8700CQ.h"
#include "global_vars.hpp"
#include "global_msgs.hpp" // for a debug printf
#include "massStorage.hpp"
#include "RotaryEncoder.h"

#include "sensInit.hpp"
#include "EventQueue.h"
#include "Event.h"
#include "math.h"
#include "magCalibrate.hpp"
#include <ThisThread.h>
#include <Thread.h>
#include <rtos.h>

#include "Imu/ADXL345_I2C.h"
#include "Imu/ITG3200.h"
#include "ManualSwitch.hpp"

#define FXOS8700CQ_FREQ 200 //!< Frequency at which the sensor is interrogated
#define ACCIMU_FREQ 200
// using namespace events;
// using namespace rtos;
// using namespace ThisThread;
// using namespace mbed;

I2C i2c(PTE25,PTE24);

FXOS8700CQ accmag(PTE25,PTE24);
CalibrateMagneto magCal;
DigitalOut calib_led(LED_GREEN,1), controllerLedSensorThread(LED_BLUE,1);

Encoder encoderL(PTB18, PTB19, true);
Encoder encoderR(PTC1, PTC8, true);

ITG3200 gyro(PTE25,PTE24, 0x68);

ADXL345_I2C imu(PTE25,PTE24);

ManualSwitch switchEnc(PTD3);
// DigitalIn batteryOn(PTD3, PullUp);
DigitalOut ledPin(PTD2);

FILE *f_calib;

float roll,pitch,mag_norm;
float magValues[3], magValues_filt[3], minExtremes[3], maxExtremes[3], minMag[3], maxMag[3];
int measurements_count = 0, id_calib;
char f_buff[100], f_buff_disc[100], temp_char;
float mag_extremes[6];
int16_t readings[3];
// char cmd[2];

int32_t posL, posR;
int32_t val;
float speedL, speedR;
Data2 imuextValues, data_test;

EventQueue queue;
// EventQueue SDaccessQueue(8096);
Event<void(void)> accmagreadEvent(&queue,AccMagRead);
Event<void(void)> calibrationEvent(mbed_event_queue(),calibration);
Event<void(void)> encoderEvent(&queue, EncoderRead);
Event<void(void)> accimureadEvent(&queue,AccImuRead);

const char* sdcard_access_thread_name = "SDStorageAccess";
Thread SDStorageAccess(osPriorityNormal,16184,nullptr,sdcard_access_thread_name);

InterruptIn irq(PTA4);

Thread SensorRead(osPriorityNormal,8092,nullptr,"sensRead");
Timer puttyTimer;

void sensInit()
{
    accmag.init();
    // Open file with params and get them...
    if (readFromSD(mag_extremes, "Magnetometer extremes [minXYZ; maxXYZ]\n") < 0)
    {
        // MBED_WARNING(MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_CODE_FAILED_OPERATION),"SD card has no calib.txt file to open! Please format the SD card and calibrate\n");
        printf("SD card has no calib.txt file to open! Please format the SD card and calibrate\n");
    }
    else
    {
        minExtremes[0] = mag_extremes[0];
        minExtremes[1] = mag_extremes[1];
        minExtremes[2] = mag_extremes[2];
        maxExtremes[0] = mag_extremes[3];
        maxExtremes[1] = mag_extremes[4];
        maxExtremes[2] = mag_extremes[5];
        magCal.setExtremes(minExtremes,maxExtremes);
        for (int ii = 0; ii < 6; ii++)
        {
            printf("data out mag extr %f\n", mag_extremes[ii]);
        }
    }
    printf("\033[2J");
    SensorRead.start(postSensorEvent);
    queue.dispatch(); // Start the queue; queue has to be started in this thread!!!
    // SDaccessQueue.dispatch();


}

void postSensorEvent(void)
{
    // Write here the sensor read events to post them into the queue!
    accmagreadEvent.period(FXOS8700CQ_FREQ); 
    accmagreadEvent.delay(200);
    accmagreadEvent.post();
    // queue.call_every(200,AccMagRead);
    encoderEvent.period(100);
    encoderEvent.delay(200);
    encoderEvent.post();

    accimureadEvent.period(ACCIMU_FREQ); 
    accimureadEvent.delay(200);
    accimureadEvent.post();

    puttyTimer.start();
}

void EncoderRead(void)
{
    //Are encoders ON? If not, reset their positions
    val = switchEnc.getState();
    if (val == 1) {ledPin = 1;}
    
    else {
        ledPin = 0;     
        encoderL.Reset(true);   // True is for resetting the encoder timer too
        encoderR.Reset(true);   // True is for resetting the encoder timer too
    }

    posL = -encoderL.getPosition()*360/(1920);
    posR = encoderR.getPosition()*360/(1920);
    VblesU.pos_l = posL;
    VblesU.pos_r = posR;
    
    speedL = encoderL.getSpeed()*60; // rpm
    speedR = encoderR.getSpeed()*60;
    // time_t secs = time(NULL);
    //int32_t value = 1000;
    // if (posL > value){
    //     encoderL.Reset(true);
    // printf("battery level:%d\n", bat.getState());
    // }
    // int secs = puttyTimer.read_ms();
    // printf("\033[13;1H");
    // printf("Encoder position: %d  %d\n",Kalman_filter_conv_U.pos_l, Kalman_filter_conv_U.pos_r);
    // printf("time %d, pwm left,right: %f, %f X Y Vx Vy psi %f %f %f %f %f Vref %f psiref %f\n", 
    //    secs, APF_conver_Y.PWM_l, APF_conver_Y.PWM_r, odom.x, odom.y, odom.vx, odom.vy, atan2(2*odom.q[0]*odom.q[3],1-2*odom.q[3]*odom.q[3]), debug_vel_ref, debug_psi_ref);
    
    
}

// TODO: add semaphore to protect the write-to-buffer operation in the following event!
void AccMagRead(void) // Event to copy sensor value from its register to extern variable
{
    accmagValues = accmag.get_values();
    magValues[0] = accmagValues.mx;
    magValues[1] = accmagValues.my;
    magValues[2] = accmagValues.mz;
    magCal.run(magValues,magValues_filt);
    // mag_norm=0.00001;
    mag_norm = sqrt(accmagValues.mx*accmagValues.mx + accmagValues.my*accmagValues.my + accmagValues.mz*accmagValues.mz);
    accmagValues.mx = accmagValues.mx/mag_norm;
    accmagValues.my = accmagValues.my/mag_norm;
    accmagValues.mz = accmagValues.mz/mag_norm;
    pitch = atan2(accmagValues.ax,sqrt(accmagValues.ay*accmagValues.ay + accmagValues.az*accmagValues.az)); // ax, ay in g e non in m/s^2!!!
    roll = atan2(-accmagValues.ay,sqrt(accmagValues.ax*accmagValues.ax + accmagValues.az*accmagValues.az));
    // feedback_control_U.psi_est = atan2(-accmagValues.my*cos(roll) - accmagValues.mz*sin(roll),accmagValues.mx*cos(pitch) \
    //                             + accmagValues.my*sin(pitch)*sin(roll) - accmagValues.mz*sin(pitch)*cos(roll))*180/3.14;
    // PI_contr_U.psi_odom = atan2(magValues_filt[1],magValues_filt[0])*180/3.14;
    // printf("yaw: %f\n",feedback_control_U.psi_est);
    // printf("ax: %.2f ay: %.2f az: %.2f pitch: %.2f roll: %.2f yaw: %.2f mx: %.2f my: %.2f mz: %.2f\n", \
    //         accmagValues.ax, accmagValues.ay, accmagValues.az, pitch*180/3.14, roll*180/3.14, feedback_control_U.psi_est, accmagValues.mx, accmagValues.my, accmagValues.mz);
    // feedback_control_U.reference = (accmagValues.ax + 1)/2; // Normalized between 0 and 1
    // feedback_control_U.estimated = 0;//servo1.read();
    // printf("\033[2;1H");
    // printf("acc read: %f servo read: %f\n", feedback_control_U.reference,feedback_control_U.estimated);
    // printf("%f\n", accmagValues.ax);
    // TODO Control sign Kalman_filter_conv_U.psi_mag = -atan2(magValues_filt[1],-magValues_filt[0]);//*180/3.14;
    VblesU.psi_mag = atan2(magValues_filt[1],magValues_filt[0]);
    VblesU.ax = accmagValues.ax*9.81;
    VblesU.ay = accmagValues.ay*9.81;
    // // Internal IMU data
    // wait(0.1);
    // printf("Internal IMU data:\n");
    // printf("ax, ay, az: %f  %f  %f  q4: %f \n", accmagValues.ax, accmagValues.ay, accmagValues.az, Kalman_filter_conv_U.psi_mag*180/3.14); 
    irq.rise(calib_irq_handle);
}

void AccImuRead(void) 
{
    ////////// Print ID of I²C devices connected
    // printf("ITG3200 gyro DevID 0x%02X\n",gyro.getWhoAmI());
    // printf("FXOS8700CQ DevID0x%02X\n",accmag.get_who_am_i());
    // printf("ADXL345 acc DevID0x%02X\n",imu.getDeviceID());
    ////////////////////////////////////////

    // External imu configuration ///////////
    //Go into standby mode to configure the device.
    imu.setPowerControl(0x00);
    //Full resolution, +/-16g, 4mg/LSB.
    imu.setDataFormatControl(0x0B);
    //3.2kHz data rate.
    imu.setDataRate(ADXL345_3200HZ);
    //Measurement mode.
    imu.setPowerControl(0x08);
    //////////////////////////////////////////
    // External accelerom data
    // wait(0.1);
    // printf("External IMU data:\n");
    imu.getOutput(readings);
    // //13-bit, sign extended values.
    // // Typical resolution is 256 == 1g
    
    float accel_resol = 256;
    // printf("acc_x: %f g, acc_y: %f g, acc_z: %f g\n", (float)readings[0]/accel_resol, (float)readings[1]/accel_resol, (float)readings[2]/accel_resol);

    // wait(0.1);
    // External gyro data
    // Units are degrees per second
    float gyro_resol = 14.375; //LSB per º/second
    // printf("gyr_x: %f, gyr_y: %f , gyr_z: %f \n", gyro.getGyroX()/gyro_resol, gyro.getGyroY()/gyro_resol, gyro.getGyroZ()/gyro_resol);
    // data_test.ax = (float)readings[0]/accel_resol;
    // data_test.ay = (float)readings[1]/accel_resol;
    // data_test.az = (float)readings[2]/accel_resol;
    // data_test.gx = gyro.getGyroX()/gyro_resol;
    // data_test.gy = gyro.getGyroY()/gyro_resol;
    // data_test.gz = gyro.getGyroZ()/gyro_resol;
    // imuextValues.ax = data_test.ax;
    // imuextValues.ay = data_test.ay;
    // imuextValues.az = data_test.az;
    // imuextValues.gx = data_test.gx;
    // imuextValues.gx = data_test.gy;
    // imuextValues.gx = data_test.gz;

    // if (batteryOn== true)
    //     ledPin = 1;
    // else 
    // ledPin = 0;






    imuextValues.ax = (float)readings[1]/accel_resol;
    imuextValues.ay = -(float)readings[0]/accel_resol;
    imuextValues.az = (float)readings[2]/accel_resol;
    imuextValues.gx = gyro.getGyroY()/gyro_resol;
    imuextValues.gy = -gyro.getGyroX()/gyro_resol;
    imuextValues.gz = gyro.getGyroZ()/gyro_resol;
    //printf("%f ,    %f ,     %f %f ,    %f %f ,   %f %f,    %f %f\n", imuextValues.gx, imuextValues.gy, imuextValues.gz,Kalman_filter_conv_U.psi_mag*180/3.14, imuextValues.ax*9.81, -accmagValues.ax*9.81, imuextValues.ay*9.81, accmagValues.ay*9.81, imuextValues.az*9.81,   -accmagValues.az*9.81);


    
    
    //printf("ax: %.2f ay: %.2f az: %.2f \n", ax_2, ay_2, az_2);
}



// Interrupt handler that starts the calibration
void calib_irq_handle(void)
{
    // printf("break queue\n");
    irq.rise(NULL);
    queue.break_dispatch();                         // Stop the dispatch of sensor queue while calibrating
    calibrationEvent.period(FXOS8700CQ_FREQ);
    id_calib = calibrationEvent.post();
}

// Calibration event
void calibration(void)
{
    // printf("Thread name: %s; Thread id: %d", ThisThread::get_name(), ThisThread::get_id());
    if(measurements_count == 0)
    {
        controllerLedSensorThread = 1;
        led_lock.lock();
    }
    calib_led = 0;
    measurements_count++;
    printf("measurm %d\n",measurements_count);
    accmagValues = accmag.get_values();
    magValues[0] = accmagValues.mx;
    magValues[1] = accmagValues.my;
    magValues[2] = accmagValues.mz;
    magCal.run(magValues,magValues_filt);
    // When reached the number of initial points the calibration is complete
    if (measurements_count == INITIAL_POINTS)
    {
        // It means the magnetometer is calibrated, so I raise a flag signaling that
        measurements_count = 0;
        SDStorageAccess.start(refreshParamFileSD);
        led_lock.unlock();
    }
    
}
void refreshParamFileSD(void)
{
    mbed_event_queue()->cancel(id_calib);
    printf("Updating the parameters file on the SD card...\n");
    magCal.getExtremes(minMag, maxMag);
    float magData_in[6] = {minMag[0], minMag[1], minMag[2], maxMag[0], maxMag[1], maxMag[2]};
    if(parametersUpdate(magData_in, "Magnetometer extremes [minXYZ; maxXYZ]\n") == MBED_SUCCESS)
    {
        printf("Done updating params!\n");
        calib_led = 1;
        queue.dispatch();           // Re-dispatch the sensor queue
        irq.rise(calib_irq_handle); // Re/enable the rise interrupt on the button to avoid multiple calibrations
        SDStorageAccess.join();
    }
}




