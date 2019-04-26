// Display.h

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#endif

#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>
#include <TFT_HX8357GLUE.h>
#include <mcufriend_special.h>
#include <mcufriend_shield.h>
#include <mcufriend_serial.h>
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

// Can alternately just connect to Arduinos reset pin. Set to Analog 4
constexpr auto LCD_RESET = A4;
// Chip Select goes to Analog 3
constexpr auto LCD_CS = A3;
// Command/Data goes to Analog 2
constexpr auto LCD_CD = A2;
// LCD Write goes to Analog 1
constexpr auto LCD_WR = A1;
// LCD Read goes to Analog 0
constexpr auto LCD_RD = A0;

// Assign human-readable names to some common 16-bit color values:
constexpr auto BLACK = 0x0000;
constexpr auto BLUE = 0x001F;
constexpr auto RED = 0xF800;
constexpr auto GREEN = 0x07E0;
constexpr auto CYAN = 0x07FF;
constexpr auto MAGENTA = 0xF81F;
constexpr auto YELLOW = 0xFFE0;
constexpr auto WHITE = 0xFFFF;

MCUFRIEND_kbv tft;
uint16_t identifier;
char header_message[] = "Andrew is a fookin' nugget!";
char message[] = "Groop\nI implore thee,\nmy foonting turlingdromes.\nAnd hooptiously drangle me\nwith crinkly bindlewurdles,\nOr I will rend thee\nin the gobberwarts\nwith my blurglecruncheon,\nsee if I don't!";

// Logs debug information about the connected LCD screen to the serial connection.
void lcd_debug();