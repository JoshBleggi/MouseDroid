#include "Drive.h"
#include "Sense.h"

bool InManeuver = false;

void SetMotorsReverse();
void SetMotorsForward();
void ReverseFullPower();
void ForwardFullPower();
void Rotate45clockwise();
void Rotate45CounterClockwise();
void selectDrive(SensorState triggeredState);

void Drive::SetMotorsReverse()  {
  digitalWrite(MOTOR_RIGHT_DIR, HIGH);
  digitalWrite(MOTOR_LEFT_DIR, HIGH);
  Serial.println("Reversing");
}

void Drive::SetMotorsForward()  {
  digitalWrite(MOTOR_RIGHT_DIR, LOW);
  digitalWrite(MOTOR_LEFT_DIR, LOW);
  Serial.println("Forward");
}

void Drive::ReverseFullPower()  {
  SetMotorsReverse();
  analogWrite(MOTOR_RIGHT_PWM, 35);
  analogWrite(MOTOR_LEFT_PWM, 45);
  InManeuver = true;
}

void Drive::ForwardFullPower()  {
  SetMotorsForward();  
  analogWrite(MOTOR_RIGHT_PWM, 210);
  analogWrite(MOTOR_LEFT_PWM, 220);
  InManeuver = false;
}

void Drive::Rotate45clockwise() {
  SetMotorsForward();  
  analogWrite(MOTOR_RIGHT_PWM, 40);
  analogWrite(MOTOR_LEFT_PWM, 220);
  InManeuver = true;
  Serial.println("Turning");
}

void Drive::Rotate45CounterClockwise() {
  SetMotorsForward();  
  analogWrite(MOTOR_RIGHT_PWM, 220);
  analogWrite(MOTOR_LEFT_PWM, 40);
  InManeuver = true;
  Serial.println("Turning");
}

void Drive::selectDrive(SensorState triggeredState) {
  Serial.println("Triggered State: " + String(triggeredState));
  if (triggeredState == SensorState::STUCK) {
    ReverseFullPower();
    delay(500);
    Rotate45clockwise();
    delay(500);
  }
  if (triggeredState != SensorState::NONE) {
    Rotate45clockwise();
  }
  else {
    ForwardFullPower();
  }
}
