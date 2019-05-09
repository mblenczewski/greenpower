// Synchronisation.h

#ifndef _SYNCHRONISATION_h
#define _SYNCHRONISATION_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

constexpr float REFRESH_RATE = 60.0;

constexpr float REFRESH_SECONDS = 1 / REFRESH_RATE;

constexpr float REFRESH_MILLISECONDS = REFRESH_SECONDS * 1000;

constexpr float REFRESH_MICROSECONDS = REFRESH_MILLISECONDS * 1000;

class sync
{
private:

	// Caches the refresh rates and associated delays as unsigned numbers.
	const unsigned REFRESH_MILLISEC_UNSIGNED = static_cast<unsigned>(REFRESH_MILLISECONDS);

	// Caches the refresh rates and associated delays as unsigned numbers.
	const unsigned REFRESH_MICROSEC_UNSIGNED = static_cast<unsigned>(REFRESH_MICROSECONDS);

	// The elapsed microseconds at the start of a new iteration.
	static unsigned start_microseconds;

	// The elapsed microseconds at the end of a new iteration.
	static unsigned end_microseconds;

	// The microsecond delta between the start and end of an iteration.
	static unsigned long delta_time;

	// We hide the constructor, emulating a static class.
	sync() = default;

protected:
	// Delays the arduino to maintain a constant refresh rate.
	inline static void complete_tick();

public:
	// Starts a new iteration. Should be called at the beginning of _loop(), before any other code.
	static void start_iteration();

	// Ends an iteration. Should be called at the end of _loop(), after any other code.
	static void end_iteration();
};

#endif
