#include "Behavior.hpp"

Behavior::Behavior() {
	subsume = false;
	action = nullptr;
 }

Behavior::~Behavior() { }

bool Behavior::DoesSubsume()
{
	return subsume;
}

Movement* Behavior::GetAction()
{
	return action;
}

void Behavior::SetAction(Movement* newAction)
{
	delete action;
	action = newAction;
}