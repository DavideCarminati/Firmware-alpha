#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "feedback_control.h"          /* Model's header file */
#include "rtwtypes.h"

// #include "global_vars.hpp"
// #include "common/mavlink.h"

void rt_OneStep(RT_MODEL_feedback_control_T *const feedback_control_M);