// CarOS.h

#ifndef _CAROS_h
#define _CAROS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "inputs.h"

// The refresh rate for the main loop, in hertz.
constexpr long REFRESH_RATE_HZ = 100;

// The amount of microseconds per loop call.
constexpr long REFRESH_RATE_MICROS = 100 * REFRESH_RATE_HZ;

static_assert(REFRESH_RATE_MICROS == 10000L, "Refresh rate doesnt convert from Hz to microseconds properly.");

// Microseconds for event loop - currently 100Hz
constexpr long EVENT_TICK_MICROS = REFRESH_RATE_MICROS;

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
#if 0 // Eek - not good in an ISR
	if (pwm_input_instance != nullptr)
	{
		Serial.print("PWM detected rising edge; pulse width: ");
		Serial.print(pwm_input_instance->read_pin());
		Serial.println(" microseconds.");
	}
#endif
}

// Generates an RPM value from the passed PWM width (in microseconds).
inline unsigned long rpm_from_pwm(const unsigned long pwm)
{
	return 1000000L * 60 / pwm;
}

#endif
