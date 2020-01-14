#include "Behavior.hpp"
#include "BoredomSensor.hpp"
#include "MovementType.hpp"

    void Boredom::Init() {
         subsume = false;
         action = new ForwardFullPower();
     };

    void Boredom::Run(Movement* lastAction) {
        BoredomSensor* borer = new BoredomSensor();

        subsume = lastAction->Type() != MovementType::DoDance && borer->Sense();

        delete borer;
    };