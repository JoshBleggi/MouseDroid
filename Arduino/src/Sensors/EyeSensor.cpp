#include "EyeSensor.hpp"

const short MILLIS_BEFORE_CHANGE = 2500;

short lastMeasurementLeft = 0;
short lastMeasurementRight = 0;
long leftStateChangeTime = 0;
long rightStateChangeTime = 0;
// objects for the vl53l0x
VL53L0X lox1;
VL53L0X lox2;

LaserReadingStruct Sense();
LaserReadingStruct getState(short leftSensorReading, short rightSensorReading);
bool isRobotStuck(short &leftSensorReading, short leftMaxReading, short &rightSensorReading, short rightMaxReading);
bool isDifInThreshold(short &reading, short &lastMeasurement, long &lastChangeTime, short maxReading);

EyeSensor::EyeSensor() {
  leftStateChangeTime = millis();
  rightStateChangeTime = millis();
}

LaserReadingStruct EyeSensor::Sense() {
  long leftSensorReading, rightSensorReading;
  Serial.println("About to read distance");

  leftSensorReading = lox1.readRangeSingleMillimeters();
  // print sensor one reading
  Serial.println("Left Sensor: " + String(leftSensorReading));

  rightSensorReading = lox2.readRangeSingleMillimeters();

  // print sensor two reading
  Serial.println("Right Sensor: " + String(rightSensorReading));

  return getState(leftSensorReading, rightSensorReading);
}

LaserReadingStruct EyeSensor::getState(short leftSensorReading, short rightSensorReading) {
  LaserReadingStruct readings;
  readings.Stuck = isRobotStuck(leftSensorReading, rightSensorReading, MAX_READING);
  readings.LeftTrigger = leftSensorReading > 0 && leftSensorReading < TRIGGER_MAX;
  readings.RightTrigger = rightSensorReading > 0 && rightSensorReading < TRIGGER_MAX;

  return readings;
}

bool EyeSensor::isRobotStuck(short &leftSensorReading, short &rightSensorReading, short MaxReading) {
  if (isDifInThreshold(leftSensorReading, lastMeasurementLeft, leftStateChangeTime, MaxReading) || 
      isDifInThreshold(rightSensorReading, lastMeasurementRight, rightStateChangeTime, MaxReading)) {
    return true;
  }
  return false;
}

bool EyeSensor::isDifInThreshold(short &reading, short &lastMeasurement, long &lastChangeTime, short maxReading) {
  const byte threshold = 30;
  short dif = reading - lastMeasurement;
  if (dif < 0) {
    dif = dif * -1;
  }
  // Serial.println("Dif: " + String(dif) + " Last Change Time: " + String(lastChangeTime));
  if (dif < threshold && reading <= maxReading && ((millis() - lastChangeTime) > MILLIS_BEFORE_CHANGE)) {
    // Serial.println("STUCK STUCK STUCK STUCK STUCK");
    return true;
  }
  if (dif > threshold || reading >= maxReading){
    lastMeasurement = reading;
    lastChangeTime = millis();
  }
  //Serial.println("Not stuck");
  return false;
}
