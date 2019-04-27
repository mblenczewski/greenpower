//
//
//

#include "Button.h"
#include "Car.h"
#include "Greenpower.h"

// Temporary variable which buttons will increment and decrement.
int temp_button_var;

// Pointer to temporary variable
int* temp_button_var_p = &temp_button_var;

// Increments a given variable by 1 whenever the ButtonAdd1 pin (pin 23) is high.
const Button INCREMENT_BY1{ temp_button_var_p, +1, Pins::ButtonAdd1 };

// Increments a given variable by 10 whenever the ButtonAdd10 pin (pin 24) is high.
const Button INCREMENT_BY10{ temp_button_var_p, +10, Pins::ButtonAdd10 };

// Decrements a given variable by 1 whenever the ButtonTake1 pin (pin 25) is high.
const Button DECREMENT_BY1{ temp_button_var_p, -1, Pins::ButtonTake1 };

// Decrements a given variable by 10 whenever the ButtonTake10 pin (pin 26) is high.
const Button DECREMENT_BY10{ temp_button_var_p, -10, Pins::ButtonTake10 };

// Array of all buttons that will be in use.
const Button BUTTONS[] = { INCREMENT_BY1, INCREMENT_BY10, DECREMENT_BY1, DECREMENT_BY10 };

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
	/*

	// Checks all buttons, and increments or decrements their backing variables if their monitored
	// pins are high. Otherwise, leaves the backing variable alone.
	for (Button button : BUTTONS)
	{
		button.check_pin();
	}

	*/

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