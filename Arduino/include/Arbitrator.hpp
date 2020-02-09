#ifndef ARBITRATOR_H
#define ARBITRATOR_H

#include "Arduino.h"
#include "Behavior.hpp"
#include "Movement.hpp"

class Arbitrator {

private:
	Behavior* behaviors[2] = { };
	Movement* action;

public:
	Arbitrator();
	virtual ~Arbitrator();

	void SetBehavior(Behavior* behavior, int level);
	void Run();
	Movement* GetAction();
};

#endif