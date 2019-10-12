#include "Drive.h"
#include "Sense.h"
#include "Movement.cpp"

void selectDrive(SensorState triggeredState);

void Drive::selectDrive(SensorState triggeredState) {
  Serial.println("Triggered State: " + String(triggeredState));
  switch (triggeredState)
  {
    case SensorState::STUCK: 
      ReverseFullPower reverse;
      reverse.Execute();
      delay(500);
      Rotate45clockwise rotateRight;
      rotateRight.Execute();
      delay(500);
      break;
    case SensorState::NONE: 
      Rotate45clockwise rotateRight;
      rotateRight.Execute();
      break;
    default:
      ForwardFullPower forward;
      forward.Execute();
  }
}

