// Car.h

#ifndef _CAR_h
#define _CAR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Display.h"
#include "Greenpower.h"

// Stores the current state of the car.
class CarState
{
private:
	// The display we will be writing to and drawing on to show the cars internal state.
	Display display;

	// The maximum value for the car's throttle.
	const int THROTTLE_CAP = 255;

	// The reccomended value for the car's throttle.
	int reccomended_throttle = 30;

	// The current value for the car's throttle.
	int throttle = reccomended_throttle;

	// The distance travelled by the car so far.
	int distance_travelled = 0;

	// The current amount of power in the battery (P=IV). Initialised as the battery's capacity.
	int battery_level = BATTERY_CAPACITY;

	// The current battery percentage, between 0 and 1.
	float battery_percentage = 1;

	// Whether the car is in race mode.
	bool in_race_mode = false;

	// Whether the car is in overtake mode.
	bool in_overtake_mode = false;

public:
	// Initialises a new instance of the CarState class.
	CarState();

	// Updates the car's internal state.
	void next_tick();

	// Updates the screen with the car's current internal state.
	void update_screen();
};

#endif
