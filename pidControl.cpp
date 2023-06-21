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
  Serial.println("Actually works.");
  if (speed>0) {
    digitalWrite(rMP1, LOW);
    digitalWrite(rMP2, HIGH);
  }
  else {
    digitalWrite(rMP1, HIGH);
    digitalWrite(rMP2, LOW);
  }
}

double pidControl::PIDcalc(double PV, int sp, double Kp, double Ki, double Kd){
  error = sp - PV;
  integral += error;
  derivative = error - previousError;

  out = error*Kp + integral*Ki + derivative*Ki;

  previousError = error;

  return out;
}