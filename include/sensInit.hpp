#include <mbed.h>
#include "FXOS8700CQ.h"
#include "global_vars.hpp"

#define FXOS8700CQ_FREQ 50 //!< Frequency at which the sensor is interrogated

void sensInit(void);
void postSensorEvent(void);
void AccMagRead(void);
