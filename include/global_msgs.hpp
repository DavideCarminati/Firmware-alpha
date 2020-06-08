/** \file global_msgs.hpp */
/**
 * Declaration and definition of used mavlink structs
 * 
 */

#include <mbed.h>
#include "common/mavlink.h"

#ifndef MAVLINK_ATT
#define MAVLINK_ATT
extern mavlink_attitude_t att;
#endif