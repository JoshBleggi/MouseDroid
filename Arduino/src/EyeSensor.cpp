#include "Sensor.hpp"

const short MILLIS_BEFORE_CHANGE = 2500;

short lastMeasurementLeft = 0;
short lastMeasurementRight = 0;
long leftStateChangeTime = 0;
long rightStateChangeTime = 0;
// objects for the vl53l0x
Adafruit_VL6180X vl = Adafruit_VL6180X();
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();

Movement* Sense();
Movement* getState(short leftSensorReading, short rightSensorReading);
bool isRobotStuck(short &leftSensorReading, short leftMaxReading, short &rightSensorReading, short rightMaxReading);
bool isDifInThreshold(short &reading, short &lastMeasurement, long &lastChangeTime, short maxReading);

Movement* EyeSensor::Sense() {
  VL53L0X_RangingMeasurementData_t measure1;
  short leftSensorReading, rightSensorReading;
  lox1.getSingleRangingMeasurement(&measure1); // pass in 'true' to get debug data printout!

  leftSensorReading = (short)measure1.RangeMilliMeter;
  rightSensorReading = (short)vl.readRange();
  // print sensor one reading
  Serial.print("Left Sensor: " + String(leftSensorReading));
  
  Serial.print(" ");

  // print sensor two reading
  Serial.print("Right Sensor: " + String(rightSensorReading));  
  Serial.println();

  return getState(leftSensorReading, rightSensorReading);
}

Movement* EyeSensor::getState(short leftSensorReading, short rightSensorReading) {
  const short LEFT_TRIGGER_MAX = 650, RIGHT_TRIGGER_MAX = 255;
  const short LEFT_MAX_READING = 8190, RIGHT_MAX_READING = 255;

  if (isRobotStuck(leftSensorReading, LEFT_MAX_READING, rightSensorReading, RIGHT_MAX_READING)) {
    return new Unstick();
  }
  
  bool leftTrigger = leftSensorReading > 0 && leftSensorReading < LEFT_TRIGGER_MAX, rightTrigger = rightSensorReading > 0 && rightSensorReading < RIGHT_TRIGGER_MAX;
  if (leftTrigger && rightTrigger) {
    return new Rotate45clockwise();
  }
   if (leftTrigger) {
    return  new Rotate45CounterClockwise();
  }
  if (rightTrigger) {
    return new Rotate45clockwise();
  }
  return new ForwardFullPower();
}

bool EyeSensor::isRobotStuck(short &leftSensorReading, short leftMaxReading, short &rightSensorReading, short rightMaxReading) {
  if (isDifInThreshold(leftSensorReading, lastMeasurementLeft, leftStateChangeTime, leftMaxReading) || 
      isDifInThreshold(rightSensorReading, lastMeasurementRight, leftStateChangeTime, rightMaxReading)) {
    return true;
  }
  return false;
}

bool EyeSensor::isDifInThreshold(short &reading, short &lastMeasurement, long lastChangeTime, short maxReading) {
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
  Serial.println("Not stuck");
  return false;
}
