#include "Adafruit_VL6180X.h"
#include "Adafruit_VL53L0X.h"

enum SensorState {
  LEFT,
  RIGHT,
  BOTH,
  NONE
};

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30

#define MOTOR_RIGHT 9
#define MOTOR_LEFT 11
// set the pins to shutdown
#define SHT_VL 13

const long MILLIS_BEFORE_CHANGE = 5000;

long stateChangeTime = 0;
SensorState LastState = SensorState::NONE;

// objects for the vl53l0x
Adafruit_VL6180X vl = Adafruit_VL6180X();
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;

void loop() {
  SensorState triggeredState = read_dual_sensors();
  delay(100);
  selectDrive(triggeredState);
}

//Sensor Section
SensorState read_dual_sensors() {
  const int VL_MAX = 255, LOX_MAX = 800 ;//8190;
  int leftSensor, rightSensor;
  lox1.getSingleRangingMeasurement(&measure1); // pass in 'true' to get debug data printout!

  leftSensor = measure1.RangeMilliMeter;
  rightSensor = vl.readRange();
  bool leftTrigger = leftSensor > 0 && leftSensor < LOX_MAX, rightTrigger = rightSensor > 0 && rightSensor < VL_MAX; 
  // print sensor one reading
  Serial.print("1: " + String(leftSensor) + " Triggered - " + leftTrigger);
  
  Serial.print(" ");

  // print sensor two reading
  Serial.print("2: " + String(rightSensor) + " Triggered - " + rightTrigger);  
  Serial.println();

  return getState(leftTrigger, rightTrigger);
}

void updateSensorState(SensorState newState) {
  if (newState != LastState) {
    LastState = newState;
    stateChangeTime = millis();
  }
}

//Drive Section
void selectDrive(SensorState triggeredState) {
  if (triggeredState != LastState) {
    updateSensorState(triggeredState);
    
    if (triggeredState != SensorState::NONE) {
      rotate45clockwise();
    }
    else {
      moveForwards();
    }
  }
  else if ((stateChangeTime - MILLIS_BEFORE_CHANGE) > 0) {
    if (triggeredState != SensorState::NONE) {
      reverse();
    }
  }
}

void rotate45clockwise() {
  analogWrite(MOTOR_RIGHT, 40);
  analogWrite(MOTOR_LEFT, 200);
}

void moveForwards() {
  analogWrite(MOTOR_RIGHT, 210);
  analogWrite(MOTOR_LEFT, 220);
}

void reverse()  {
  analogWrite(MOTOR_RIGHT, -220);
  analogWrite(MOTOR_LEFT, -210);
}

//Setup section
void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) { delay(1); }

  pinMode(SHT_VL, OUTPUT);
  
  Serial.println("Starting...");
  setSensorIDs();
  initializeMotorPins();
}

void setSensorIDs() {
  /*
    Reset all sensors by setting all of their XSHUT pins low for delay(10), then set all XSHUT high to bring out of reset
    Keep sensor #1 awake by keeping XSHUT pin high
    Put all other sensors into shutdown by pulling XSHUT pins low
    Initialize sensor #1 with lox.begin(new_i2c_address) Pick any number but 0x29 and it must be under 0x7F. Going with 0x30 to 0x3F is probably OK.
    Keep sensor #1 awake, and now bring sensor #2 out of reset by setting its XSHUT pin high.
    Initialize sensor #2 with lox.begin(new_i2c_address) Pick any number but 0x29 and whatever you set the first sensor to
 */
 
  Serial.println(F("Activating LOX1 and reseting LOX2"));
  digitalWrite(SHT_VL, LOW);

  Serial.println(F("Initing LOX1"));
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  
  Serial.println(F("SUCCESS LOX1"));

  Serial.println(F("Activating VL"));
  digitalWrite(SHT_VL, HIGH);
  Serial.println(F("Initing VL"));

  if(!vl.begin()) {
    Serial.println(F("Failed to boot VL"));
    while(1);
  }
  Serial.println(F("SUCCESS VL"));
}

void initializeMotorPins() {
  pinMode(MOTOR_RIGHT, OUTPUT);
  
  pinMode(10, OUTPUT);
  
  pinMode(MOTOR_LEFT, OUTPUT);
  
  pinMode(12, OUTPUT);
}

//Helper Section
SensorState getState(bool leftTrigger, bool rightTrigger) {
  if (leftTrigger && rightTrigger) {
    return SensorState::BOTH;
  }
  else if (leftTrigger) {
    return SensorState::LEFT;
  }
  else if (rightTrigger) {
    return SensorState::RIGHT;
  }
  else {
    return SensorState::NONE;
  }
}
