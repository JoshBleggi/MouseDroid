#include "Arduino.h"
#include "Constants.h"
#include "SensorState.h"

class Movement {
    public:
        virtual void Execute();
    
    protected:
        bool InManeuver = false;

        void SetMotorsReverse()  {
            digitalWrite(MOTOR_RIGHT_DIR, HIGH);
            digitalWrite(MOTOR_LEFT_DIR, HIGH);
            Serial.println("Reversing");
        }

        void SetMotorsForward()  {
            digitalWrite(MOTOR_RIGHT_DIR, LOW);
            digitalWrite(MOTOR_LEFT_DIR, LOW);
            Serial.println("Forward");
        }
};

class ForwardFullPower: Movement {
    public:
        void Execute() {
            SetMotorsForward();  
            analogWrite(MOTOR_RIGHT_PWM, 210);
            analogWrite(MOTOR_LEFT_PWM, 220);
        };
};

class ReverseFullPower: Movement {
    public:
        void Execute() {
            SetMotorsReverse();
            analogWrite(MOTOR_RIGHT_PWM, 35);
            analogWrite(MOTOR_LEFT_PWM, 45);
        };
};

class Rotate45clockwise: Movement {
    public:
        void Execute() {
            SetMotorsForward();  
            analogWrite(MOTOR_RIGHT_PWM, 40);
            analogWrite(MOTOR_LEFT_PWM, 220);
            InManeuver = true;
            Serial.println("Turning");
        };
};

class Rotate45CounterClockwise: Movement {
    public:
        void Execute() {
            SetMotorsForward();  
            analogWrite(MOTOR_RIGHT_PWM, 220);
            analogWrite(MOTOR_LEFT_PWM, 40);
            InManeuver = true;
            Serial.println("Turning");
        };
};