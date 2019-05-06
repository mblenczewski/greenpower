//
//
//

#include "Greenpower.h"
#include "Car.h"

// The elapsed time since the Arduino was powered on.
unsigned long global_elapsed_time_ms = millis();

// The display that we will be writing to.
MCUFRIEND_kbv tft_display;

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

int _loop()
{
	// The delta time (in milliseconds) between the last tick and the current one.
	const unsigned long delta_time_ms = global_elapsed_time_ms - millis();

	car.update_buttons();
	car.next_tick(delta_time_ms);
	car.update_screen();

	// Update the global elapsed time (in milliseconds) for the next iteration.
	global_elapsed_time_ms = millis();

	Serial.println(F("Hello, World!"));
	return 0;
}

int main()
{
	// Initialises Arduino stuff, such as serial output and input.
	init();
	Serial.begin(115200);

	// Initialises car stuff, such as the pin modes, the screen, and the RF module.
	setup_pin_modes();
	lcd_setup(&tft_display);

	// Set the display to horizontal
	tft_display.setRotation(1);

	for (;;)
	{
		// The return code for the next loop iteration; main() will break if it is not 0.
		const int ret_code = _loop();

		if (ret_code != 0)
		{
			Serial.print(F("Non-zero error code returned: "));
			Serial.println(ret_code, DEC);
			break;
		}
	}

	Serial.flush();
	return 0;
}