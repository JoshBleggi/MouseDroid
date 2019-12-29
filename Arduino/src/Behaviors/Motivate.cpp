#include "Behavior.hpp"
#include "EyeSensor.hpp"
#include "LaserReadingStruct.hpp"

    
    
    Motivate::Motivate() { }

    Motivate::~Motivate() { }

    void Motivate::Init() {
        subsume = true;
        action = new ForwardFullPower();
    };

    void Motivate::Run() {
        EyeSensor* eyes = new EyeSensor();
        LaserReadingStruct readings = eyes->Sense();
        delete action;

        if (readings.Stuck) {
            action = new Unstick();
        }
        else if (readings.RightTrigger) {
            action = new Rotate45clockwise();
        }
        else if (readings.LeftTrigger) {
            action = new Rotate45CounterClockwise();
        }
        else {
            action = new ForwardFullPower();
        }

        delete eyes;
    };