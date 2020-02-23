#ifndef BEHAVIOR_H
#define BEHAVIOR_H

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
	public:
		Motivate();
		~Motivate();
		void Init();
		void Run(Movement* lastAction); 

	private:
        bool isRobotStuck(short &leftSensorReading, short &rightSensorReading, short rightMaxReading);
        bool isDifInThreshold(short &reading, short &lastMeasurement, long &lastChangeTime, short maxReading); 
};

class Boredom: public Behavior {
	public:
		void Init();
		void Run(Movement* lastAction);  
};

#endif