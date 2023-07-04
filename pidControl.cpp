#include "pidControl.h"

int rMP1; // rightMotorPin1.
int rMP2; // rightMotorPin2.
int rMPP; // rightMotorPowerPin.

int lMP1; // leftMotorPin1.
int lMP2; // leftMotorPin2.
int lMPP; // leftMotorPowerPin.

// define variables for PIDcalc().
double integral = 0;
double derivative;
double error;
double previousError = 0;
double previousTime = millis();
double currentTime = millis();
double deltaTime;
double out;

// define variables for goToAngle.
double tempOut;
double processValue;
int speedR;
int speedL;

pidControl::pidControl(int inR1, int inR2, int enR, int inL1, int inL2, int enL){
  // right motor pins.
  rMP1 = inR1;
  rMP2 = inR2;
  rMPP = enR;

  // left motor pins.
  lMP1 = inL1;
  lMP2 = inL2;
  lMPP = enL;

  // initialize right motor pins.
  pinMode(rMP1, OUTPUT);
  pinMode(rMP2, OUTPUT);
  pinMode(rMPP, OUTPUT);

  // intialize left motor pins.
  pinMode(lMP1, OUTPUT);
  pinMode(lMP2, OUTPUT);
  pinMode(lMPP, OUTPUT);
}

// spins right motor at (speed).
void pidControl::rightMotor(int speed){
  // change motor speed to (speed).
  analogWrite(rMPP, abs(speed));
  // if speed > 0 turn forward.
  if (speed>0) {
    digitalWrite(rMP1, LOW);
    digitalWrite(rMP2, HIGH);
  }
  // else turn backward.
  else {
    digitalWrite(rMP1, HIGH);
    digitalWrite(rMP2, LOW);
  }
}

// spins left motor at (speed).
void pidControl::leftMotor(int speed) {
  // change motor speed to (speed).
  analogWrite(lMPP, abs(speed));
  // if speed > 0 turn forward.
  if (speed>0) {
    digitalWrite(lMP1, HIGH);
    digitalWrite(lMP2, LOW);
  }
  // else turn backward.
  else {
    digitalWrite(lMP1, LOW);
    digitalWrite(lMP2, HIGH);
  }
}

// turn both motors at speeds (rightSpeed, leftSpeed).
void pidControl::move(int rightSpeed, int leftSpeed) {
  rightMotor(rightSpeed);
  leftMotor(leftSpeed);
  Serial.print(rightSpeed);
  Serial.print(" | ")
  Serial.println(leftSpeed);
}

// stop motors.
void pidControl::stopMoving(){
  digitalWrite(lMP1, LOW);
  digitalWrite(lMP2, LOW);
  digitalWrite(rMP1, LOW);
  digitalWrite(rMP2, LOW);
}

// calculate PID output.
double pidControl::PIDcalc(double PV, int sp, double Kp, double Ki, double Kd){
  // set current time to elapsed time in seconds.
  currentTime = millis()/1000.0;

  // set delateTime to the change of time in seconds since the last iteration.
  deltaTime = currentTime-previousTime;
  if (deltaTime == 0) {
    deltaTime = 0.01;
  }
  // set error to set_point - process_value.
  error = sp - PV;
  // add error to integral.
  integral += error * deltaTime;
  if (integral > 255 || integral < -255) {integral = 0;}
  // set derivative to ∆error/∆time.
  derivative = (error - previousError)/deltaTime;
  if (derivative > 255 || derivative < -255) {derivative = 0;}

  // multiple each part of PID by Kp, Ki, Kd.
  out = error*Kp + integral*Ki + derivative*Kd;

  // set previous error to current error.
  previousError = error;
  // set previous time to elapsed time in seconds.
  previousTime = millis()/1000.0; 

  // Serial.println(derivative);

  // test prints.
  // Serial.print("integral: ");
  // Serial.print(integral);
  // Serial.print(" | derivative: ");
  // Serial.print(derivative);
  // Serial.print(" | error: ");
  // Serial.println(error);

  return out;
}

// go to angle using PID.
void pidControl::goToAngle(int deg, int speed, double Kp, double Ki, double Kd){
  // reset variables used in other functions.
  integral = 0;
  previousError = 0;

  // set process value to current yaw angle.
  processValue = getYaw();

  // repeat until current yaw angle == deg.
  while (processValue != deg) {
    // set process value to current yaw angle.
    processValue = getYaw();

    // set tempOut to PIDcalc output.
    tempOut = PIDcalc(processValue, deg, Kp, Ki, Kd);

    // set motor speeds to be opposite of each other.
    speedR = (speed + tempOut) * -1;
    speedL = (speed + tempOut);

    // cant have a speed over 255.
    if (speedR > 255) {
      speedR = 255;
    }

    // cant have a speed less than -255.
    else if (speedR < -255) {
      speedR = -255;
    }

    // cant have a speed over 255.
    if (speedL > 255) {
      speedL = 255;
    }
    
    // cant have a speed less than -255.
    else if (speedL < -255) {
      speedL = -255;
    }
    // for testing purposes print the speed of each motor.
    Serial.print(speedR);
    Serial.print(" <- speedR, speedL -> ");
    Serial.println(speedL);

    // move both motors at their speed.
    move(speedR, speedL);
  }
}

// drives at an angle (deg) while correcting itself.
void pidControl::steer(int deg, int speed, double Kp, double Ki, double Kd) {
  // set processValue to current yaw angle.
  processValue = getYaw();

  // set tempOut to PIDcalc output.
  tempOut = PIDcalc(processValue, deg, Kp, Ki, Kd);

  // set the motors' speeds to speed + out and speed - out.
  speedR = speed - tempOut;
  speedL = speed + tempOut;

  // cant have speed over 255.
  if (speedR > 255) {
    speedR = 255;
  }

  // cant have speed less than -255.
  else if (speedR < -255) {
    speedR = -255;
  }

  // cant have speed over 255.
  if (speedL > 255) {
    speedL = 255;
  }

  // cant have speed less than -255.
  else if (speedL < -255) {
    speedL = -255;
  }

  // for testing purposes print the speed of each motor.
    // Serial.print(speedR);
    // Serial.print(" <- speedR, speedL -> ");
    // Serial.println(speedL);

  // move motors at the correct speed to correct the error.
  move(speedR, speedL);
}

// get current yaw angle.
int pidControl::getYaw(){
  // for testing return yaw angle of 0˚.
  return 0;
}