#include "Behavior.hpp"
#include "EyeSensor.hpp"
#include "LaserReadingStruct.hpp"

class Motivate: public Behavior {
    void Motivate::Init() {
        subsume = true;
    };

    void Motivate::Run() {
        EyeSensor* eyes = new EyeSensor();
        LaserReadingStruct readings = eyes->Sense();

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
    };
};