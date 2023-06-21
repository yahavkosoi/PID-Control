#include "pidControl.h"

int rMP1;
int rMP2;
int rMPP;

int lMP1;
int lMP2;
int lMPP;

double integral = 0;
double derivative;
double error;
double previousError = 0;

double out;
int tempOut;
int processValue;

int speedR;
int speedL;

pidControl::pidControl(int inR1, int inR2, int enR, int inL1, int inL2, int enL){
  rMP1 = inR1;
  rMP2 = inR2;
  rMPP = enR;

  lMP1 = inL1;
  lMP2 = inL2;
  lMPP = enL;

  pinMode(rMP1, OUTPUT);
  pinMode(rMP2, OUTPUT);
  pinMode(rMPP, OUTPUT);

  pinMode(lMP1, OUTPUT);
  pinMode(lMP2, OUTPUT);
  pinMode(lMPP, OUTPUT);
}

void pidControl::rightMotor(int speed){
  analogWrite(rMPP, abs(speed));
  if (speed>0) {
    digitalWrite(rMP1, LOW);
    digitalWrite(rMP2, HIGH);
  }
  else {
    digitalWrite(rMP1, HIGH);
    digitalWrite(rMP2, LOW);
  }
}

void pidControl::leftMotor(int speed) {
  analogWrite(lMPP, abs(speed));
  if (speed>0) {
    digitalWrite(lMP1, HIGH);
    digitalWrite(lMP2, LOW);
  }
  else {
    digitalWrite(lMP1, LOW);
    digitalWrite(lMP2, HIGH);
  }
}

void pidControl::move(int rightSpeed, int leftSpeed) {
  rightMotor(rightSpeed);
  leftMotor(leftSpeed);
}

void pidControl::stopMoving(){
  digitalWrite(lMP1, LOW);
  digitalWrite(lMP2, LOW);
  digitalWrite(rMP1, LOW);
  digitalWrite(rMP2, LOW);
}

double pidControl::PIDcalc(double PV, int sp, double Kp, double Ki, double Kd){
  error = sp - PV;
  integral += error;
  derivative = error - previousError;

  out = error*Kp + integral*Ki + derivative*Ki;

  previousError = error;

  return out;
}

void pidControl::goToAngle(int deg, int speed, double Kp, double Ki, double Kd){
  processValue = getYaw();
  while (processValue != deg) {
    processValue = getYaw();

    tempOut = PIDcalc(processValue, deg, Kp, Ki, Kd);

    speedR = (speed + tempOut) * -1;
    speedL = (speed + tempOut);

    if (speedR > 255) {
      speedR = 255;
    }

    else if (speedR < -255) {
      speedR = -255;
    }

    if (speedL > 255) {
      speedL = 255;
    }

    else if (speedL < -255) {
      speedL = -255;
    }

    Serial.print(speedR);
    Serial.print(" <- speedR, speedL -> ");
    Serial.println(speedL);
    move(speedR, speedL);
  }
}

int pidControl::getYaw(){
  return 0;
}