#include "Arbitrator.hpp"

Arbitrator::Arbitrator() {
	action = new Movement();
	Serial.println("Set first action");
 }

Arbitrator::~Arbitrator() { }

void Arbitrator::SetBehavior(Behavior* behavior, int level)
{
	behaviors[level] = behavior;
	behavior->Init();
}

void Arbitrator::Run()
{
	int numberOfBehaviors = sizeof(behaviors) / sizeof(behaviors[0]);
	// iterate over all behaviors starting from the level 0.
	for (int i = 0; i < numberOfBehaviors; i++)
	{
		behaviors[i]->Run(action);
		if (behaviors[i]->DoesSubsume()) {
			action = behaviors[i]->GetAction();
			Serial.println("Level " + String(i));
			break;
		}
	}
}

Movement* Arbitrator::GetAction()
{
	return action;
}