#include <cmath>
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"




void sensInit(void);
void postSensorEvent(void);
extern void AccMagRead(void);
void calib_irq_handle(void);
void calibration(void);
void readFromSD(void);
void refreshParamFileSD(void);
extern void EncoderRead(void);
void AccImuRead(void);