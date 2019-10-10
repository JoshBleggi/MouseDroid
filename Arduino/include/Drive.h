#ifndef DRIVE_H
#define DRIVE_H

#include "SensorState.h"

class Drive {
    public:
        void selectDrive(SensorState triggeredState);
};

#endif