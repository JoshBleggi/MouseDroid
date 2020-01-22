#include "Behavior.hpp"
#include "BoredomSensor.hpp"
#include "MovementType.hpp"

    void Boredom::Init() {
         subsume = false;
         SetAction(new Dance());
     };

    void Boredom::Run() {
        BoredomSensor* borer = new BoredomSensor();

        subsume = action->Type() != MovementType::DoDance && borer->Sense();
        if (subsume) {
            SetAction(new Dance());
        }

        delete borer;
    };