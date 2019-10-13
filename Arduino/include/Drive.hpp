#ifndef DRIVE_H
#define DRIVE_H

#include "Movement.hpp"
#include "Sense.h"
#include "SensorState.h"

class Drive {
    public:
        void selectDrive(SensorState triggeredState);
    
    private:
        void Move(Movement* movement, short executeTime);
        void Move(Movement* movement);
};

#endif