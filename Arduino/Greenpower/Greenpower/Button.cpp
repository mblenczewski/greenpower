//
//
//

#include "Button.h"

template <typename T>
Button<T>::Button(T* target_variable_pointer, uint8_t target_pin, void(*button_pressed_callback_ptr)(T*),
	void(*button_not_pressed_callback_ptr)(T*))
{
	pin_to_check = target_pin;
	target_var_ptr = target_variable_pointer;

	// Function pointers are assigned
	pressed_callback_ptr = button_not_pressed_callback_ptr;
	not_pressed_callback_ptr = button_not_pressed_callback_ptr;

	is_pressed = digitalRead(pin_to_check) == HIGH;
}

template <typename T>
Button<T>::Button(T* target_variable_pointer, Pins target_pin, void(*button_pressed_callback_ptr)(T*),
	void(*button_not_pressed_callback_ptr)(T*))
{
	pin_to_check = get_pin(target_pin);
	target_var_ptr = target_variable_pointer;

	// Function pointers are assigned
	pressed_callback_ptr = button_not_pressed_callback_ptr;
	not_pressed_callback_ptr = button_not_pressed_callback_ptr;

	is_pressed = digitalRead(pin_to_check) == HIGH;
}

template <typename T>
void Button<T>::check_button()
{
	const bool pin_high = digitalRead(pin_to_check) == HIGH;

	// updates the stored 'is_pressed' value
	// the pin is now high, so the button must be pressed
	if (!is_pressed && pin_high)
	{
		is_pressed = true;
		pressed_callback_ptr(target_var_ptr);
	}
	// the pin is now low, so the button must not be pressed
	else if (is_pressed && !pin_high)
	{
		is_pressed = false;
		not_pressed_callback_ptr(target_var_ptr);
	}
}

template <typename T>
void Button<T>::set_target_variable_ptr(T* target_variable_pointer)
{
	target_var_ptr = target_variable_pointer;
}

template <typename T>
void Button<T>::set_pressed_func_ptr(void(*new_pressed_callback_ptr)(T*))
{
	pressed_callback_ptr = new_pressed_callback_ptr;
}

template <typename T>
void Button<T>::set_not_pressed_func_ptr(void(*new_not_pressed_callback_ptr)(T*))
{
	not_pressed_callback_ptr = new_not_pressed_callback_ptr;
}