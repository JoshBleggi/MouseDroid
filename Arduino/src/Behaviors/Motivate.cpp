#include "Behavior.hpp"
#include "EyeSensor.hpp"
#include "LaserReadingStruct.hpp"
#include "MovementType.hpp"

    Motivate::Motivate() { }

    Motivate::~Motivate() { }

    void Motivate::Init() {
        subsume = true;
        action = new ForwardFullPower();
    };

    void Motivate::Run(Movement* lastAction) {
        EyeSensor* eyes = new EyeSensor();
        LaserReadingStruct readings = eyes->Sense();

        if (readings.Stuck) {
            SetAction(new Unstick());
        }
        else if (!(readings.RightTrigger || readings.LeftTrigger)) {
            SetAction(new ForwardFullPower());
        }
        else if (lastAction->Type() == MovementType::RotateClockwise || readings.RightTrigger) {
            SetAction(new Rotate45clockwise());
        }
        else if (lastAction->Type() == MovementType::RotateCounterClockwise || readings.LeftTrigger) {
            SetAction(new Rotate45CounterClockwise());
        }

        delete eyes;
    };