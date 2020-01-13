#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "EyeSensor.hpp"
#include "Movement.hpp"

class Behavior {
protected:
	bool subsume;
    Movement* action;

	void SetAction(Movement* newAction);

public:
	Behavior();
	virtual ~Behavior();

	virtual void Init() = 0;
	virtual void Run(Movement* lastAction) = 0;

	bool DoesSubsume();
	Movement* GetAction();
};

class Motivate: public Behavior {
	private:
	EyeSensor* eyes;

	public:
		Motivate();
		~Motivate();
		void Init();
		void Run(Movement* lastAction);  
};

#endif