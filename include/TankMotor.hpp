/*! @class TankMotor.hpp

    @brief Class used to move tank motors using PWM

    @author Davide Carminati, Matteo Scanavino

    @details
*/
#include <mbed.h>

class TankMotor
{
    public:
        TankMotor(PinName pin, PinName forwardPin, PinName backwardPin);
        void Move(int pwm);
        
    private:
        PwmOut _pwmout;
        DigitalOut _in_forward, _in_backward;
};