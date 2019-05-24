//
//
//

#include "outputs.h"

output::output(const uint8_t monitored_input_pin)
{
	setup_instance(monitored_input_pin, OUTPUT, minimum_value, maximum_value);
}

output::output(const uint8_t monitored_input_pin, const uint8_t pin_mode)
{
	setup_instance(monitored_input_pin, pin_mode, minimum_value, maximum_value);
}

output::output(const output& other)
{
	setup_instance(other.monitored_pin, other.pin_mode, other.minimum_value, other.maximum_value);
}

output::output(output&& other) noexcept
{
	setup_instance(other.monitored_pin, other.pin_mode, other.minimum_value, other.maximum_value);
}

output::~output()
{
	pinMode(monitored_pin, OUTPUT);
}

void output::set_minimum_value(const int value)
{
	minimum_value = value;
}

void output::set_maximum_value(const int value)
{
	maximum_value = value;
}

int output::cap_input(const int output, const int min, const int max)
{
	// caps the input if its greater than the maximum allowed value
	// or if its smaller than the minimum allowed value
	return output > max ? max : output < min ? min : output;
}

output& output::operator=(const output& other)
{
	if (this != &other)
	{
		setup_instance(other.monitored_pin, other.pin_mode, other.minimum_value, other.maximum_value);
	}

	return *this;
}

output& output::operator=(output&& other) noexcept
{
	if (this != &other)
	{
		setup_instance(other.monitored_pin, other.pin_mode, other.minimum_value, other.maximum_value);
	}

	return *this;
}

int output::get_minimum_value() const
{
	return minimum_value;
}

int output::get_maximum_value() const
{
	return maximum_value;
}

analog_output::analog_output(const uint8_t monitored_input_pin) : output(monitored_input_pin)
{
}

analog_output::analog_output(const uint8_t monitored_input_pin, const uint8_t pin_mode) : output(monitored_input_pin, pin_mode)
{
}

analog_output::analog_output(const uint8_t monitored_input_pin, const int minimum_value, const int maximum_value) : output(monitored_input_pin)
{
}

analog_output::analog_output(const uint8_t monitored_input_pin, const uint8_t pin_mode, const int minimum_value, const int maximum_value) : output(monitored_input_pin, pin_mode)
{
}

void analog_output::write_pin(const int value)
{
	analogWrite(monitored_pin, value);
}

int digital_output::cap_input(const int output, const int min, const int max)
{
	return output < (max - min) / 2 ? LOW : HIGH;
}

digital_output::digital_output(const uint8_t monitored_input_pin) : output(monitored_input_pin)
{
}

digital_output::digital_output(const uint8_t monitored_input_pin, const uint8_t pin_mode) : output(monitored_input_pin, pin_mode)
{
}

void digital_output::write_pin(const int value)
{
	digitalWrite(monitored_pin, cap_input(value, 0, 1023));
}

pwm_output::pwm_output(const uint8_t monitored_input_pin) : digital_output(monitored_input_pin)
{
}

pwm_output::pwm_output(const uint8_t monitored_input_pin, const uint8_t pin_mode) : digital_output(monitored_input_pin, pin_mode)
{
}

pwm_output::pwm_output(const pwm_output& other) : digital_output(other.monitored_pin, other.pin_mode)
{
}

pwm_output::pwm_output(pwm_output&& other) noexcept : digital_output(other.monitored_pin, other.pin_mode)
{
}

pwm_output& pwm_output::operator=(const pwm_output& other)
{
	if (this != &other)
	{
		setup_pwm_instance(other.monitored_pin, other.pin_mode);
	}

	return *this;
}

pwm_output& pwm_output::operator=(pwm_output&& other) noexcept
{
	if (this != &other)
	{
		setup_pwm_instance(other.monitored_pin, other.pin_mode);
	}

	return *this;
}

//pwm_output::~pwm_output() { }

void pwm_output::write_pin(const int value)
{
	digitalWrite(monitored_pin, cap_input(value, 0, 1023));
}

void pwm_output::write_pwm(const unsigned long pulse_width_microseconds) const
{
	digitalWrite(monitored_pin, HIGH);
	delayMicroseconds(pulse_width_microseconds);
	digitalWrite(monitored_pin, LOW);
}