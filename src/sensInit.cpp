/*! \file sensInit.cpp 
    \brief Thread initializing sensors read at the given frequency

    Creates a timer that calls an interrupt with the given frequency
*/
#include <mbed.h>
#include "FXOS8700CQ.h"
#include "global_vars.hpp"

#include "sensInit.hpp"
#include "EventQueue.h"
#include "Event.h"
#include "math.h"
#include "magCalibrate.hpp"

#define FXOS8700CQ_FREQ 200 //!< Frequency at which the sensor is interrogated

FXOS8700CQ accmag(PTE25,PTE24);
CalibrateMagneto magCal;
DigitalOut calib_led(LED_GREEN,1);

float roll,pitch,mag_norm;
float magValues[3], magValues_filt[3], minMag[3], maxMag[3];
int measurements_count = 0;
char f_buff[100];

EventQueue queue;
Event<void(void)> accmagreadEvent(&queue,AccMagRead);
Event<void(void)> calibrationEvent(mbed_event_queue(),calibration);

InterruptIn irq(PTA4);

Thread SensorRead(osPriorityNormal,8092,nullptr,"sensRead");

void sensInit()
{
    accmag.init();
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
    calibrationEvent.period(FXOS8700CQ_FREQ);
    int id_calib = calibrationEvent.post();
}

// Calibration event
void calibration(void)
{
    calib_led = 0;
    queue.break_dispatch();         // Stop the dispatch of sensor queue while calibrating
    measurements_count++;
    magCal.run(magValues,magValues_filt);
    // When reached the number of initial points the calibration is complete
    if (measurements_count == INITIAL_POINTS)
    {
        magCal.getExtremes(minMag, maxMag); 
        // magCal.setExtremes(minMag, maxMag);
        FILE *f_calib = fopen("/fs/params/calib.txt","w+");
        while(fgetc(f_calib) != EOF) // Now writing into the file on the SD card
        {
            if (fgetc(f_calib) == '#')
            {
                do
                {
                    long f_pos = ftell(f_calib);
                    fseek(f_calib,f_pos++,SEEK_CUR);
                } while (fgetc(f_calib) == '\n');
                
            }
            else
            {
                fgets(f_buff, 100, f_calib);
                if (f_buff == "Magnetometer extremes")
                {
                    fprintf(f_calib,"minXYZ %.3f %.3f %.3f\n",minMag[0], minMag[1], minMag[2]);
                    fprintf(f_calib,"maxXYZ %.3f %.3f %.3f\n", maxMag[0], maxMag[1], maxMag[2]);

                }
            }
        }
        calib_led = 1;
        queue.dispatch();           // Re-dispatch the sensor queue
        calibrationEvent.cancel();  // Cancel this event
    }
    
}

