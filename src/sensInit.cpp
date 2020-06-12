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

#define FXOS8700CQ_FREQ 50 //!< Frequency at which the sensor is interrogated

FXOS8700CQ accmag(PTE25,PTE24);

// EventQueue queue;
Event<void(void)> accmagreadEvent(&queue,AccMagRead);

Thread SensorRead(osPriorityNormal,8092,nullptr,"sensRead");

Data accmagValues;

void sensInit()
{
    accmag.init();
    SensorRead.start(postSensorEvent);

    queue.dispatch(); // Start the queue
}

void postSensorEvent(void)
{
    // Write here the sensor read events to post them into the queue!
    accmagreadEvent.period(FXOS8700CQ_FREQ); // 100 ms
    accmagreadEvent.delay(200);
    accmagreadEvent.post();
}

// TODO: add semaphore to protect the write-to-buffer operation in the following event!
void AccMagRead(void) // Event to copy sensor value from its register to extern variable
{

    accmagValues = accmag.get_values(); 
    feedback_control_U.reference = (accmagValues.ax + 1)/2; // Normalized between 0 and 1
    feedback_control_U.estimated = 0;//servo1.read();
    // printf("\033[2;1H");
    // printf("acc read: %f servo read: %f\n", feedback_control_U.reference,feedback_control_U.estimated);
}

