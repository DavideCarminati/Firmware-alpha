#ifndef _BATTERY_H_
#define _BATTERY_H_

#include "mbed.h"
#include "rtwtypes.h"

/** Battery class.
 *  Class to be used to define the use of the battery conditioned by the state of an switch
 * Example:
 * @code
 * #include "mbed.h"
 * #include "Battery.hpp"
 *
 *   Battery bat(PTBsomething);

 * @endcode
 */
class Battery
{
    public:
    /** Create Encoder instance
    @param int_a Pin to be used as InterruptIn! Be careful, as not all pins on all platforms may be used as InterruptIn.
    */

    Battery(PinName int_a);
    /** Request position
    @returns current position in encoder counts
    */
    int32_t getState(){return bat_in;}

    private:
    void Nothing(void);
    DigitalIn bat_in;

};


#endif //_ENCODER_H_