#include "pidControl.h"
#include "clicli.h"
pidControl controller(2, 3, 5, 6, 7, 8);

clicli mycli(controller);

int setPoint = 50;
double pv = 0.1;
double output;

void setup() {
  mycli.begin();
}

void loop() {
  mycli.run();
  // Serial.print(pv);
  // Serial.print(" ");
  // Serial.println(setPoint);
  output = controller.PIDcalc(pv, setPoint, 1, 0, 1);
  pv += output;
  delay(10);
  
}
