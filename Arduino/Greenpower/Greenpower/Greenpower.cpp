//
//
//

#include "Greenpower.h"

int _loop() {
	/*
	tft.fillScreen(BLACK);
	tft.setCursor(0, 0);

	tft.setTextColor(GREEN);
	tft.setTextSize(5);
	tft.println(header_message);

	tft.println();
	tft.setTextColor(RED);
	tft.setTextSize(2);
	tft.println(message);
	*/

	return 0;
}

int main()
{
	init();
	Serial.begin(9600);

	/*
	Serial.println(F("TFT LCD test"));

	tft.reset();
	identifier = tft.readID();
	lcd_debug();
	tft.begin(identifier);

	tft.fillScreen(BLACK);
	tft.setCursor(0, 0);
	*/

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