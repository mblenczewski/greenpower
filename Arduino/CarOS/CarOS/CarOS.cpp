//
//
//

#include "CarOS.h"

int loop_()
{
	return -1;
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
	return 0;
}