#ifndef MOVEMENT_H
#define MOVEMENT_H

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

class Rotate45clockwise: virtual public Movement {
    public:
        void Execute();
};

class Rotate45CounterClockwise: virtual public Movement {
    public:
        void Execute();
};

class Unstick: public Rotate45clockwise, public Rotate45CounterClockwise {
    public:
        Unstick();
        void Execute();
};

class Dance: public Rotate45clockwise, public Rotate45CounterClockwise {
    public:
        Dance();
        void Execute();
};

#endif