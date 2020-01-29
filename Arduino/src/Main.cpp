#include "Arduino.h"
#include "Arbitrator.hpp"
#include "Constants.hpp"
#include "EyeSensor.hpp"

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x29
// set the pins to shutdown
#define SHT_LOX1 13
#define SHT_LOX2 8

Arbitrator* thinkingCap;

void setSensorIDs();
void initializeMotorPins();

void loop() {
  thinkingCap->Run();
  thinkingCap->GetAction()->Execute();
}

//Setup section
void setup() {
  Serial.println("Hello World");
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) { delay(1); }
  
  Serial.println("Starting...");
  setSensorIDs();
  Serial.println("Sensors initialized...");

  initializeMotorPins();
  Serial.println("Motors initialized...");

  thinkingCap = new Arbitrator();
  thinkingCap->SetBehavior(new Boredom(), 0);
  thinkingCap->SetBehavior(new Motivate(), 1);
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

  Wire.begin();
 
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);

  Serial.println(F("Activating Left Eye and deactivating Right Eye"));
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX1, LOW);

  delay(10);

  Serial.println(F("Initing Left Eye"));
  lox1.setAddress(LOX1_ADDRESS);
  if(!lox1.init()) {
    Serial.println(F("Failed to boot Left Eye"));
    while(1);
  }
  
  Serial.println(F("SUCCESS Left Eye"));

  Serial.println(F("Activating Right Eye"));
  digitalWrite(SHT_LOX1, HIGH);
  Serial.println(F("Deactivating Left Eye"));
  digitalWrite(SHT_LOX2, LOW);
  Serial.println(F("Initing Right Eye"));

  delay(10);

  lox2.setAddress(LOX2_ADDRESS);
  if(!lox2.init()) {
    Serial.println(F("Failed to boot Right Eye"));
    while(1);
  }
  Serial.println(F("SUCCESS Right Eye"));
}

void initializeMotorPins() {
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);
  
  pinMode(10, OUTPUT);
  
  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  
  pinMode(12, OUTPUT);
}
