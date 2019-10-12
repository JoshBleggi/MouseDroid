#include "Sense.h"

const short MILLIS_BEFORE_CHANGE = 2500;

short lastMeasurementLeft = 0;
long lastMeasurementRight = 0;
long leftStateChangeTime = 0;
long rightStateChangeTime = 0;
// objects for the vl53l0x
Adafruit_VL6180X vl = Adafruit_VL6180X();
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();

SensorState read_dual_sensors();
SensorState getState(short leftSensorReading, short rightSensorReading);
bool isRobotStuck(short &leftSensorReading, short leftMaxReading, short &rightSensorReading, short rightMaxReading);
bool isDifInThreshold(short &reading, short &lastMeasurement, long &lastChangeTime, short maxReading);

SensorState Sense::read_dual_sensors() {
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

SensorState Sense::getState(short leftSensorReading, short rightSensorReading) {
  const short LEFT_TRIGGER_MAX = 650, RIGHT_TRIGGER_MAX = 255;
  const short LEFT_MAX_READING = 8190, RIGHT_MAX_READING = 255;

  if (isRobotStuck(leftSensorReading, LEFT_MAX_READING, rightSensorReading, RIGHT_MAX_READING)) {
    return SensorState::STUCK;
  }
  
  bool leftTrigger = leftSensorReading > 0 && leftSensorReading < LEFT_TRIGGER_MAX, rightTrigger = rightSensorReading > 0 && rightSensorReading < RIGHT_TRIGGER_MAX;
  if (leftTrigger && rightTrigger) {
    return SensorState::BOTH;
  }
  else if (leftTrigger) {
    return SensorState::LEFT;
  }
  else if (rightTrigger) {
    return SensorState::RIGHT;
  }
  else {
    return SensorState::NONE;
  }
}

bool Sense::isRobotStuck(short &leftSensorReading, short leftMaxReading, short &rightSensorReading, short rightMaxReading) {
  if (isDifInThreshold(leftSensorReading, lastMeasurementLeft, leftStateChangeTime, leftMaxReading) || 
      isDifInThreshold(leftSensorReading, lastMeasurementLeft, leftStateChangeTime, rightMaxReading)) {
    return true;
  }
  return false;
}

bool Sense::isDifInThreshold(short &reading, short &lastMeasurement, long &lastChangeTime, short maxReading) {
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
