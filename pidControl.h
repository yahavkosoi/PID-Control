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
    double previousTime;
    double currentTime;
    double deltaTime;
    
    double out;
    int tempOut;
    int processValue;

    int speedR;
    int speedL;

    double yaw;

    void calibrateMPU();
    
  public:
    pidControl(int inR1, int inR2, int enR, int inL1, int inL2, int enL);
    void begin();
    void rightMotor(int speed);
    void leftMotor(int speed);
    void stopMoving();
    void move(int rightSpeed, int leftSpeed);
    double PIDcalc(double PV, int sp, double Kp, double Ki, double Kd);
    int getYaw();
    void goToAngle(int deg, int speed, double Kp, double Ki, double Kd);
    void steer(int deg, int speed, double Kp, double Ki, double Kd);
};

#endif