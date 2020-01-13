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
        bool notStraight = (readings.RightTrigger || readings.LeftTrigger);

        if (readings.Stuck) {
            SetAction(new Unstick());
        }
        else if (notStraight && lastAction->Type() == MovementType::RotateClockwise) {
            SetAction(new Rotate45clockwise());
        }
        else if (notStraight && (lastAction->Type() == MovementType::RotateCounterClockwise || readings.LeftTrigger)) {
            SetAction(new Rotate45CounterClockwise());
        }
        else if (readings.RightTrigger) {
            SetAction(new Rotate45clockwise());
        }
        else {
            SetAction(new ForwardFullPower());
        }

        delete eyes;
    };