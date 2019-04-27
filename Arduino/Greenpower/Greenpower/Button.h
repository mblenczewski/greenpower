// Button.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Greenpower.h"

// Represents a physical button, that stores a physical pin and checks whether the pin is high or low.
// Increments a given variable by a given amount if the pin is high, and does nothing if the pin is low.
// The incremented variable is given via a pointer.
class Button
{
private:
	// The buttons target, represented as the pin that the button needs to check.
	uint8_t pin_to_check;

	// Reference to the variable that will be incremented or decremented on a button press.
	int* target_var_p;

	// The amount that the target variable (see 'target_var_ref') should be incremented by.
	int change_interval;

	// Whether the button was pressed last tick.
	bool is_pressed;

public:
	// Initialises a new instance of the Button class.
	// Takes a pointer to a variable that will be incremented when the button is pressed, and a value by which to increment said variable.
	// Also takes a 'uint8_t', which holds the pin that should be checked to see whether the physical button is pressed.
	Button(int* target_variable_pointer, int change_increment, uint8_t target_pin);

	// Initialises a new instance of the Button class.
	// Takes a pointer to a variable that will be incremented when the button is pressed, and a value by which to increment said variable.
	// Also takes a 'Pins' value, which holds the pin that should be checked to see whether the physical button is pressed.
	Button(int* target_variable_pointer, int change_increment, Pins target_pin);

	// Checks whether the pin given in the constructor (given as a 'BtnTarget') is high. If so, increments the given variable (via its pointer).
	void check_pin();

	// Sets the target variable pointer to the given value, so that the button increments a different variable.
	void set_target_variable(int* target_variable_pointer);
};

#endif