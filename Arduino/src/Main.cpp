#include "Constants.hpp"
#include "Drive.hpp"
#include "Movement.hpp"
#include "Sensor.hpp"

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
// set the pins to shutdown
#define SHT_VL 13

Sensor sensor;
Drive driver;

void setSensorIDs();
void initializeMotorPins();

void loop() {
  SensorState triggeredState = sensor.read_dual_sensors();
  
  delay(100);
  driver.selectDrive(triggeredState);
}

//Setup section
void setup() {
  Serial.begin(115200);

  sensor = Sensor();
  driver = Drive();

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
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);
  
  pinMode(10, OUTPUT);
  
  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  
  pinMode(12, OUTPUT);
}
