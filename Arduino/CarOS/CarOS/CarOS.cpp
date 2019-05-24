//
//
//

#include <Adafruit_GFX.h>
#include <eRCaGuy_Timer2_Counter.h>
#include <MCUFRIEND_kbv.h>
#include <Streaming.h>

#include "builtin_button_callbacks.h"
#include "CarOS.h"
#include "inputs.h"
#include "miscellaneous.h"
#include "models.h"
#include "outputs.h"

eRCaGuy_Timer2_Counter accurate_microsecond_timer{};

MCUFRIEND_kbv tft_display{};

display car_display{ TFT_DISPLAY_PTR };

// Records idle time during event loop in microseconds
long idle_time = 0;

int press_counter = 0;
button<int> incrementer{ A1, &press_counter, &increment_by_1_debug, &null_func };

pwm_input pwm_reader{ 21, nullptr, RISING }; // on an arduino mega, pin 21 has interrupt functionality

input* inputs[] = { &incrementer, &pwm_reader };

output* outputs[1] = {};

// Used to periodically print out the RPM, instead of every loop_() call.
int loop_counter = 0;

int loop_()
{
	// read inputs and update their state; buttons will invoke callback functions when updated
	for (input* input_ : inputs)
	{
		input_->read_pin();
	}

	if (loop_counter++ % 20 == 0)
	{
		Serial << "RPM: " << rpm_from_pwm(pwm_reader.read_pwm()) << ", Idle time: " << idle_time;
	}

	for (output* output_ : outputs)
	{
		output_->write_pin(0);
	}

	return 0;
}

int main()
{
	init();

	// Setup
	Serial.begin(115200);
	Serial.println("Hello, World!");

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	accurate_microsecond_timer.setup();

#ifdef _DEBUG
	lcd_debug(Serial, car_display);
#endif

	// Event loop
	unsigned long tick = micros();

	for (;;)
	{
		const int ret_code = loop_();

		if (ret_code != 0)
		{
			Serial << "Non zero error code returned by loop_(): " << ret_code;
#ifdef _DEBUG
			// When running in release mode, as the code on the race day will be, we want to continue
			// running the code regardless of any errors. In debug mode any error should cause a break
			// in the program for debugging.
			break;
#endif
		}

		// When should next loop run?
		tick += EVENT_TICK_MICROS;

		// Record time left (or overrun if -ve)
		idle_time = static_cast<long>(tick - micros());

		// Wait until next loop (cast to signed to cope with wraparound)
		//
		// XXX If power becomes an issue, use a timer interrupt for event tick, and 'sleep' instruction here
		//
		while (static_cast<long>(micros() - tick) < 0)
		{
		}
	}

	Serial.println("Goodbye, World!");
	Serial.flush();
	return 0;
}