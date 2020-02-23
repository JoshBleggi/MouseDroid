#ifndef EYESENSE_H
#define EYESENSE_H

#include <Wire.h>
#include <VL53L0X.h>
#include "Constants.cpp"
#include "LaserReadingStruct.hpp"

// objects for the vl53l0x
extern VL53L0X lox1;
extern VL53L0X lox2;

class EyeSensor {
    public:
        EyeSensor();
        LaserReadingStruct Sense();
    private:
        LaserReadingStruct getState(short leftSensorReading, short rightSensorReading);
};

#endif