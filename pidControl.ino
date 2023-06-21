#include "pidControl.h"

pidControl controller(2, 3, 5, 6, 7, 8);

void setup() {
  Serial.begin(9600);
  
  
  
}

void loop() {
  controller.goToAngle(1, 100, 1, 0, 0);
  delay(1000);
}
