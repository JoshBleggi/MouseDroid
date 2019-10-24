#include "Sensor.hpp"

Movement* BoredomSensor::Sense() {
    short random = rand() % 1000;
    if((random) < 5) {
        Serial.println(random);
        return new Dance();
    }
    return nullptr;
}