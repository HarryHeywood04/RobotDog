//MIT LICENSE
//Created by Harry Heywood

#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "LegControls.h"

#define MIN_PULSE_WIDTH       500
#define MAX_PULSE_WIDTH       2500
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();

int servoMid[8] = {90, 90, 90, 90, 90, 90, 90, 90};
int currentPosition[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int target[8] = {45, -45, -45, 45, 45, -45, -45, 45};
bool atTarget = false;

int IK[] = {0, 0};


int walkPhase = 0;

//ANGLE SETUP
//DOWN IS 0
//REAR IS -90
//FRONT IS 90

void setupLegs() {
  driver.begin();
  driver.setPWMFreq(FREQUENCY);
  loadEEPROM();
}

// Moves the input leg to the input coordinates
void moveLeg(String leg, float x, float y) {
  inverseKinematics(x,y);
  setLeg(leg, IK[0], IK[1]);
}

//Stores the angles needed to reach the input coordinates in the IK array
void inverseKinematics(float x, float y){
  float L = sqrt((-y*-y)+(x*x));
  float Q1 = atan((x/y) + acos((1115.56 - 1169.64 - (L * L)) / (-2 * L * 34.2)));
  float Q2 = acos(((L * L) - 1115.56 - 1169.64) / -2284.56);
  IK[0] = -Q1 * 57.2958;
  IK[1] = 180-(Q2 * 57.2958);
}

//Loads the calibration values from the EEPROM
void loadEEPROM(){ 
  EEPROM.get(0,servoMid[0]);
  EEPROM.get(2,servoMid[1]);
  EEPROM.get(4,servoMid[2]);
  EEPROM.get(6,servoMid[3]);
  EEPROM.get(8,servoMid[4]);
  EEPROM.get(10,servoMid[5]);
  EEPROM.get(12,servoMid[6]);
  EEPROM.get(14,servoMid[7]);
}

//Sets the input leg to the input angle
void setLeg(String leg, int hipAngle, int kneeAngle){
  atTarget = false;
  if (leg == "FL"){
    setServo(0, kneeAngle);
    setServo(1, hipAngle);
  } else if (leg == "FR") {
    setServo(7, kneeAngle);
    setServo(6, hipAngle);
  } else if (leg == "RL") {
    setServo(3, kneeAngle);
    setServo(2, hipAngle);
  } else if (leg == "RR") {
    setServo(4, kneeAngle);
    setServo(5, hipAngle);
  }
}

void setServo(int num, int angle){
  currentPosition[num] = angle;
  angle *= -1;
  int finalAngle;
  switch (num){
    case 0:
      finalAngle = servoMid[num] - angle - 90;
      break;
    case 1:
      finalAngle = angle + servoMid[num];
      break;
    case 2:
      finalAngle = angle + servoMid[num];
      break;
    case 3:
      finalAngle = servoMid[num] - angle - 90;
      break;
    case 4:
      finalAngle = angle + servoMid[num] + 90;
      break;
    case 5:
      finalAngle = servoMid[num] - angle;
      break;
    case 6:
      finalAngle = servoMid[num] - angle;
      break;
    case 7:
      finalAngle = angle + servoMid[num] + 90;
      break;
  }
  driver.setPWM(num, 0, pulseWidth(finalAngle));
}

void setServoAbsolute(int servo, int angle) {
  driver.setPWM(servo, 0, pulseWidth(angle));
}

int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}