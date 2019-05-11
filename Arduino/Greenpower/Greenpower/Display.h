// Display.h

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Greenpower.h"
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

// LCD RS - identical to LCD_CD
constexpr auto LCD_RS = LCD_CD;

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

// Gets the ID for our display's processing chip. Inlined for performance reasons.
inline uint16_t get_lcd_id(MCUFRIEND_kbv* lcd_screen)
{
	return lcd_screen->readID();
}

// Represents a display that can be written to or drawn on.
class display
{
private:
	// The display that we will be drawing to.
	MCUFRIEND_kbv* tft_display = nullptr;

	// The ID for our display's processing chip.
	unsigned short int display_identifier = 0x9486;

	// Holds the size of the display (x = width, y = height).
	vec2<int> display_size{ 0, 0 };

	// The default size for any text written to the screen. Rendered text size in pixels
	// is calculated via the following equation: pixel_size = font_size * 10.
	static const unsigned short int TEXT_SIZE = 2;

	// The default background colour for the screen.
	static const unsigned short int BG_COLOUR = BLACK;

	// The default foreground colour for the screen.
	static const unsigned short int FG_COLOUR = WHITE;

protected:
	// Returns the number of pixels that the given string message will take up on the display
	// at the given font size. Inlined for performance reasons.
	static uint16_t string_size_in_pixels(const char* str, const int font_size)
	{
		// The font size in pixels can be found via: pixel_size = font_size * 10
		return strlen(str)* font_size * 10;
	}

	// Called to move the display's cursor to the correct position on the screen, and set the
	// appropriate colour for drawing text. Inlined for performance reasons.
	void start_draw_text(const int x_pos, const int y_pos, const uint16_t text_colour, const int text_size) const
	{
		tft_display->setCursor(x_pos, y_pos);
		tft_display->setTextSize(text_size);
		tft_display->setTextColor(text_colour);
	}

public:
	// Initialises a new instance of the Display class.
	explicit display(MCUFRIEND_kbv* lcd_display);

	// Sets the display up ready for writing or drawing.
	void setup_display();

	// Gets the identifier for the processing chip of the display.
	unsigned short int get_display_id() const
	{
		return display_identifier;
	}

	// Gets the size of the display.
	vec2<int> get_display_size() const
	{
		return display_size;
	}

	// Gets the width of a character with the given font size.
	int get_font_width(const int font_size = TEXT_SIZE) const
	{
		return font_size * 10;
	}

	// Gets the height of a character with the given font size.
	int get_font_height(const int font_size = TEXT_SIZE) const
	{
		return font_size * 10;
	}

	// Writes the given string message to the display, starting at the given (x, y) cursor position.
	// Writes the message in the default colour (white) and default font size.
	void write(const char* str, const int x, const int y)
	{
		write(str, x, y, FG_COLOUR, TEXT_SIZE);
	}

	// Writes the given string message to the display, starting at the given (x, y) cursor position.
	// Writes the message in the given 16-bit colour, and with the given font size.
	void write(const char* str, int x, int y, uint16_t colour, int size);

	// Writes the given printable object to the display, starting at the given (x, y) cursor position.
	// Writes the message in the given 16-bit colour, and with the given font size.
	void write_printable(Printable* printable, int x, int y, uint16_t colour, int size);

	// Draws a vertical line of the given height, 1 pixel wide, starting at the given (x, y) cursor position.
	// Draws the line in the default colour (white).
	void draw_vertical_line(const int x, const int y, const int height)
	{
		draw_vertical_line(x, y, height, 1, FG_COLOUR);
	}

	// Draws a vertical line of the given height, 1 pixel wide, starting at the given (x, y) cursor position.
	// Draws the line in the given 16-bit colour.
	void draw_vertical_line(const int x, const int y, const int height, const uint16_t colour)
	{
		draw_vertical_line(x, y, height, 1, colour);
	}

	// Draws a vertical line of the given height, of the given thickness, starting at the given (x, y) cursor position.
	// Draws the line in the given 16-bit colour.
	void draw_vertical_line(int x, int y, int height, int thickness, uint16_t colour);

	// Draws a horizontal line of the given width, 1 pixel high, starting at the given (x, y) cursor position.
	// Draws the line in the default colour (white).
	void draw_horizontal_line(const int x, const int y, const int width)
	{
		draw_horizontal_line(x, y, width, 1, FG_COLOUR);
	}

	// Draws a horizontal line of the given width, 1 pixel high, starting at the given (x, y) cursor position.
	// Draws the line in the given 16-bit colour.
	void draw_horizontal_line(const int x, const int y, const int width, const uint16_t colour)
	{
		draw_horizontal_line(x, y, width, 1, colour);
	}

	// Draws a horizontal line of the given width, of the given thickness, starting at the given (x, y) cursor position.
	// Draws the line in the given 16-bit colour.
	void draw_horizontal_line(int x, int y, int width, int thickness, uint16_t colour);

	// Draws a filled rectangle, of the given width and height, starting at the given (x, y) cursor position.
	// Draws the rectangle in the default colour (white).
	void draw_filled_rectangle(const uint16_t x, const uint16_t y, const uint16_t width, const int height)
	{
		draw_filled_rectangle(x, y, width, height, FG_COLOUR);
	}

	// Draws a filled rectangle, of the given width and height, starting at the given (x, y) cursor position.
	// Draws the rectangle in the given 16-bit colour.
	void draw_filled_rectangle(int x, int y, int width, int height, uint16_t colour);

	// Draws a hollow rectangle, of the given width and height, starting at the given (x, y) cursor position.
	// All lines that make up the rectangle (i.e. the left and right vertical line and the top and bottom horizontal line)
	// will be 1 pixel thick. Draws the rectangle in the default colour (white).
	void draw_hollow_rectangle(const int x, const int y, const int width, const int height)
	{
		draw_hollow_rectangle(x, y, width, height, FG_COLOUR);
	}

	// Draws a hollow rectangle, of the given width and height, starting at the given (x, y) cursor position.
	// All lines that make up the rectangle (i.e. the left and right vertical line and the top and bottom horizontal line)
	// will be 1 pixel thick. Draws the rectangle in the given 16-bit colour.
	void draw_hollow_rectangle(int x, int y, int width, int height, uint16_t colour);

	// Draws a hollow rectangle, of the given width and height, starting at the given (x, y) cursor position.
	// All lines that make up the rectangle (i.e. the left and right vertical line and the top and bottom horizontal line)
	// will be of the given thickness (in pixels). Draws the rectangle in the given 16-bit colour.
	void draw_hollow_rectangle(int x, int y, int width, int height, int thickness, uint16_t colour);

	// Draws a pixel at the given (x, y) cursor position in the default colour (white).
	void draw_pixel(const int x, const int y)
	{
		draw_pixel(x, y, FG_COLOUR);
	}

	// Draws a pixel at the given (x, y) cursor position in the given 16-bit colour.
	void draw_pixel(int x, int y, uint16_t colour);
};

// Sets up the MCUFRIEND_kvb lcd given, and returns the id in use by the lcd screen.
uint16_t lcd_setup(MCUFRIEND_kbv* lcd_display);

// Logs debug information about the given LCD screen to the serial connection.
void lcd_debug(const display* lcd_display);
#endif