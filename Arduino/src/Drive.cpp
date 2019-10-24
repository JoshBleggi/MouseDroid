#include "Drive.hpp"

void Drive::selectDrive(SensorState triggeredState) {
  Serial.println("Triggered State: " + String(triggeredState));
  switch (triggeredState)
  {
    case SensorState::STUCK: {
      Move(new ReverseFullPower(), 500);
      Move(new Rotate45clockwise(), 500);
      break;
    }
    case SensorState::NONE: {
      Move(new ForwardFullPower());
      break;
    }
    case SensorState::LEFT: {
      Move(new Rotate45CounterClockwise());
      break;
    }
    case SensorState::BORED: {
      Move(new Dance());
      break;
    }
    default: {
      Move(new Rotate45clockwise(), 500);
    }
  }
}

void Drive::Move(Movement* movement, short executeTime) {
    Move(movement);
    delay(executeTime);
}

void Drive::Move(Movement* movement) {
    movement->Execute();
}
