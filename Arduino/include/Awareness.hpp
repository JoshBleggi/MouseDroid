#ifndef AWARENESS_H
#define AWARENESS_H

#include "Movement.hpp"


class Awareness {
    public:
        Awareness();
        static Movement* CurrentMovement;
};

class AwarenessManager {
    public:
        static Awareness* getAwareness();

    private:
        static Awareness* instance;
        AwarenessManager();
};

#endif