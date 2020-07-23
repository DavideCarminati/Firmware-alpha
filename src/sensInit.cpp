/*! \file sensInit.cpp 
    \brief Thread initializing sensors read at the given frequency

    Creates a timer that calls an interrupt with the given frequency
*/
#include <mbed.h>
#include "FXOS8700CQ.h"
#include "global_vars.hpp"
#include "massStorage.hpp"

#include "sensInit.hpp"
#include "EventQueue.h"
#include "Event.h"
#include "math.h"
#include "magCalibrate.hpp"
#include <ThisThread.h>
#include <Thread.h>
#include <rtos.h>


#define FXOS8700CQ_FREQ 200 //!< Frequency at which the sensor is interrogated

// using namespace events;
// using namespace rtos;
// using namespace ThisThread;
// using namespace mbed;

FXOS8700CQ accmag(PTE25,PTE24);
CalibrateMagneto magCal;
DigitalOut calib_led(LED_GREEN,1);

FILE *f_calib;

float roll,pitch,mag_norm;
float magValues[3], magValues_filt[3], minMag[3], maxMag[3], minExtremes[3], maxExtremes[3];
int measurements_count = 0, id_calib;
char f_buff[100], f_buff_disc[100], temp_char;
float mag_extremes[6];

EventQueue queue;
Event<void(void)> accmagreadEvent(&queue,AccMagRead);
Event<void(void)> calibrationEvent(mbed_event_queue(),calibration);

InterruptIn irq(PTA4);

Thread SensorRead(osPriorityNormal,8092,nullptr,"sensRead");

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
    
    SensorRead.start(postSensorEvent);
    queue.dispatch(); // Start the queue; queue has to be started in this thread!!!
}

void postSensorEvent(void)
{
    // Write here the sensor read events to post them into the queue!
    accmagreadEvent.period(FXOS8700CQ_FREQ); 
    accmagreadEvent.delay(200);
    accmagreadEvent.post();
    // queue.call_every(200,AccMagRead);
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
    pitch = atan2(accmagValues.ax,sqrt(accmagValues.ay*accmagValues.ay + accmagValues.az*accmagValues.az));
    roll = atan2(-accmagValues.ay,sqrt(accmagValues.ax*accmagValues.ax + accmagValues.az*accmagValues.az));
    // feedback_control_U.psi_est = atan2(-accmagValues.my*cos(roll) - accmagValues.mz*sin(roll),accmagValues.mx*cos(pitch) \
    //                             + accmagValues.my*sin(pitch)*sin(roll) - accmagValues.mz*sin(pitch)*cos(roll))*180/3.14;
    feedback_control_U.psi_est = atan2(magValues_filt[1],magValues_filt[0])*180/3.14;
    // printf("yaw: %f\n",feedback_control_U.psi_est);
    // printf("ax: %.2f ay: %.2f az: %.2f pitch: %.2f roll: %.2f yaw: %.2f mx: %.2f my: %.2f mz: %.2f\n", \ 
            // accmagValues.ax, accmagValues.ay, accmagValues.az, pitch*180/3.14, roll*180/3.14, feedback_control_U.psi_est, accmagValues.mx, accmagValues.my, accmagValues.mz);
    // feedback_control_U.reference = (accmagValues.ax + 1)/2; // Normalized between 0 and 1
    // feedback_control_U.estimated = 0;//servo1.read();
    // printf("\033[2;1H");
    // printf("acc read: %f servo read: %f\n", feedback_control_U.reference,feedback_control_U.estimated);
    // printf("%f\n", accmagValues.ax);
    irq.fall(calib_irq_handle);
}

// Interrupt handler that starts the calibration
void calib_irq_handle(void)
{
    // printf("break queue\n");
    queue.break_dispatch();                         // Stop the dispatch of sensor queue while calibrating
    calibrationEvent.period(FXOS8700CQ_FREQ);
    id_calib = calibrationEvent.post();
}

// Calibration event
void calibration(void)
{
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
        mbed_event_queue()->call(writeOnSD);
    }
    
}
void writeOnSD(void)
{
    mbed_event_queue()->cancel(id_calib);
    printf("Writing vals...\n");
    magCal.getExtremes(minMag, maxMag);
    fflush(stdout);
    f_calib = fopen("/fs/calib.txt","a+");
    printf("%s\n", (!f_calib ? "Fail :(" : "OK"));
    fflush(stdout);
    rewind(f_calib);
    long line_begin = ftell(f_calib); // Beginning of the line
    while(!feof(f_calib)) // Now writing into the file on the SD card
    {
        printf("Getting char... \n");
        temp_char = fgetc(f_calib);
        fflush(stdout);
        if (temp_char == '#' || temp_char == '\t')  // Skip the line
        {
            fgets(f_buff_disc,100,f_calib); // Discard the line
            line_begin = ftell(f_calib);    // Set new beginning of the line
            printf("Line discarded\n");
            // memset(f_buff,0,sizeof(f_buff));
            fflush(stdout);
        }
        else // Here I look for the field I'm interested in and I fill it with data
        {
            fseek(f_calib,line_begin,SEEK_SET);
            fgets(f_buff, 100, f_calib);
            printf(f_buff);
            printf("qui\n");
            fflush(stdout);
            if (!strcmp(f_buff,"Magnetometer extremes [minXYZ; maxXYZ]\n"))
            {
                fprintf(f_calib,"\t%.3e %.3e %.3e\n",minMag[0], minMag[1], minMag[2]);
                fprintf(f_calib,"\t%.3e %.3e %.3e\n", maxMag[0], maxMag[1], maxMag[2]);
                line_begin = ftell(f_calib);
                // fflush(stdout);
                printf("done\n");
                fflush(stdout);
                break;

            }
        }
    }
    fclose(f_calib); // Important!
    calib_led = 1;
    queue.dispatch();           // Re-dispatch the sensor queue
}

