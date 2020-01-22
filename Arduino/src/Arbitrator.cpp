#include "Arbitrator.hpp"
#include "freeMemory.cpp"

Arbitrator::Arbitrator() {
	action = new ForwardFullPower();
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
		Serial.println("Remaining Memory: " + String(freeMemory()));
		behaviors[i]->Run();
		Serial.println("Remaining Memory: " + String(freeMemory()));
		if (behaviors[i]->DoesSubsume()) {
			action = behaviors[i]->GetAction();
			Serial.println("Level " + String(i));
			break;
		}
	}
}

Movement* Arbitrator::GetAction()
{
	Serial.println("Remaining Memory: " + String(freeMemory()));
	return action;
}