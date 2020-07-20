// #include <mbed.h>
// #include "FXOS8700CQ.h"
// #include "global_vars.hpp"

// #define FXOS8700CQ_FREQ 50 //!< Frequency at which the sensor is interrogated

void sensInit(void);
void postSensorEvent(void);
void AccMagRead(void);
void calib_irq_handle(void);
void calibration(void);
void writeOnSD(void);
