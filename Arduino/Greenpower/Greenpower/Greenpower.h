// Greenpower.h

#ifndef _GREENPOWER_h
#define _GREENPOWER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#endif

// Stores all the possible components and their respective pins (that they affect).
enum class Pins : uint8_t
{
	Ammeter = A0,
	Voltmeter = A1,
	Throttle = A2,
	Radio = 1,
	SpeedController = 2,
	Tachometer = 22,

	// The button that needs to be pressed to increment a variable by 1.
	ButtonAdd1 = 23,
	// The button that needs to be pressed to increment a variable by 10.
	ButtonAdd10 = 24,
	// The button that needs to be pressed to decrement a variable by 1.
	ButtonTake1 = 25,
	// The button that needs to be pressed to decrement a variable by 10.
	ButtonTake10 = 26,
	ButtonRaceMode = 27,
	ButtonOvertakeMode = 28,
};