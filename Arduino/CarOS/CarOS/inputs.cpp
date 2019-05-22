//
//
//

#include <eRCaGuy_Timer2_Counter.h>
#include "inputs.h"

// Global counter used to track elapsed time to within 1 microsecond.
eRCaGuy_Timer2_Counter accurate_microsecond_timer{};

// Holds the single pwm_input instance that can be acted upon by an interrupt service routine.
pwm_input* pwm_input_instance = nullptr;

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

pwm_input::~pwm_input()
{
	detachInterrupt(digitalPinToInterrupt(monitored_pin));
	pwm_input_instance = nullptr;
}

pwm_input::pwm_input(const uint8_t monitored_input_pin) : input(monitored_input_pin)
{
	setup_pwm(monitored_input_pin, nullptr, RISING);
}

pwm_input::pwm_input(const uint8_t monitored_input_pin, const uint8_t pwm_mode) : input(monitored_input_pin)
{
	setup_pwm(monitored_input_pin, nullptr, pwm_mode);
}

pwm_input::pwm_input(const uint8_t monitored_input_pin, const interrupt_service_routine isr, const uint8_t pwm_mode) : input(monitored_input_pin)
{
	setup_pwm(monitored_input_pin, isr, pwm_mode);
}

pwm_input::pwm_input(const pwm_input& other) : input(other.monitored_pin)
{
	setup_pwm_from_other(const_cast<pwm_input&>(other));
}

pwm_input::pwm_input(pwm_input&& other) noexcept : input(other.monitored_pin)
{
	setup_pwm_from_other(other);
}

pwm_input& pwm_input::operator=(const pwm_input& other)
{
	if (this != &other)
	{
		setup_pwm_from_other(const_cast<pwm_input&>(other));
	}

	return *this;
}

pwm_input& pwm_input::operator=(pwm_input&& other) noexcept
{
	if (this != &other)
	{
		setup_pwm_from_other(other);
	}

	return *this;
}

int pwm_input::read_pin()
{
	return pulse_width;
}

float pwm_input::percentage_input()
{
	return 0;
}

analog_input::analog_input(const uint8_t monitored_input_pin) : input(monitored_input_pin)
{
	// can set maximum and minimum input values here
}

analog_input::analog_input(const uint8_t monitored_input_pin, const int minimum_value, const int maximum_value) : input(monitored_input_pin)
{
	this->minimum_value = minimum_value;
	this->maximum_value = maximum_value;
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

void default_isr()
{
  unsigned long t = micros(); //  accurate_microsecond_timer.get_count(); XXX not behaving
  
  if (pwm_input_instance == nullptr)
	{
		return;
	}

  pwm_input_instance->pulse_width = t - pwm_input_instance->last_interrupt_time;
	pwm_input_instance->last_interrupt_time = t;

	if (pwm_input_instance->custom_isr == nullptr)
	{
		return;
	}

	pwm_input_instance->custom_isr();
}
