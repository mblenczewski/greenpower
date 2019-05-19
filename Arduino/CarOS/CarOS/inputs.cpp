//
//
//

#include "inputs.h"

input::input(const uint8_t monitored_input_pin)
{
	setup_instance(monitored_input_pin, minimum_value, maximum_value);
}

input::input(const input& other)
{
	setup_instance(other.monitored_pin, other.minimum_value, other.maximum_value);
}

input::input(input&& other) noexcept
{
	setup_instance(other.monitored_pin, other.minimum_value, other.maximum_value);
}

input::~input()
{
	pinMode(monitored_pin, OUTPUT);
}

void input::set_minimum_value(const int value)
{
	minimum_value = value;
}

void input::set_maximum_value(const int value)
{
	maximum_value = value;
}

int input::cap_input(const int input, const int min, const int max)
{
	// caps the input if its greater than the maximum allowed value
	// or if its smaller than the minimum allowed value
	return input > max ? max : input < min ? min : input;
}

input& input::operator=(const input& other)
{
	if (this != &other)
	{
		setup_instance(other.monitored_pin, other.minimum_value, other.maximum_value);
	}

	return *this;
}

input& input::operator=(input&& other) noexcept
{
	if (this != &other)
	{
		setup_instance(other.monitored_pin, other.minimum_value, other.maximum_value);
	}

	return *this;
}

int input::get_minimum_value() const
{
	return minimum_value;
}

int input::get_maximum_value() const
{
	return maximum_value;
}

analog_input::analog_input(const uint8_t monitored_input_pin) : input(monitored_input_pin)
{
	// can set maximum and minimum input values here
}

int analog_input::read_pin()
{
	return cap_input(analogRead(monitored_pin), minimum_value, maximum_value);
}

float analog_input::percentage_input()
{
	return static_cast<float>(cap_input(analogRead(monitored_pin), minimum_value, maximum_value)) / static_cast<float>(maximum_value);
}

digital_input::digital_input(const uint8_t monitored_input_pin) : input(monitored_input_pin)
{
	// can set maximum and minimum input values here
	minimum_value = LOW;
	maximum_value = HIGH;
}

int digital_input::read_pin()
{
	return digitalRead(monitored_pin);
}

float digital_input::percentage_input()
{
	if (digitalRead(monitored_pin) == LOW)
	{
		return 0;
	}

	return 1;
}