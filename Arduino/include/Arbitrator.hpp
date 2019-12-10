#ifndef ARBITRATOR_H
#define ARBITRATOR_H

#include <string>
#include <vector>
#include "Behavior.hpp"
#include "Movement.hpp"

class Arbitrator {

private:
	std::vector<MyBehavior*> behaviors;
	Movement* action;

public:
	Arbitrator();
	virtual ~Arbitrator();

	void AddBehavior(Behavior* behavior);
	void Run();
	Movement* GetAction();
};

#endif