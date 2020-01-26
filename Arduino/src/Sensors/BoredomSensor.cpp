#include "BoredomSensor.hpp"

bool BoredomSensor::Sense() {
    if(random(10000) <= 5) {
        return true;
    }
    return false;
}