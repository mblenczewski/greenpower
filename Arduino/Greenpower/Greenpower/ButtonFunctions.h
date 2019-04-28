// ButtonFunctions.h

#ifndef _BUTTONFUNCTIONS_h
#define _BUTTONFUNCTIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Represents an empty function that does nothing with the given value.
template<typename T>
void null_func(T* ptr)
{
}

// Adds the given delta value to the given variable.
template<typename T>
void increment_variable(T* var, int delta) { *var += delta; }

// Increments the given variable by 1.
inline void increment_variable_1(int* variable) { increment_variable(variable, +1); }

// Increments the given variable by 10.
inline void increment_variable_10(int* variable) { increment_variable(variable, +10); }

// Decrements the given variable by 1.
inline void decrement_variable_1(int* variable) { increment_variable(variable, -1); }

// Decrements the given variable by 10.
inline void decrement_variable_10(int* variable) { increment_variable(variable, -10); }

// Sets the given bool to true.
inline void set_bool(bool* bool_ptr) { *bool_ptr = true; }

// Sets the given bool to false.
inline void reset_bool(bool* bool_ptr) { *bool_ptr = false; }

#endif
