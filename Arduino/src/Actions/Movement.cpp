#include "Movement.hpp"

Movement::Movement() { }

Movement::~Movement() { }

void Movement::Execute() { }

MovementType Movement::Type() { return MovementType::None; }

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

MovementType ForwardFullPower::Type() {
    return MovementType::Forward;
}

void ReverseFullPower::Execute() {
    Movement::SetMotorsReverse();
    analogWrite(MOTOR_RIGHT_PWM, 35);
    analogWrite(MOTOR_LEFT_PWM, 45);
}

MovementType ReverseFullPower::Type() {
    return MovementType::Reverse;
}

void Rotate45clockwise::Execute() {
    Movement::SetMotorsForward();  
    analogWrite(MOTOR_RIGHT_PWM, 40);
    analogWrite(MOTOR_LEFT_PWM, 220);
    Serial.println("Turning right");
}

MovementType Rotate45clockwise::Type() {
    return MovementType::RotateClockwise;
}

void Rotate45CounterClockwise::Execute() {
    Movement::SetMotorsForward();  
    analogWrite(MOTOR_RIGHT_PWM, 220);
    analogWrite(MOTOR_LEFT_PWM, 40);
    Serial.println("Turning left");
}

MovementType Rotate45CounterClockwise::Type() {
    return MovementType::RotateCounterClockwise;
}

void Unstick::Execute() {
    (new ReverseFullPower())->Execute();  
    delay(500);
    (new Rotate45clockwise())->Execute();  
    delay(500);
    Serial.println("Getting Unstuck");
}

MovementType Unstick::Type() {
    return MovementType::GetUnstuck;
}

void Dance::Execute() {
    Serial.println("Dancing");
    SetMotorsForward();  
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
    SetMotorsReverse(); 
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
    SetMotorsForward();  
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
    SetMotorsReverse(); 
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
}

MovementType Dance::Type() {
    return MovementType::DoDance;
}