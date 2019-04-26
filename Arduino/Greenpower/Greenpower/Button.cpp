//
//
//

#include "Button.h"

Button::Button(int* target_variable_pointer, int change_increment, uint8_t target_pin)
{
	pin_to_check = target_pin;
	target_var_p = target_variable_pointer;
	change_interval = change_increment;

	is_pressed = digitalRead(pin_to_check) == HIGH;
}

Button::Button(int* target_variable_pointer, int change_increment, ::Pins target_pin)
{
	pin_to_check = static_cast<uint8_t>(target_pin);
	target_var_p = target_variable_pointer;
	change_interval = change_increment;

	is_pressed = digitalRead(pin_to_check) == HIGH;
}

void Button::check_pin()
{
	const bool pin_high = digitalRead(pin_to_check) == HIGH;

	// updates the stored 'is_pressed' value
	// the pin is now high, so the button must be pressed
	if (!is_pressed && pin_high)
	{
		is_pressed = true;
		*target_var_p += change_interval;
	}
	// the pin is now low, so the button must not be pressed
	else if (is_pressed && !pin_high)
	{
		is_pressed = false;
	}
}

void Button::set_target_variable(int* target_variable_pointer)
{
	target_var_p = target_variable_pointer;
}