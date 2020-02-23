#include "EyeSensor.hpp"

// objects for the vl53l0x
VL53L0X lox1;
VL53L0X lox2;

LaserReadingStruct Sense();
LaserReadingStruct getState(short leftSensorReading, short rightSensorReading);

EyeSensor::EyeSensor() { }

LaserReadingStruct EyeSensor::Sense() {
  long leftSensorReading, rightSensorReading;
  Serial.println("About to read distance");

  leftSensorReading = lox1.readRangeSingleMillimeters();
  // print sensor one reading
  Serial.println("Left Sensor: " + String(leftSensorReading));

  rightSensorReading = lox2.readRangeSingleMillimeters();

  // print sensor two reading
  Serial.println("Right Sensor: " + String(rightSensorReading));

  return LaserReadingStruct {
    .LeftReading = leftSensorReading,
    .RightReading = rightSensorReading
  };
}
