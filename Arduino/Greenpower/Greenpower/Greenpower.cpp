//
//
//

#include "Car.h"
#include "Greenpower.h"

// Represents the car.
CarState car;

void setup_pin_modes()
{
	pinMode(get_pin(Pins::Ammeter), INPUT);
	pinMode(get_pin(Pins::Voltmeter), INPUT);
	pinMode(get_pin(Pins::Throttle), INPUT);
	pinMode(get_pin(Pins::Radio), OUTPUT);
	pinMode(get_pin(Pins::SpeedController), OUTPUT);
	pinMode(get_pin(Pins::Tachometer), INPUT);
	pinMode(get_pin(Pins::ButtonAdd1), INPUT);
	pinMode(get_pin(Pins::ButtonAdd10), INPUT);
	pinMode(get_pin(Pins::ButtonTake1), INPUT);
	pinMode(get_pin(Pins::ButtonTake10), INPUT);
	pinMode(get_pin(Pins::ButtonRaceMode), INPUT);
	pinMode(get_pin(Pins::ButtonOvertakeMode), INPUT);
}

int _loop() {
	car.update_buttons();
	car.next_tick();
	car.update_screen();

	delay(200);

	return 0;
}

int main()
{
	// Initialises Arduino stuff, such as serial output and input.
	init();
	Serial.begin(9600);

	// Initialises car stuff, such as pin modes and the RF module.
	setup_pin_modes();

	while (true)
	{
		const int return_code = _loop();

		if (return_code == 0)
		{
			//Serial.println(F("Loop completed successfuly."));
		}
		else
		{
			Serial.print(F("Loop failed with error code "));
			Serial.println(return_code, DEC);
			break;
		}
	}

	Serial.flush();
	return 0;
}