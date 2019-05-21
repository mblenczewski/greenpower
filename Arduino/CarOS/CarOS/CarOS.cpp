//
//
//

#include "CarOS.h"
#include "builtin_button_callbacks.h"
#include "inputs.h"

int press_counter = 0;
button<int> incrementer{ A1, &press_counter, &increment_by_1_debug, &null_func };

pwm_input pwm_reader{ 21, pwm_reader_debug, RISING }; // on an arduino mega, pin 21 has interrupt functionality

input* inputs[] = { &incrementer, &pwm_reader };

int loop_()
{
	// read inputs and update their state; buttons will invoke callback functions
	for (input* input_ : inputs)
	{
		input_->read_pin();
	}

	return 0;
}

int main()
{
	init();

	Serial.begin(115200);
	Serial.println("Hello, World!");

	for (;;)
	{
		const int ret_code = loop_();

		if (ret_code != 0)
		{
			Serial.print("Error, non-zero return code: ");
			Serial.println(ret_code, DEC);
#ifdef _DEBUG
			break;
#endif
		}
	}

	Serial.println("Goodbye, World!");
	Serial.flush();
	return 0;
}