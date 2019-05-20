// builtin_button_callbacks.h

#ifndef _BUILTIN_BUTTON_CALLBACKS_h
#define _BUILTIN_BUTTON_CALLBACKS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Represents a null function, that doesn't affect the target variable.
template <typename T>
void null_func(T& target_variable_ptr)
{
}

// Increments the target variable by the given delta.
template <typename T>
void increment_value(T& target_variable_ptr, T delta)
{
	target_variable_ptr += delta;
}

// Increments the target variable by 1.
template <typename T>
void increment_by_1(T& target_variable_ptr)
{
	increment_value(target_variable_ptr, 1);
}

// Increments the target variable by 10.
template <typename T>
void increment_by_10(T& target_variable_ptr)
{
	increment_value(target_variable_ptr, 10);
}

// Increments the target variable by 100.
template <typename T>
void increment_by_100(T& target_variable_ptr)
{
	increment_value(target_variable_ptr, 100);
}

// Decrements the target variable by the given delta.
template <typename T>
void decrement_value(T& target_variable_ptr, T delta)
{
	target_variable_ptr -= delta;
}

// Decrements the target variable by 1.
template <typename T>
void decrement_by_1(T& target_variable_ptr)
{
	decrement_value(target_variable_ptr, 1);
}

// Decrements the target variable by 10.
template <typename T>
void decrement_by_10(T& target_variable_ptr)
{
	decrement_value(target_variable_ptr, 10);
}

// Decrements the target variable by 100.
template <typename T>
void decrement_by_100(T& target_variable_ptr)
{
	decrement_value(target_variable_ptr, 100);
}

// Sets the target variable to true.
inline void set_bool(bool& target_variable_ptr)
{
	target_variable_ptr = false;
}

// Sets the target variable to false.
inline void reset_bool(bool& target_variable_ptr)
{
}

#endif
