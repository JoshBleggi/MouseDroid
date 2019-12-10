#include "Behavior.hpp"

Behavior::Behavior() { }

Behavior::~Behavior() { }

bool Behavior::DoesSubsume()
{
	return subsume;
}

Movement* Behavior::GetAction()
{
	return action;
}