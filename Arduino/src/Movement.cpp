#include "Movement.hpp"

Movement::Movement() {
    Movement::InManeuver = false;
}

void Movement::SetMotorsReverse()  {
    digitalWrite(MOTOR_RIGHT_DIR, HIGH);
    digitalWrite(MOTOR_LEFT_DIR, HIGH);
    Serial.println("Reversing");
}

void Movement::SetMotorsForward()  {
    digitalWrite(MOTOR_RIGHT_DIR, LOW);
    digitalWrite(MOTOR_LEFT_DIR, LOW);
    Serial.println("Forward");
}

void ForwardFullPower::Execute() {
    Movement::SetMotorsForward();  
    analogWrite(MOTOR_RIGHT_PWM, 210);
    analogWrite(MOTOR_LEFT_PWM, 220);
}

void ReverseFullPower::Execute() {
    Movement::SetMotorsReverse();
    analogWrite(MOTOR_RIGHT_PWM, 35);
    analogWrite(MOTOR_LEFT_PWM, 45);
}


void Rotate45clockwise::Execute() {
    Movement::SetMotorsForward();  
    analogWrite(MOTOR_RIGHT_PWM, 40);
    analogWrite(MOTOR_LEFT_PWM, 220);
    Movement::InManeuver = true;
    Serial.println("Turning");
}


void Rotate45CounterClockwise::Execute() {
    Movement::SetMotorsForward();  
    analogWrite(MOTOR_RIGHT_PWM, 220);
    analogWrite(MOTOR_LEFT_PWM, 40);
    Movement::InManeuver = true;
    Serial.println("Turning");
}