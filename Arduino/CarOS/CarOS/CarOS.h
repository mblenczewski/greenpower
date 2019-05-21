// CarOS.h

#ifndef _CAROS_h
#define _CAROS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "inputs.h"

// The behaviour to constantly run until the Arduino runs out of power.
int loop_();

// The main function, ran once during startup.
int main();

template<typename T>
void increment_by_1_debug(T& ptr)
{
	Serial.print("Counter value incremented, was ");
	Serial.print(ptr++);
	Serial.print(" and is now ");
	Serial.println(ptr);
}

inline void pwm_reader_debug()
{
	if (pwm_input_instance != nullptr)
	{
		Serial.print("PWM detected rising edge; pulse width: ");
		Serial.print(pwm_input_instance->read_pin());
		Serial.println(" microseconds.");
	}
}

#endif
