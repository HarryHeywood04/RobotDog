//MIT LICENSE
//Created by Harry Heywood

// MAIN FUNCTIONS
void setupLegs();
void moveLeg(String,float,float);

void inverseKinematics(float x, float y);
void loadEEPROM();
void setLeg(String leg, int hipAngle, int kneeAngle);
void setServo(int num, int angle);
void setServoAbsolute(int servo, int angle);
int pulseWidth(int angle);