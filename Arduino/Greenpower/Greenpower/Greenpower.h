// Greenpower.h

#ifndef _GREENPOWER_h
#define _GREENPOWER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Stores all the possible components and their respective pins (that they affect).
enum class Pins : byte
{
	// The ammeter; on analog pin 0.
	Ammeter = A0,

	// The voltmeter; on analog pin 1.
	Voltmeter = A1,

	// The throttle; on analog pin 2.
	Throttle = A2,

	// The RF module; on pin 1.
	Radio = 1,

	// The speed controller; on pin 2.
	SpeedController = 2,

	// The tachometer; on pin 22.
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
#endif