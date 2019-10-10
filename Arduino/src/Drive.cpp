#include "Drive.h"
#include "Sense.h"
#include "Movement.cpp"

void selectDrive(SensorState triggeredState);

void Drive::selectDrive(SensorState triggeredState) {
  Serial.println("Triggered State: " + String(triggeredState));
  if (triggeredState == SensorState::STUCK) {
    ReverseFullPower action;
    action.Execute();
    delay(500);
    Rotate45clockwise action2;
    action2.Execute();
    delay(500);
  }
  if (triggeredState != SensorState::NONE) {
    Rotate45clockwise action;
    action.Execute();
  }
  else {
    ForwardFullPower action;
    action.Execute();
  }
}
