#include "Behavior.hpp"
#include "BoredomSensor.hpp"
#include "MovementType.hpp"

    void Boredom::Init() {
         subsume = false;
     };

    void Boredom::Run(Movement* lastAction) {
        BoredomSensor* borer = new BoredomSensor();
        if (lastAction->Type() == MovementType::DoDance) {
            Serial.println("We just danced");
        }
        subsume = lastAction->Type() != MovementType::DoDance && borer->Sense();
        if (subsume) {
            SetAction(new Dance());
        }

        delete borer;
    };