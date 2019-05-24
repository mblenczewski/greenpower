// CarOS.h

#ifndef _CAROS_h
#define _CAROS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_GFX.h>
#include <eRCaGuy_Timer2_Counter.h>
#include <MCUFRIEND_kbv.h>
#include <PID_v1.h>
#include <Streaming.h>

#include "builtin_button_callbacks.h"
#include "CarOS.h"
#include "inputs.h"
#include "miscellaneous.h"
#include "models.h"
#include "outputs.h"

// Global counter used to track elapsed time to within 1 microsecond.
extern eRCaGuy_Timer2_Counter accurate_microsecond_timer;

// Global tft display used for displaying any information graphically.
extern MCUFRIEND_kbv tft_display;

// Pointer to the global tft display.
constexpr MCUFRIEND_kbv* TFT_DISPLAY_PTR = &tft_display;

// The refresh rate for the main loop, in hertz.
constexpr long REFRESH_RATE_HZ = 100;

// The amount of microseconds per loop call.
constexpr long REFRESH_RATE_MICROS = 100 * REFRESH_RATE_HZ;

// Microseconds for event loop - currently 100Hz
constexpr long EVENT_TICK_MICROS = REFRESH_RATE_MICROS;

// The behaviour to constantly run until the Arduino runs out of power.
int loop_();

// The main function, ran once during startup.
int main();

template<typename T>
void increment_by_1_debug(T& ptr)
{
	Serial << "Counter value incremented. Was: " << ptr++ << ", Is: " << ptr << endl;
}

inline void pwm_reader_debug()
{
#if 0 // Eek - not good in an ISR
	if (pwm_input_instance != nullptr)
	{
		Serial << "PWM detected rising edge; pulse width: " << pwm_input_instance->read_pin() << " microseconds" << endl;
	}
#endif
}

// Generates an RPM value from the passed PWM width (in microseconds).
inline unsigned long rpm_from_pwm(const unsigned long pwm)
{
	return 1000000L * 60 / pwm;
}

#endif
