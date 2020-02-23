#include "Behavior.hpp"
#include "EyeSensor.hpp"
#include "LaserReadingStruct.hpp"
#include "MovementType.hpp"

short lastMeasurementLeft = 0;
short lastMeasurementRight = 0;
long leftStateChangeTime = 0;
long rightStateChangeTime = 0;

Motivate::Motivate() {
  leftStateChangeTime = millis();
  rightStateChangeTime = millis();
 }

Motivate::~Motivate() {
    delete &leftStateChangeTime;
    delete &rightStateChangeTime;
 }

void Motivate::Init() {
    subsume = true;
};

void Motivate::Run(Movement* lastAction) {
    EyeSensor* eyes = new EyeSensor();
    LaserReadingStruct readings = eyes->Sense();
    bool rightTrigger = readings.RightReading > 0 && readings.RightReading < TRIGGER_MAX;
    bool leftTrigger = readings.LeftReading > 0 && readings.LeftReading < TRIGGER_MAX;
    bool notStraight = (rightTrigger || leftTrigger);

    if (isRobotStuck(readings.LeftReading, readings.RightReading, MAX_READING)) {
        SetAction(new Unstick());
    }
    else if (notStraight && lastAction->Type() == MovementType::RotateClockwise) {
        SetAction(new Rotate45clockwise());
    }
    else if (notStraight && (lastAction->Type() == MovementType::RotateCounterClockwise || leftTrigger)) {
        SetAction(new Rotate45CounterClockwise());
    }
    else if (rightTrigger) {
        SetAction(new Rotate45clockwise());
    }
    else {
        SetAction(new ForwardFullPower());
    }

    delete eyes;
};

bool Motivate::isRobotStuck(short &leftSensorReading, short &rightSensorReading, short MaxReading) {
  if (isDifInThreshold(leftSensorReading, lastMeasurementLeft, leftStateChangeTime, MaxReading) || 
      isDifInThreshold(rightSensorReading, lastMeasurementRight, rightStateChangeTime, MaxReading)) {
    return true;
  }
  return false;
}

bool Motivate::isDifInThreshold(short &reading, short &lastMeasurement, long &lastChangeTime, short maxReading) {
  const byte threshold = 30;
  short dif = reading - lastMeasurement;
  if (dif < 0) {
    dif = dif * -1;
  }
  Serial.println("Dif: " + String(dif) + " Last Change Time: " + String(lastChangeTime));
  if (dif < threshold && reading <= maxReading && ((millis() - lastChangeTime) > MILLIS_BEFORE_CHANGE)) {
    Serial.println("STUCK STUCK STUCK STUCK STUCK");
    return true;
  }
  if (dif > threshold || reading >= maxReading){
    lastMeasurement = reading;
    lastChangeTime = millis();
  }
  //Serial.println("Not stuck");
  return false;
}