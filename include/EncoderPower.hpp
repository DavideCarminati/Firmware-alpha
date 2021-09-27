#ifndef _ENCODERPOWER_H_
#define _ENCODERPOWER_H_

#include "mbed.h"
#include "rtwtypes.h"

/** EncoderPower class.
 *  Class to be used to define the use of the EncoderPower conditioned by the state of an switch
 * Example:
 * @code
 * #include "mbed.h"
 * #include "EncoderPower.hpp"
 *
 *   EncoderPower bat(PTBsomething);

 * @endcode
 */
class EncoderPower
{
    public:
    /** Create Encoder instance
    @param int_a Pin to be used as InterruptIn! Be careful, as not all pins on all platforms may be used as InterruptIn.
    */

    EncoderPower(PinName int_a);
    /** Request position
    @returns current position in encoder counts
    */
    int32_t getState(){return bat_in;}

    private:
    void Nothing(void);
    DigitalIn bat_in;

};


#endif //_ENCODER_H_