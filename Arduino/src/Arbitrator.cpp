#include "Arbitrator.hpp"

Arbitrator::Arbitrator() { }

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
		behaviors[i]->Run();
		if (behaviors[i]->DoesSubsume()) {
			action = behaviors[i]->GetAction();
			Serial.print("Level " + i);
			break;
		}
	}
}

Movement* Arbitrator::GetAction()
{
	return action;
}