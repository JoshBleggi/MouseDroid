#include "BoredomSensor.hpp"

bool BoredomSensor::Sense() {
    short random = rand() % 1000;
    if((random) < 5) {
        Serial.println(random);
        return true;
    }
    return false;
}