//MIT LICENSE
//Created by Harry Heywood
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "MPU.h"

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

int updateInterval = 4;
int lastUpdate = 0;

int walkPhase = 0;

//ANGLE SETUP
//DOWN IS 0
//REAR IS -90
//FRONT IS 90

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  driver.begin();
  driver.setPWMFreq(FREQUENCY);
  loadEEPROM();
}

void loop() {
  if (millis() - updateInterval >= lastUpdate)
    update();
}

//Function called at a fixed rate to allow slower movement of servos
void update(){
  bool flag = false;
  lastUpdate = millis();
  for (int i = 0; i<=7; i++){
    if(currentPosition[i] < target[i]){
      flag = true;
      setServo(i, currentPosition[i] + 1);
    } else if (currentPosition[i] > target[i]){
      flag = true;
      setServo(i, currentPosition[i] - 1);
    }
  }
  if (flag)
    atTarget = false;
  else
    atTarget = true;
}

//Stores the angles needed to reach the input coordinates in the IK array
void inverseKinematics(float x, float y){
  if ((x*x) + (y*y) > 4225){ //4225 is a little less than leg length squared
    Serial.println("ERROR: Input IK distance is unreachable");
    digitalWrite(LED_BUILTIN, HIGH);
    return;
  }
  float L = sqrt((-y*-y)+(x*x));
  float Q1 = atan((x/y) + acos(((33.4 * 33.4) - (34.2 * 34.2) - (L * L)) / (-2 * L * 34.2)));
  float Q2 = acos(((L * L) - (33.4 * 33.4) - (34.2 * 34.2)) / (-2 * 34.2 * 33.4));
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
    target[0] = kneeAngle;
    target[1] = hipAngle;
  } else if (leg == "FR") {
    target[7] = kneeAngle;
    target[6] = hipAngle;
  } else if (leg == "RL") {
    target[3] = kneeAngle;
    target[2] = hipAngle;
  } else if (leg == "RR") {
    target[4] = kneeAngle;
    target[5] = hipAngle;
  }
}

void setServo(int num, int angle){
  currentPosition[num] = angle;
  angle *= -1;
  int finalAngle;
  switch (num){
    case 0:
      finalAngle = servoMid[num] - angle;
      break;
    case 1:
      finalAngle = angle + servoMid[num];
      break;
    case 2:
      finalAngle = angle + servoMid[num];
      break;
    case 3:
      finalAngle = servoMid[num] - angle;
      break;
    case 4:
      finalAngle = angle + servoMid[num];
      break;
    case 5:
      finalAngle = servoMid[num] - angle;
      break;
    case 6:
      finalAngle = servoMid[num] - angle;
      break;
    case 7:
      finalAngle = angle + servoMid[num];
      break;
  }
  driver.setPWM(num, 0, pulseWidth(finalAngle));
}

int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}