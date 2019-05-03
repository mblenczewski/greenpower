//
//
//

#include "Car.h"
#include "Greenpower.h"

// The elapsed time since the Arduino was powered on.
unsigned long global_elapsed_time_ms = millis();

// Represents the car.
car_state car;

void setup_pin_modes()
{
	pinMode(get_pin(pins::ammeter), INPUT);
	pinMode(get_pin(pins::voltmeter), INPUT);
	pinMode(get_pin(pins::throttle), INPUT);
	pinMode(get_pin(pins::radio), OUTPUT);
	pinMode(get_pin(pins::speed_controller), OUTPUT);
	pinMode(get_pin(pins::tachometer), INPUT);
	pinMode(get_pin(pins::button_add1), INPUT);
	pinMode(get_pin(pins::button_add10), INPUT);
	pinMode(get_pin(pins::button_take1), INPUT);
	pinMode(get_pin(pins::button_take10), INPUT);
	pinMode(get_pin(pins::button_race_mode), INPUT);
	pinMode(get_pin(pins::button_overtake_mode), INPUT);
}

int _loop() {
	// The delta time (in milliseconds) between the last tick and the current one.
	const unsigned long delta_time_ms = global_elapsed_time_ms - millis();

	car.update_buttons();
	car.next_tick(delta_time_ms);
	car.update_screen();

	// Update the global elapsed time (in milliseconds) for the next iteration.
	global_elapsed_time_ms = millis();

	return 0;
}

int main()
{
	// Initialises Arduino stuff, such as serial output and input.
	init();
	Serial.begin(9600);

	// Initialises car stuff, such as pin modes and the RF module.
	setup_pin_modes();

	for (;;)
	{
		// The return code for the next loop iteration; main will break if it is not 0.
		const int return_code = _loop();

		if (!return_code)
		{
			//Serial.println(F("Loop completed successfuly."));
			continue;
		}

		Serial.print(F("Loop failed with error code "));
		Serial.println(return_code, DEC);
		break;
	}

	Serial.flush();
	return 0;
}