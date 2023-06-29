#include "pidControl.h"
#include "clicli.h"
pidControl controller(2, 3, 5, 6, 7, 8);

clicli mycli;

void setup() {
  Serial.begin(9600);
  mycli.begin();
}

void loop() {
  mycli.run();
  //controller.steer(50, 100, 1, 0, 0);
  //delay(1000);
}
