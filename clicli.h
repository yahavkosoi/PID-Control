#ifndef CLICLI_H
#define CLICLI_H
#include "pidControl.h"

 class clicli {

  public:
   clicli(pidControl &pidcontrol) ;
   void begin();   //must be called from  void setup()
   void run();   //must be called from  void loop()

  private:
   pidControl &controller;
   int number;

 };
#endif 