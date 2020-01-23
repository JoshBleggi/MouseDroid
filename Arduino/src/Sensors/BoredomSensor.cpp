#include "BoredomSensor.hpp"

bool BoredomSensor::Sense() {
    if(random(10000) <= 1) {
        return true;
    }
    return false;
}