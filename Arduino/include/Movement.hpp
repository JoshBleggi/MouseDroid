#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Arduino.h"
#include "Constants.hpp"
#include "SensorState.hpp"

class Movement {
    public:
        virtual void Execute();
    
    protected:
        bool InManeuver;

        Movement();
        void SetMotorsForward();
        void SetMotorsReverse();
};


class ForwardFullPower: public Movement {
    public:
        void Execute();
};

class ReverseFullPower: public Movement {
    public:
        void Execute();
};

class Rotate45clockwise: public Movement {
    public:
        void Execute();
};

class Rotate45CounterClockwise: public Movement {
    public:
        void Execute();
};

#endif