#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "Movement.hpp"

class Behavior {
protected:
	bool subsume;
    Movement* action;

public:
	Behavior();
	virtual ~Behavior();

	virtual void Init() = 0;
	virtual void Run() = 0;

	bool DoesSubsume();
	Movement* GetAction();
};

class Motivate: public Behavior {
  public:
    void Init();
    void Run();  
};

#endif