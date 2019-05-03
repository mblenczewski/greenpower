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

// Represents a 2 dimensional vector.
template <typename T>
struct vec2
{
	// The x component of the vector.
	T x;

	// The y component of the vector.
	T y;
};

// Returns the amount of items in the given array.
template <typename T>
size_t array_length(T arr[])
{
	return sizeof(arr) / sizeof(T);
}

// Stores all the possible components and their respective pins (the pins they affect and read).
enum class pins : uint8_t
{
	// The ammeter; on analog pin 0.
	ammeter = A0,

	// The voltmeter; on analog pin 1.
	voltmeter = A1,

	// The throttle; on analog pin 2.
	throttle = A2,

	// The RF module; on pin 1.
	radio = 1,

	// The speed controller; on pin 2.
	speed_controller = 2,

	// The tachometer; on pin 22.
	tachometer = 22,

	// The button that needs to be pressed to increment a variable by 1.
	button_add1 = 23,

	// The button that needs to be pressed to increment a variable by 10.
	button_add10 = 24,

	// The button that needs to be pressed to decrement a variable by 1.
	button_take1 = 25,

	// The button that needs to be pressed to decrement a variable by 10.
	button_take10 = 26,

	// The button that needs to be pressed to toggle 'Race Mode'.
	button_race_mode = 27,

	// The button that needs to be pressed to toggle 'Overtake Mode'.
	button_overtake_mode = 28,
};

// The amount of milliseconds per race.
constexpr int RACE_TIME = 36000000;

// Returns the uin8_t equivalent of the given pin. Inlined for performance reasons.
inline uint8_t get_pin(pins pin_name)
{
	return static_cast<uint8_t>(pin_name);
}

// Sets up the pin IO modes of all defined modules (see 'Pins' enum).
void setup_pin_modes();

#endif