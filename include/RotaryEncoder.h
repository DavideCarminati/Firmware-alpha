#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "mbed.h"

/** Encoder class.
 *  Used to read out incremental position encoder. Decodes position in X2 configuration.
 *
 *  Speed estimation is very crude and computationally intensive. Turned off by default
 *
 * Example:
 * @code
 * #include "mbed.h"
 * #include "Encoder.h"
 *
 *   Encoder motor1(PTD0,PTC9,true);
 *   Serial pc(USBTX,USBRX);
 *   pc.baud(115200);
 *   while(1) {
 *       wait(0.2);
 *       pc.printf("pos: %d, speed %f \r\n",motor1.getPosition(), motor1.getSpeed());
 *   }
 * @endcode
 */
class Encoder
{
    public:
    /** Create Encoder instance
    @param int_a Pin to be used as InterruptIn! Be careful, as not all pins on all platforms may be used as InterruptIn.
    @param int_b second encoder pin, used as DigitalIn. Can be any DigitalIn pin, not necessarily on InterruptIn location
    @param speed boolean value to determine whether speed calculation is done in interrupt routine. Default false (no speed calculation)
    */

    Encoder(PinName int_a, PinName int_b, bool speed=false);
    /** Request position
    @returns current position in encoder counts
    */
    int32_t getPosition(){return m_position;}
    /** Overwrite position
    @param pos position to be written
    */
    void    setPosition(int32_t pos){m_position = pos;}
    /** Request speed
    @returns current speed
    */
    float   getSpeed(){return m_speed;}
    private:
    void encoderFalling(void);
    void encoderRising(void);
    bool m_speed_enabled;
    Timer EncoderTimer;
    Timeout EncoderTimeout;
    InterruptIn pin_a;
    DigitalIn pin_b;
    int32_t m_position;
    float   m_speed;
    void timeouthandler(void);
    bool zero_speed;
};


#endif //_ENCODER_H_