//MIT LICENSE
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PULSE_WIDTH       500
#define MAX_PULSE_WIDTH       2500
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();

void setup() {
  Wire.begin();
  Serial.begin(9600);

  driver.begin();
  driver.setPWMFreq(FREQUENCY);

  setServo(0, 90);
  setServo(1, 90);
  setServo(2, 90);
  setServo(3, 90);
  setServo(4, 90);
  setServo(5, 90);
  setServo(6, 90);
  setServo(7, 90);

  calibrate();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void calibrate() {
  int calibrationValues[8];
  String input = "";
  Serial.println("Enter angle for servo 1 till correct: ");
  while(input != "n"){
    while (Serial.available() == 0) {}
    input = Serial.readString();
    if (input != "n"){
      setServo(0, input.toInt());
      calibrationValues[0] = input.toInt();
    }
  }
  input = "";
  Serial.println("Enter angle for servo 2 till correct: ");
  while(input != "n"){
    while (Serial.available() == 0) {}
    input = Serial.readString();
    if (input != "n"){
      setServo(1, input.toInt());
      calibrationValues[1] = input.toInt();
    }
  }
  input = "";
  Serial.println("Enter angle for servo 3 till correct: ");
  while(input != "n"){
    while (Serial.available() == 0) {}
    input = Serial.readString();
    if (input != "n"){
      setServo(2, input.toInt());
      calibrationValues[2] = input.toInt();
    }
  }
  input = "";
  Serial.println("Enter angle for servo 4 till correct: ");
  while(input != "n"){
    while (Serial.available() == 0) {}
    input = Serial.readString();
    if (input != "n"){
      setServo(3, input.toInt());
      calibrationValues[3] = input.toInt();
    }
  }
  input = "";
  Serial.println("Enter angle for servo 5 till correct: ");
  while(input != "n"){
    while (Serial.available() == 0) {}
    input = Serial.readString();
    if (input != "n"){
      setServo(4, input.toInt());
      calibrationValues[4] = input.toInt();
    }
  }
  input = "";
  Serial.println("Enter angle for servo 6 till correct: ");
  while(input != "n"){
    while (Serial.available() == 0) {}
    input = Serial.readString();
    if (input != "n"){
      setServo(5, input.toInt());
      calibrationValues[5] = input.toInt();
    }
  }
  input = "";
  Serial.println("Enter angle for servo 7 till correct: ");
  while(input != "n"){
    while (Serial.available() == 0) {}
    input = Serial.readString();
    if (input != "n"){
      setServo(6, input.toInt());
      calibrationValues[6] = input.toInt();
    }
  }
  input = "";
  Serial.println("Enter angle for servo 8 till correct: ");
  while(input != "n"){
    while (Serial.available() == 0) {}
    input = Serial.readString();
    if (input != "n"){
      setServo(7, input.toInt());
      calibrationValues[7] = input.toInt();
    }
  }
  Serial.println("Save (y/n): ");
  while (Serial.available() == 0) {}
  input = Serial.readString();
  if (input == "y"){
      EEPROM.put(0, calibrationValues[0]);
      Serial.println(calibrationValues[0]);
      EEPROM.put(2, calibrationValues[1]);
      EEPROM.put(4, calibrationValues[2]);
      EEPROM.put(6, calibrationValues[3]);
      EEPROM.put(8, calibrationValues[4]);
      EEPROM.put(10, calibrationValues[5]);
      EEPROM.put(12, calibrationValues[6]);
      EEPROM.put(14, calibrationValues[7]);
      Serial.println("Saved!");
      Serial.println("Values:");
      int haha = 0;
      EEPROM.get(0, haha);
      Serial.println("S1: " + haha);
  }
}

void setServo(int num, int angle){
  driver.setPWM(num, 0, pulseWidth(angle));
}

int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}