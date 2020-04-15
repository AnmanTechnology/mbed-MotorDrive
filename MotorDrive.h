//https://os.mbed.com/users/littlexc/code/Motordriver//file/3110b9209d3c/motordriver.cpp/
#ifndef _MOTOR_DRIVE_H_
#define _MOTOR_DRIVE_H_

#include "mbed.h"

/**
 * Interface to control a standard DC motor
 * with an H-bridge using PwmOut and 2 DigitalOuts
 */
class MotorDrive
{
public:
    /**
     * Create a motor control interface
     * @param pwmPin a PwmOut pin, driving the H-Bridge enable line to control the speed
     * @param inAPin a DigitalOut pin, to set the direction of motor
     * @param inBPin a DigitalOut pin, to set the direction of motor
     */
    MotorDrive(PinName pwmPin, PinName inAPin, PinName inBPin);

    /**
     * Set the speed of the motor
     * @param speed The speed of the motor as a nomalised value between -1.0 and 1.0
     */
    void speed(float speed);

    /**
     * Set the speed of the motor with reverse protect
     * @param speed The speed of the motor as a nomalised value between -1.0 and 1.0
     */
    void speedX(float speed);

protected:
    PwmOut _pwm;
    DigitalOut _inA;
    DigitalOut _inB;
    int sign;
};

MotorDrive::MotorDrive(PinName pwmPin, PinName inAPin, PinName inBPin) : _pwm(pwmPin), _inA(inAPin, 0), _inB(inBPin, 0)
{
    _pwm.period_us(50);
    _pwm = 0;
    sign = 0;
}

void MotorDrive::speed(float speed)
{
    _inA = (speed < 0.0);
    _inB = (speed > 0.0);
    _pwm = abs(speed);
}

void MotorDrive::speedX(float speed)
{
    _inA = (speed < 0.0);
    _inB = (speed > 0.0);
    if (sign == 0)
    {
        _pwm = abs(speed);
    }
    else if (sign == 1)
    {
        if (speed < 0)
            _pwm = 0;
        else
            _pwm = abs(speed);
    }
    else if (sign == -1)
    {
        if (speed > 0)
            _pwm = 0;
        else
            _pwm = abs(speed);
    }

    if (speed > 0)
        sign = 1;
    else if (speed < 0)
        sign = -1;
    else
        sign = 0;
}

#endif // _MOTOR_DRIVE_H_