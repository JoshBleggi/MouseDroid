#include "Arduino.h"
#include "Awareness.hpp"

Awareness* AwarenessManager::instance = nullptr;

Awareness* AwarenessManager::getAwareness()
{
    if (instance == nullptr)
    {
        instance = new Awareness();
    }

    return instance;
}

AwarenessManager::AwarenessManager() {}
AwarenessManager::~AwarenessManager() {
    free(AwarenessManager::instance);
}

Movement* Awareness::CurrentMovement = nullptr;

Awareness::Awareness() {}

void Awareness::SetMovement(Movement* newMovement) {
    free(Awareness::CurrentMovement);
    Awareness::CurrentMovement = newMovement;
}

void Awareness::ExecuteMovement() {
    Awareness::CurrentMovement->Execute();
}
