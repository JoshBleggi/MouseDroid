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

Movement* Awareness::CurrentMovement = nullptr;

Awareness::Awareness() {}
