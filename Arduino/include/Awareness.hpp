#ifndef AWARENESS_H
#define AWARENESS_H

#include "Movement.hpp"


class Awareness {
    public:
        Awareness();
        static void SetMovement(Movement*);
        static void ExecuteMovement();

    private:
        static Movement* CurrentMovement;
};

class AwarenessManager {
    public:
        static Awareness* getAwareness();

    private:
        AwarenessManager();
        ~AwarenessManager();
        static Awareness* instance;
};

#endif