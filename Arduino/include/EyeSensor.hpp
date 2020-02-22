#ifndef EYESENSE_H
#define EYESENSE_H

#include <Wire.h>
#include <VL53L0X.h>
#include "Constants.cpp"
#include "LaserReadingStruct.hpp"

extern const short MILLIS_BEFORE_CHANGE;

extern short lastMeasurementLeft;
extern short lastMeasurementRight;
extern long leftStateChangeTime;
extern long rightStateChangeTime;
// objects for the vl53l0x
extern VL53L0X lox1;
extern VL53L0X lox2;

class EyeSensor {
    public:
        EyeSensor();
        LaserReadingStruct Sense();
    private:
        LaserReadingStruct getState(short leftSensorReading, short rightSensorReading);
        bool isRobotStuck(short &leftSensorReading, short &rightSensorReading, short rightMaxReading);
        bool isDifInThreshold(short &reading, short &lastMeasurement, long &lastChangeTime, short maxReading);
};

#endif