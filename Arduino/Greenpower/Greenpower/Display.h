// Display.h

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <MCUFRIEND_kbv.h>

// wiring with UNO or Mega2560:
//--------------POWER Pins--------------------------------
//   5V  connects to DC 5V
//   GND connects to Ground
//   3V3 do not need to connect(NC)
//--------------LCD Display Pins--------------------------
//   LCD_RD   connects to Analog pin A0
//   LCD_WR   connects to Analog pin A1
//   LCD_RS   connects to Analog pin A2
//   LCD_CS   connects to Analog pin A3
//   LCD_RST  connects to Analog pin A4
//   LCD_D0   connects to digital pin 8
//   LCD_D1   connects to digital pin 9
//   LCD_D2   connects to digital pin 2
//   LCD_D3   connects to digital pin 3
//   LCD_D4   connects to digital pin 4
//   LCD_D5   connects to digital pin 5
//   LCD_D6   connects to digital pin 6
//   LCD_D7   connects to digital pin 7
//--------------SD-card fuction Pins ----------------------
//This Connection Only for UNO, Do not support Mega2560
//because they use different Hardware-SPI Pins
//SD_SS    connects to digital pin 10
//SD_DI    connects to digital pin 11
//SD_DO    connects to digital pin 12
//SD_SCK   connects to digital pin 13

// Can alternately just connect to Arduinos reset pin. Set to Analog pin 4.
constexpr auto LCD_RESET = A4;

// Chip Select goes to Analog pin 3.
constexpr auto LCD_CS = A3;

// Command/Data goes to Analog pin 2.
constexpr auto LCD_CD = A2;

// LCD Write goes to Analog pin 1.
constexpr auto LCD_WR = A1;

// LCD Read goes to Analog pin 0.
constexpr auto LCD_RD = A0;

// Assign human-readable names to some common 16-bit color values:

// Defines the colour black as a 16-bit value.
constexpr unsigned short int BLACK = 0x0000;

// Defines the colour blue as a 16-bit value.
constexpr unsigned short int BLUE = 0x001F;

// Defines the colour red as a 16-bit value.
constexpr unsigned short int RED = 0xF800;

// Defines the colour green as a 16-bit value.
constexpr unsigned short int GREEN = 0x07E0;

// Defines the colour cyan as a 16-bit value.
constexpr unsigned short int CYAN = 0x07FF;

// Defines the colour magenta as a 16-bit value.
constexpr unsigned short int MAGENTA = 0xF81F;

// Defines the colour yellow as a 16-bit value.
constexpr unsigned short int YELLOW = 0xFFE0;

// Defines the colour white as a 16-bit value.
constexpr unsigned short int WHITE = 0xFFFF;

// Represents a display that can be written to or drawn on.
class Display
{
private:
	// The display that we will be drawing to.
	MCUFRIEND_kbv tft_display;

	// The ID for our display's processing chip.
	unsigned short int display_identifier;

public:
	// Initialises a new instance of the Display class.
	Display();

	// Sets the display up ready for writing or drawing.
	void setup_display();

	// Gets the identifier for the processing chip of the display.
	unsigned short int get_display_id() const;

	// Writes the given string message to the display, starting at the given (x, y) cursor position,
	// setting the text colour to white.
	void write(char str[], const uint16_t x, const uint16_t y) { write(str, x, y, WHITE); }

	// Writes the given string message to the display, starting at the given (x, y) cursor position,
	// and in the given 16-bit colour.
	void write(char str[], uint16_t x, uint16_t y, uint16_t colour);
};

// Logs debug information about the given LCD screen to the serial connection.
void lcd_debug(const Display& lcd_display);

// Gets the ID for our display's processing chip. Is inlined whenever it is used for performance reasons.
inline uint16_t get_lcd_id(MCUFRIEND_kbv lcd_screen)
{
	return lcd_screen.readID();
}
#endif