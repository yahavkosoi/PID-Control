#ifndef PIDCONTROL_H
#define PIDCONTROL_H

#include "Arduino.h"

class pidControl{
  private:
    int rMP1;
    int rMP2;
    int rMPP;

    int lMP1;
    int lMP2;
    int lMPP;

    double integral;
    double derivative;
    double error;
    double previousError;
    
    double out;

    
  public:
    pidControl(int inR1, int inR2, int enR, int inL1, int inL2, int enL);
    void rightMotor(int speed);
    double PIDcalc(double PV, int sp, double Kp, double Ki, double Kd);
    
};

#endif