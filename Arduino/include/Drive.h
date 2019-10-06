#ifndef DRIVE_H
#define DRIVE_H

#include "SensorState.h"

#define MOTOR_RIGHT_PWM 9
#define MOTOR_RIGHT_DIR 10
#define MOTOR_LEFT_PWM 11
#define MOTOR_LEFT_DIR 12

extern bool InManeuver;

class Drive {
    public:
        void selectDrive(SensorState triggeredState);
    private:
        void SetMotorsForward();
        void SetMotorsReverse();
        void ReverseFullPower();
        void ForwardFullPower();
        void Rotate45clockwise();
        void Rotate45CounterClockwise();
};

#endif