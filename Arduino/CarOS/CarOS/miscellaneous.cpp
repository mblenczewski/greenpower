//
//
//

#include <Adafruit_GFX.h>
#include <Streaming.h>

#include "miscellaneous.h"

uint16_t lcd_setup(MCUFRIEND_kbv* lcd_display);
void lcd_debug(Print& print_stream, const display& lcd_display);

display::display(MCUFRIEND_kbv* lcd_display)
{
	tft_display = lcd_display;

	display_size.x = tft_display->width();
	display_size.y = tft_display->height();
}

void display::setup_display()
{
	// Setup the display, and use the correct identifier.
	display_identifier = lcd_setup(tft_display);

	// We clear the screen and reset the position of the cursor.
	tft_display->fillScreen(BG_COLOUR);
	start_draw_text(0, 0, FG_COLOUR, TEXT_SIZE);
}

void display::write(const char* str, const int x, const int y, const uint16_t colour, const int size)
{
	start_draw_text(x, y, colour, size);

	tft_display->println(str);
}

void display::write_printable(Printable* printable, const int x, const int y, const uint16_t colour, const int size)
{
	start_draw_text(x, y, colour, size);

	tft_display->println(*printable);
}

void display::draw_vertical_line(const int x, const int y, const int height, const int thickness, const uint16_t colour)
{
	tft_display->fillRect(x, y, thickness, height, colour);
}

void display::draw_horizontal_line(const int x, const int y, const int width, const int thickness, const uint16_t colour)
{
	tft_display->fillRect(x, y, width, thickness, colour);
}

void display::draw_filled_rectangle(const int x, const int y, const int width, const int height, const uint16_t colour)
{
	tft_display->fillRect(x, y, width, height, colour);
}

void display::draw_hollow_rectangle(const int x, const int y, const int width, const int height, const uint16_t colour)
{
	tft_display->drawRect(x, y, width, height, colour);
}

void display::draw_hollow_rectangle(const int x, const int y, const int width, const int height, const int thickness,
	const uint16_t colour)
{
	// Draw the top horizontal line
	tft_display->fillRect(x, y, width, thickness, colour);

	// Draw the left hand vertical line
	tft_display->fillRect(x, y, thickness, height, colour);

	// Draw the bottom horizontal line
	tft_display->fillRect(x, y + height, width, thickness, colour);

	// Draw the right hand vertical line
	tft_display->fillRect(x + width, y, thickness, height, colour);
}

void display::draw_pixel(const int x, const int y, const uint16_t colour)
{
	tft_display->drawPixel(x, y, colour);
}

uint16_t lcd_setup(MCUFRIEND_kbv* lcd_display)
{
	// We reset the display and read its id.
	lcd_display->reset();
	uint16_t display_identifier = get_lcd_id(lcd_display);

	// There is no need to change the id.
	if (display_identifier == 0x9325 || display_identifier == 0x9328 || display_identifier == 0x4535 ||
		display_identifier == 0x7575 || display_identifier == 0x9595 || display_identifier == 0x4747 ||
		display_identifier == 0x8347 || display_identifier == 0x9341 || display_identifier == 0x7783 ||
		display_identifier == 0x8230 || display_identifier == 0x8357 || display_identifier == 0x7793 ||
		display_identifier == 0xB509 || display_identifier == 0x9486 || display_identifier == 0x9488)
	{
	}
	// Otherwise, the id needs to be changed.
	else if (display_identifier == 0x0101)
	{
		display_identifier = 0x9341;
	}
	else
	{
		display_identifier = 0x9486;
	}

	// We begin talking to the display with the correct settings.
	lcd_display->begin(display_identifier);
	return display_identifier;
}

void lcd_debug(Print& print_stream, const display& lcd_display)
{
	const uint16_t display_identifier = lcd_display.get_display_id();

	if (display_identifier == 0x9325)
	{
		print_stream << F("Found ILI9325 LCD driver");
	}
	else if (display_identifier == 0x9328)
	{
		print_stream << F("Found ILI9328 LCD driver");
	}
	else if (display_identifier == 0x4535)
	{
		print_stream << F("Found LGDP4535 LCD driver");
	}
	else if (display_identifier == 0x7575)
	{
		print_stream << F("Found HX8347G LCD driver");
	}
	else if (display_identifier == 0x9595)
	{
		print_stream << F("Found HX8347-I LCD driver");
	}
	else if (display_identifier == 0x4747)
	{
		print_stream << F("Found HX8347-D LCD driver");
	}
	else if (display_identifier == 0x8347)
	{
		print_stream << F("Found HX8347-A LCD driver");
	}
	else if (display_identifier == 0x9341)
	{
		print_stream << F("Found ILI9341 LCD driver");
	}
	else if (display_identifier == 0x7783)
	{
		print_stream << F("Found ST7781 LCD driver");
	}
	else if (display_identifier == 0x8230)
	{
		print_stream << F("Found UC8230 LCD driver");
	}
	else if (display_identifier == 0x8357)
	{
		print_stream << F("Found HX8357D LCD driver");
	}
	else if (display_identifier == 0x0101)
	{
		print_stream << F("Found 0x9341 LCD driver");
	}
	else if (display_identifier == 0x7793)
	{
		print_stream << F("Found ST7793 LCD driver");
	}
	else if (display_identifier == 0xB509)
	{
		print_stream << F("Found R61509 LCD driver");
	}
	else if (display_identifier == 0x9486)
	{
		print_stream << F("Found ILI9486 LCD driver");
	}
	else if (display_identifier == 0x9488)
	{
		print_stream << F("Found ILI9488 LCD driver");
	}
	else
	{
		print_stream << F("Unknown LCD driver chip: ") << _HEX(display_identifier) << endl;
		print_stream << F("If using the Adafruit 2.8 TFT Arduino shield, the line: ") << endl;
		print_stream << F("  #define USE_ADAFRUIT_SHIELD_PINOUT") << endl;
		print_stream << F("should appear in the library header (Adafruit_TFT.h).") << endl;
		print_stream << F("If using the breakout board, it should NOT be defined.") << endl;
		print_stream << F("Also if using the breaktout, double-check that all wiring") << endl;
		print_stream << F("matches the tutorial.") << endl;
	}
}