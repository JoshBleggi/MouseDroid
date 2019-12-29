#include "Arduino.h"
#include "Movement.hpp"

Movement::Movement() {
    Movement::InManeuver = false;
}

Movement::~Movement() { }

void Movement::Execute() { }

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
    Serial.println("Turning right");
}

void Rotate45CounterClockwise::Execute() {
    Movement::SetMotorsForward();  
    analogWrite(MOTOR_RIGHT_PWM, 220);
    analogWrite(MOTOR_LEFT_PWM, 40);
    Movement::InManeuver = true;
    Serial.println("Turning left");
}

Unstick::Unstick() { };

void Unstick::Execute() {
    ReverseFullPower* rev = new ReverseFullPower();
    rev->Execute();  
    delay(500);
    Rotate45clockwise* rot = new Rotate45clockwise();
    rot->Execute();  
    delay(500);
    Serial.println("Getting Unstuck");
}

Dance::Dance() { };

void Dance::Execute() {
    Movement::InManeuver = true;
    Movement::SetMotorsForward();  
    analogWrite(MOTOR_RIGHT_PWM, 110);
    analogWrite(MOTOR_LEFT_PWM, 40);
    delay(100);
    analogWrite(MOTOR_RIGHT_PWM, 40);
    analogWrite(MOTOR_LEFT_PWM, 110);
    delay(100);
    analogWrite(MOTOR_RIGHT_PWM, 110);
    analogWrite(MOTOR_LEFT_PWM, 40);
    delay(100);
    analogWrite(MOTOR_RIGHT_PWM, 40);
    analogWrite(MOTOR_LEFT_PWM, 110);
    delay(100);
    Movement::SetMotorsReverse(); 
    analogWrite(MOTOR_RIGHT_PWM, 40);
    analogWrite(MOTOR_LEFT_PWM, 110);
    delay(100);
    analogWrite(MOTOR_RIGHT_PWM, 110);
    analogWrite(MOTOR_LEFT_PWM, 40);
    delay(100);
    analogWrite(MOTOR_RIGHT_PWM, 40);
    analogWrite(MOTOR_LEFT_PWM, 110);
    delay(100); 
    analogWrite(MOTOR_RIGHT_PWM, 110);
    analogWrite(MOTOR_LEFT_PWM, 40);
    delay(100);    
    Movement::SetMotorsForward();  
    analogWrite(MOTOR_RIGHT_PWM, 110);
    analogWrite(MOTOR_LEFT_PWM, 40);
    delay(100);
    analogWrite(MOTOR_RIGHT_PWM, 40);
    analogWrite(MOTOR_LEFT_PWM, 110);
    delay(100);
    analogWrite(MOTOR_RIGHT_PWM, 110);
    analogWrite(MOTOR_LEFT_PWM, 40);
    delay(100);
    analogWrite(MOTOR_RIGHT_PWM, 40);
    analogWrite(MOTOR_LEFT_PWM, 110);
    delay(100);
    Movement::SetMotorsReverse(); 
    analogWrite(MOTOR_RIGHT_PWM, 40);
    analogWrite(MOTOR_LEFT_PWM, 110);
    delay(100);
    analogWrite(MOTOR_RIGHT_PWM, 110);
    analogWrite(MOTOR_LEFT_PWM, 40);
    delay(100);
    analogWrite(MOTOR_RIGHT_PWM, 40);
    analogWrite(MOTOR_LEFT_PWM, 110);
    delay(100); 
    analogWrite(MOTOR_RIGHT_PWM, 110);
    analogWrite(MOTOR_LEFT_PWM, 40);
    delay(100);
    Serial.println("dancing");
}