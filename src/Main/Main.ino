//MIT LICENSE
//Created by Harry Heywood

#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "MPU.h"
#include "LegControls.h"

int updateInterval = 4;
int lastUpdate = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  setupLegs();
}

void loop() {
  //Set all servos to 90 degrees
  for (int i = 0; i < 8; i++) {
    setServo(i,0);
  }
  while (Serial.available() == 0) {}
  String input = Serial.readString();
  if (input.startsWith("control")){
    control();
  } else if (input.startsWith("calibrate")) {
    calibrate();
  }
}

void control() {
  //Controller stuff
  while (true) {
    while (Serial.available() == 0) {}
    String input = Serial.readString();
    if (input == "fwd") {

    } else if (input == "rgt") {

    } else if (input == "bck") {

    } else if (input == "lft") {

    } else if (input == "menu") {
      break;
    }
  }
}

// This function calibrates ther servos of the robot, it uses communication over serial by the user to set the angles of the servos
// Format:
// sX - s defines you are selecting the servo, X is the int (0-7) that selects which servo you want to calibrate
// aX - a defines you are setting an angle value, X is an int that defines the angle to set it to
// c - completes the calibration and saves the values to EEPROM
// x - cancels the calibration
void calibrate() {
  //Set default values
  int calibrationValues[] = {90,90,90,90,90,90,90,90};
  int servo = 0;
  String input = "";
  bool cal = false;
  //Set servos to default values
  for (int i = 0; i < 8; i++) {
    setServoAbsolute(i,calibrationValues[i]);
  }
  while(!cal){
    //Wait for message
    while (Serial.available() == 0) {}
    input = Serial.readString();
    //Get type from first character of string
    char type = input[0];
    //Remove first character to get integer value
    input.remove(0,1);
    if (type == 's') {
      //Set selected servo it input int
      servo = input.toInt();
    } else if (type == 'a') {
      //Adjust selected servo's angle to input int
      setServoAbsolute(servo, input.toInt());
      calibrationValues[servo] = input.toInt();
    } else if (type == 'c') {
      //Finish calibration
      cal = true;
    } else if (type == 'x') {
      //Finish calibration
      break;
    }
  }
  if (cal) {
    //Save values to EEPROM
    EEPROM.put(0, calibrationValues[0]);
    EEPROM.put(2, calibrationValues[1]);
    EEPROM.put(4, calibrationValues[2]);
    EEPROM.put(6, calibrationValues[3]);
    EEPROM.put(8, calibrationValues[4]);
    EEPROM.put(10, calibrationValues[5]);
    EEPROM.put(12, calibrationValues[6]);
    EEPROM.put(14, calibrationValues[7]);
    //Flash LED 3 times to signal calibration complete
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
  }
}