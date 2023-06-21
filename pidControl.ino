#include "pidControl.h"

void setup() {
  Serial.begin(9600);

  pidControl controller(2, 3, 5, 6, 7, 8);
  controller.rightMotor(200);
}

void loop() {
  // put your main code here, to run repeatedly:

}
