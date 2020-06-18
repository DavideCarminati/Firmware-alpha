#include "TankMotor.hpp"

TankMotor::TankMotor(PinName PWMpin, PinName forwardPin, PinName backwardPin) : _pwmout(PWMpin), _in_forward(forwardPin), _in_backward(backwardPin)
{
    _pwmout.period(0.02);
    _pwmout.pulsewidth_us(0);
    _in_backward.write(0);
    _in_forward.write(0);
};

void TankMotor::Move(int pwm)
{
    if(pwm > 0)
    {
        _in_forward.write(1);
        _in_backward.write(0);
        _pwmout.pulsewidth_us(pwm);
    }
    else if(pwm < 0)
    {
        _in_forward.write(0);
        _in_backward.write(1);
        _pwmout.pulsewidth_us(-pwm);
    }
    else if(pwm == 0)
    {
        _in_backward.write(0);
        _in_forward.write(0);
    }
};