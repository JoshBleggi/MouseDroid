#include "Arbitrator.hpp"

Arbitrator::Arbitrator() { }

Arbitrator::~Arbitrator() {
}

void Arbitrator::addBehavior(Behavior* behavior)
{
	behaviors.push_back(behavior);
	behavior->init();
}

void MyArbitrator::run()
{
	action.turnCommand = 0;
	action.forwardCommand = 0;
	// iterate over all behaviors starting from the level 0.
	for (int i = 0; i < behaviors.size(); i++)
	{
		behaviors[i]->run();
		if (behaviors[i]->doesSubsume()) {
			action = behaviors[i]->getAction();
			Serial.Print("Level " + i);
			break;
		}
	}
}

Action Arbitrator::GetAction()
{
	return action;
}