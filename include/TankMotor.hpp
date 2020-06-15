/*! @class TankMotor.hpp

    @brief Class used to move tank motors using PWM

    @author Davide Carminati

    @details
*/
#include <mbed.h>

class TankMotor
{
    public:
        TankMotor(PinName pin);
        
    private:
        PwmOut _pwmout;
};