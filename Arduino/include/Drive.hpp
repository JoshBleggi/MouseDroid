#ifndef DRIVE_H
#define DRIVE_H

#include "Movement.hpp"
#include "Sensor.hpp"
#include "SensorState.hpp"

class Drive {
    public:
        void selectDrive(SensorState triggeredState);
    
    private:
        void Move(Movement* movement, short executeTime);
        void Move(Movement* movement);
};

#endif