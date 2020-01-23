#include "Behavior.hpp"
#include "BoredomSensor.hpp"
#include "MovementType.hpp"

    void Boredom::Init() {
         subsume = false;
     };

    void Boredom::Run() {
        BoredomSensor* borer = new BoredomSensor();
        if (action->Type() == MovementType::DoDance) {
            Serial.println("We just danced");
        }
        subsume = action->Type() != MovementType::DoDance;// && borer->Sense();
        if (subsume) {
            SetAction(new Dance());
        }

        delete borer;
    };