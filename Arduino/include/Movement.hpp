#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "ActionComparer.hpp"
#include "Arduino.h"
#include "Constants.hpp"
#include "MovementType.hpp"

class Movement {
    public:
        bool InManeuver;

        virtual void Execute();
        Movement();
        virtual ~Movement();
	    virtual MovementType Type();
    
    protected:
        void SetMotorsForward();
        void SetMotorsReverse();
};

class ForwardFullPower: public Movement {
    public:
        void Execute();
        MovementType Type();
};

class ReverseFullPower: public Movement {
    public:
        void Execute();
        MovementType Type();
};

class Rotate45clockwise: virtual public Movement {
    public:
        void Execute();
        MovementType Type();
};

class Rotate45CounterClockwise: virtual public Movement {
    public:
        void Execute();
        MovementType Type();
};

class Unstick: virtual public Rotate45clockwise, public Rotate45CounterClockwise {
    public:
        void Execute();
        MovementType Type();
};

class Dance: virtual public Rotate45clockwise, public Rotate45CounterClockwise {
    public:
        void Execute();
        MovementType Type();
};

#endif