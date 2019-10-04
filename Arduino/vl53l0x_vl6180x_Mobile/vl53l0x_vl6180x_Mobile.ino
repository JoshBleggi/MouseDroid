#include "Adafruit_VL6180X.h"
#include "Adafruit_VL53L0X.h"

enum SensorState {
  LEFT,
  RIGHT,
  BOTH,
  NONE,
  STUCK
};

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30

#define MOTOR_RIGHT_PWM 9
#define MOTOR_RIGHT_DIR 10
#define MOTOR_LEFT_PWM 11
#define MOTOR_LEFT_DIR 12
// set the pins to shutdown
#define SHT_VL 13

const short MILLIS_BEFORE_CHANGE = 2500;
short lastMeasurementLeft = 0;
long lastMeasurementRight = 0;
long leftStateChangeTime = 0;
long rightStateChangeTime = 0;

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
  int leftSensorReading, rightSensorReading;
  lox1.getSingleRangingMeasurement(&measure1); // pass in 'true' to get debug data printout!

  leftSensorReading = measure1.RangeMilliMeter;
  rightSensorReading = vl.readRange();
  // print sensor one reading
  Serial.print("Left Sensor: " + String(leftSensorReading));
  
  Serial.print(" ");

  // print sensor two reading
  Serial.print("Right Sensor: " + String(rightSensorReading));  
  Serial.println();

  return getState(leftSensorReading, rightSensorReading);
}

SensorState getState(short leftSensorReading, short rightSensorReading) {
  const short LEFT_TRIGGER_MAX = 650, RIGHT_TRIGGER_MAX = 255;
  const short LEFT_MAX_READING = 8190, RIGHT_MAX_READING = 255;

  if (isRobotStuck(leftSensorReading, LEFT_MAX_READING, rightSensorReading, RIGHT_MAX_READING)) {
    return SensorState::STUCK;
  }
  
  bool leftTrigger = leftSensorReading > 0 && leftSensorReading < LEFT_TRIGGER_MAX, rightTrigger = rightSensorReading > 0 && rightSensorReading < RIGHT_TRIGGER_MAX;
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

bool isRobotStuck(short &leftSensorReading, short leftMaxReading, short &rightSensorReading, short rightMaxReading) {
  if (isDifInThreshold(leftSensorReading, lastMeasurementLeft, leftStateChangeTime, leftMaxReading) || 
      isDifInThreshold(leftSensorReading, lastMeasurementLeft, leftStateChangeTime, rightMaxReading)) {
    return true;
  }
  return false;
}

bool isDifInThreshold(short &reading, short &lastMeasurement, long &lastChangeTime, short maxReading) {
  const byte threshold = 30;
  short dif = reading - lastMeasurement;
  if (dif < 0) {
    dif = dif * -1;
  }
  Serial.println("Dif: " + String(dif) + " Last Change Time: " + String(lastChangeTime));
  if (dif < threshold && reading < maxReading && ((millis() - lastChangeTime) > MILLIS_BEFORE_CHANGE)) {
    Serial.println("STUCK STUCK STUCK STUCK STUCK");
    return true;
  }
  if (dif > threshold || reading >= maxReading){
    lastMeasurement = reading;
    lastChangeTime = millis();
  }
  Serial.println("Not stuck");
  return false;
}

//Drive Section
void selectDrive(SensorState triggeredState) {
  Serial.println("Triggered State: " + String(triggeredState));
  if (triggeredState == SensorState::STUCK) {
    ReverseFullPower();
    delay(500);
    Rotate45clockwise();
    delay(500);
  }
  if (triggeredState != SensorState::NONE) {
    Rotate45clockwise();
  }
  else {
    ForwardFullPower();
  }
}

void Rotate45clockwise() {
  SetMotorsForward();  
  analogWrite(MOTOR_RIGHT_PWM, 40);
  analogWrite(MOTOR_LEFT_PWM, 220);
  Serial.println("Turning");
}

void SetMotorsReverse()  {
  digitalWrite(MOTOR_RIGHT_DIR, HIGH);
  digitalWrite(MOTOR_LEFT_DIR, HIGH);
  Serial.println("Reversing");
}

void SetMotorsForward()  {
  digitalWrite(MOTOR_RIGHT_DIR, LOW);
  digitalWrite(MOTOR_LEFT_DIR, LOW);
  Serial.println("Forward");
}

void ReverseFullPower()  {
  SetMotorsReverse();
  analogWrite(MOTOR_RIGHT_PWM, 35);
  analogWrite(MOTOR_LEFT_PWM, 45);
}

void ForwardFullPower()  {
  SetMotorsForward();  
  analogWrite(MOTOR_RIGHT_PWM, 210);
  analogWrite(MOTOR_LEFT_PWM, 220);
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

  ForwardFullPower();
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
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);
  
  pinMode(10, OUTPUT);
  
  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  
  pinMode(12, OUTPUT);
}
