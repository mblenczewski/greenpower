//
//
//

#include "CarOS.h"
#include "builtin_button_callbacks.h"
#include "inputs.h"

int counter = 0;
button<int> incrementer{ A1, &counter, &increment_by_1_debug, &null_func };

input* inputs[1] = { &incrementer };

int loop_()
{
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