// CarOS.h

#ifndef _CAROS_h
#define _CAROS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// The behaviour to constantly run until the Arduino runs out of power.
int loop_();

// The main function, ran once during startup.
int main();

#endif
