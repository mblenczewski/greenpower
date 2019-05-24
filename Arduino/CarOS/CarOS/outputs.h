// outputs.h

#ifndef _OUTPUTS_h
#define _OUTPUTS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "CarOS.h"

// Represents an output that binds a pin and can write value to it.
class output
{
private:
	// Sets up this output instance with the given parameters.
	void setup_instance(const uint8_t pin_to_monitor, const uint8_t pin_mode, const int minimum_value, const int maximum_value)
	{
		monitored_pin = pin_to_monitor;
		pinMode(monitored_pin, pin_mode);
		this->minimum_value = minimum_value;
		this->maximum_value = maximum_value;
	}

protected:
	// Initialises a new instance of the output class.
	// Takes a pin that should be bound as an output, and sets it as an output (via pinMode(input_pin, OUTPUT)).
	explicit output(uint8_t monitored_input_pin);

	// Initialises a new instance of the output class.
	// Takes a pin that should be bound as an output, and sets it to the given mode (via pinMode(input_pin, pin_mode)).
	explicit output(uint8_t monitored_input_pin, uint8_t pin_mode);

	// Initialises a new instance of the output class via a copy constructor.
	// Takes a reference to a previous output instance.
	output(const output& other);

	// Initialises a new instance of the output class via a move constructor.
	// Takes a reference to a previous output instance.
	output(output&& other) noexcept;

	// Destroys an instance of the output class.
	// Also sets the bound pin to an output pin (via pinMode(pin, OUTPUT)).
	virtual ~output();

	// The pin that should be bound as an output.
	uint8_t monitored_pin = A0;

	// The current pin mode.
	uint8_t pin_mode = OUTPUT;

	// The minimum value that the written output value should be capped to.
	int minimum_value = 0;

	// The maximum value that the written output value should be capped to.
	int maximum_value = 1023;

	// Sets the minimum possible reading for an output to the given value.
	inline void set_minimum_value(int value);

	// Sets the maximum possible reading for an output to the given value.
	inline void set_maximum_value(int value);

	// Caps the given output between the given minimum and maximum values.
	virtual inline int cap_input(int output, int min, int max);

public:
	// Implementation of the copy assignment operator.
	output& operator= (const output& other);

	// Implementation of the move assignment operator.
	output& operator= (output&& other) noexcept;

	// Returns the current minimum possible reading for an output.
	inline int get_minimum_value() const;

	// Returns the current maximum possible reading for an output.
	inline int get_maximum_value() const;

	// Caps the given value between the minimum and maximum values, and writes it to the monitored pin.
	virtual void write_pin(int value) = 0;
};

// Represents an analog output that binds a pin and can write value to it.
class analog_output : public output
{
public:
	// Initialises a new instance of the analog_output class.
	// Takes a pin that should be bound as an output, and sets it as an output (via pinMode(input_pin, OUTPUT)).
	explicit analog_output(uint8_t monitored_input_pin);

	// Initialises a new instance of the analog_output class.
	// Takes a pin that should be bound as an output, and sets it to the given mode (via pinMode(input_pin, pin_mode)).
	explicit analog_output(uint8_t monitored_input_pin, uint8_t pin_mode);

	// Initialises a new instance of the analog_output class.
	// Takes a pin that should be bound as an output, and sets it as an output (via pinMode(input_pin, OUTPUT)).
	// Also takes a minimum output value and a maximum output value, to which the actual output reading will be capped.
	// This allows for 'dead-zones' in the output, giving a buffer between the actual maximum output and the written maximum output.
	analog_output(uint8_t monitored_input_pin, int minimum_value, int maximum_value);

	// Initialises a new instance of the analog_output class.
	// Takes a pin that should be bound as an output, and sets it to the given mode (via pinMode(input_pin, pin_mode)).
	// Also takes a minimum output value and a maximum output value, to which the actual output reading will be capped.
	// This allows for 'dead-zones' in the output, giving a buffer between the actual maximum output and the written maximum output.
	analog_output(uint8_t monitored_input_pin, uint8_t pin_mode, int minimum_value, int maximum_value);

	// Caps the given value between the minimum and maximum values, and writes it to the monitored pin.
	void write_pin(int value) override;
};

// Represents a digital output that binds a pin and can write value to it.
class digital_output : public output
{
protected:
	// Caps the given output between the given minimum and maximum values (these should be 0 and 1023 respectively). Will return
	// LOW if the given output is less than half of the maximum value, and HIGH if it is greater than half the maximum value.
	int cap_input(int output, int min, int max) override;

public:
	// Initialises a new instance of the digital_output class.
	// Takes a pin that should be bound as an output, and sets it as an output (via pinMode(input_pin, OUTPUT)).
	explicit digital_output(uint8_t monitored_input_pin);

	// Initialises a new instance of the digital_output class.
	// Takes a pin that should be bound as an output, and sets it to the given mode (via pinMode(input_pin, pin_mode)).
	explicit digital_output(uint8_t monitored_input_pin, uint8_t pin_mode);

	// Caps the given value between the minimum and maximum values, and writes it to the monitored pin.
	void write_pin(int value) override;
};

// Represents an output that binds a pin and can write PWM (Pulse Width Modulated) values to it.
class pwm_output final : public digital_output
{
private:
	// Sets up this pwm_output instance with the given parameters.
	void setup_pwm_instance(const uint8_t pin, const uint8_t pin_mode)
	{
		pinMode(monitored_pin, OUTPUT);
		monitored_pin = pin;
		this->pin_mode = pin_mode;
		pinMode(monitored_pin, pin_mode);
	}

public:
	// Initialises a new instance of the pwm_output class.
	// Takes a pin that should be bound as an output, and sets it as an output (via pinMode(input_pin, OUTPUT)).
	explicit pwm_output(uint8_t monitored_input_pin);

	// Initialises a new instance of the pwm_output class.
	// Takes a pin that should be bound as an output, and sets it to the given mode (via pinMode(input_pin, pin_mode)).
	explicit pwm_output(uint8_t monitored_input_pin, uint8_t pin_mode);

	// Initialises a new instance of the pwm_output class via a copy constructor.
	// Takes a reference to a previous pwm_output instance.
	pwm_output(const pwm_output& other);

	// Initialises a new instance of the pwm_output class via a move constructor.
	// Takes a reference to a previous pwm_output instance.
	pwm_output(pwm_output&& other) noexcept;

	// Implementation of the copy assignment operator.
	pwm_output& operator= (const pwm_output& other);

	// Implementation of the move assignment operator.
	pwm_output& operator= (pwm_output&& other) noexcept;

	// Destroys an instance of the pwm_output class.
	~pwm_output() override = default;

	// Caps the given value between the minimum and maximum values, and writes it to the monitored pin.
	void write_pin(int value) override;

	// Writes a pulse of the given pulse width in microseconds to the monitored pin.
	void write_pwm(unsigned long pulse_width_microseconds) const;
};

#endif
