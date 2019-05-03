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
// Should the pin be high (the button is pressed) a function will be performed. Should it not be high,
// a different function will be performed.
template<typename T>
class button
{
private:
	// The reading interval used to counter button bouncing.
	const unsigned long DEBOUNCE_MS = 50;

	// The last time that the button was read with debounce.
	unsigned long last_valid_reading = 0;

	// The buttons target, represented as the pin that the button needs to check.
	uint8_t pin_to_check;

	// Reference to the variable that will be incremented or decremented on a button press.
	T* target_var_ptr;

	// Pointer to a function that will be executed when the button is pressed.
	void(*pressed_callback_ptr)(T* target_variable);

	// Pointer to a function that will be executed when the button is not pressed.
	void(*not_pressed_callback_ptr)(T* target_variable);

	// Whether the button was pressed last tick.
	bool is_pressed;

public:
	// Initialises a new instance of the Button class.
	// Takes a pointer to a variable , and two pointers to functions that will operate on said variable. One function will only
	// be invoked if the button is not pressed, and vice versa. Also takes a uint8_t value, which holds the pin that should be checked
	// to see whether the physical button is pressed.
	button(T* target_variable_pointer, uint8_t target_pin, void (*button_pressed_callback_ptr)(T*),
		void (*button_not_pressed_callback_ptr)(T*));

	// Initialises a new instance of the Button class.
	// Takes a pointer to a variable , and two pointers to functions that will operate on said variable. One function will only
	// be invoked if the button is not pressed, and vice versa. Also takes a Pins value, which holds the pin that should be checked
	// to see whether the physical button is pressed.
	button(T* target_variable_pointer, pins target_pin, void (*button_pressed_callback_ptr)(T*),
		void (*button_not_pressed_callback_ptr)(T*));

	// Checks whether the button is pressed, and executes the functions given by the pointers passed to the constructor accordingly.
	void check_button();

	// Sets the pointer to the targeted variable to the given value, so that the button operates on a different variable.
	void set_target_variable_ptr(T* target_variable_pointer);

	// Sets the pointer to the pressed callback function to the given value, so a new function is invoked when the button is pressed.
	void set_pressed_func_ptr(void (*new_pressed_callback_ptr)(T*));

	// Sets the pointer to the not pressed callback function to the given value, so a new function is invoked when the button is not pressed.
	void set_not_pressed_func_ptr(void (*new_not_pressed_callback_ptr)(T*));
};

#endif
