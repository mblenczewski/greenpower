// Greenpower.h

#ifndef _GREENPOWER_h
#define _GREENPOWER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Internal loop function, that will be repeated until the Arduino is reset.
int _loop();

// Main function that will be executed when the Arduino receives power.
int main();

// Stores all the possible components and their respective pins (the pins they affect and read).
enum class Pins : uint8_t
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

	// The button that needs to be pressed to toggle 'Race Mode'.
	ButtonRaceMode = 27,

	// The button that needs to be pressed to toggle 'Overtake Mode'.
	ButtonOvertakeMode = 28,
};

// The amount of seconds per race.
constexpr int RACE_TIME = 36000;

// Total amount of power in the battery when fully charged (P=IV).
constexpr int BATTERY_CAPACITY = 3400;

// The minimum reading for the throttle controlling pin.
constexpr int THROTTLE_MIN = 0;

// The maximum reading for the throttle controlling pin.
constexpr  int THROTTLE_MAX = 1023;

constexpr int SPEED_CONTROLLER_MAX = 255;

// Returns the uin8_t equivalent of the given pin.
inline uint8_t get_pin(Pins pin_name)
{
	return static_cast<uint8_t>(pin_name);
}

// Sets up the pin IO modes of all defined modules (see 'Pins' enum).
void setup_pin_modes();

#endif