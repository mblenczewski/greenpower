// inputs.h

#ifndef _INPUTS_h
#define _INPUTS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <eRCaGuy_Timer2_Counter.h>

// Global counter used to track elapsed time to within 1 microsecond.
extern eRCaGuy_Timer2_Counter accurate_microsecond_timer;

class pwm_input;

// Holds the single pwm_input instance that can be acted upon by an interrupt service routine.
extern pwm_input* pwm_input_instance;

void default_isr();

// Represents an input that reads a pin and returns the read value.
class input
{
private:
	// Sets up this input instance with the given parameters.
	void setup_instance(const uint8_t pin_to_monitor, const int minimum_value, const int maximum_value)
	{
		monitored_pin = pin_to_monitor;
		pinMode(monitored_pin, INPUT_PULLUP);
		this->minimum_value = minimum_value;
		this->maximum_value = maximum_value;
	}

protected:
	// Initialises a new instance of the input class.
	// Takes a pin that should be monitored as an input, and sets it as an input (via pinMode(input_pin, INPUT)).
	explicit input(uint8_t monitored_input_pin);

	// Initialises a new instance of the input class via a copy constructor.
	// Takes a reference to a previous input instance.
	input(const input& other);

	// Initialises a new instance of the input class via a move constructor.
	// Takes a reference to a previous input instance.
	input(input&& other) noexcept;

	// Destroys an instance of the input class.
	// Also sets the monitored input pin to an output pin (via pinMode(pin, OUTPUT)).
	virtual ~input();

	// The pin that should be read as the input.
	uint8_t monitored_pin = A0;

	// The minimum value that the read input should be capped to.
	int minimum_value = 0;

	// The maximum value that the read input should be capped to.
	int maximum_value = 1023;

	// Sets the minimum possible reading for an input to the given value.
	inline void set_minimum_value(int value);

	// Sets the maximum possible reading for an input to the given value.
	inline void set_maximum_value(int value);

	// Caps the given input between the given minimum and maximum values.
	static inline int cap_input(int input, int min, int max);

public:
	// Implementation of the copy assignment operator.
	input& operator= (const input& other);

	// Implementation of the move assignment operator.
	input& operator= (input&& other) noexcept;

	// Returns the current minimum possible reading for an input.
	inline int get_minimum_value() const;

	// Returns the current maximum possible reading for an input.
	inline int get_maximum_value() const;

	// Reads the monitored input pin, caps the result between the minimum and maximum value
	// and returns it.
	virtual int read_pin() = 0;

	// Reads the monitored input pin, caps the result between the minimum and maximum value
	// and returns the percentage of the way to the maximum value that the reading is.
	// Returns the percentage as a float between 0 and 1.
	virtual float percentage_input() = 0;
};

// Represents an input capable of reading PWM (pulse width modulated) signals.
class pwm_input final : public input
{
private:
	// Defines a typename alias for an ISR.
	using interrupt_service_routine = void(*)();

	// The default interrupt service routine, used for counting the length of the pwm.
	friend void default_isr();

	// Sets up this pwm_input instance with the given parameters.
	void setup_pwm(const uint8_t pin, const interrupt_service_routine isr, const uint8_t mode)
	{
		timer_start = last_interrupt_time = pulse_width = 0;
		custom_isr = isr;
		pwm_mode = mode;
		attachInterrupt(digitalPinToInterrupt(pin), default_isr, pwm_mode);
		pwm_input_instance = this;
	}

	// Sets up this pwm_input instance from the given instance reference.
	void setup_pwm_from_other(pwm_input& other)
	{
		monitored_pin = other.monitored_pin;
		minimum_value = other.minimum_value;
		maximum_value = other.maximum_value;

		timer_start = other.timer_start;
		last_interrupt_time = other.last_interrupt_time;
		pulse_width = other.pulse_width;
		custom_isr = other.custom_isr;
		pwm_mode = other.pwm_mode;

		detachInterrupt(digitalPinToInterrupt(monitored_pin));
		pwm_input_instance = this;
		attachInterrupt(digitalPinToInterrupt(monitored_pin), default_isr, pwm_mode);
	}

	// The time at which the timer was started.
	volatile unsigned long timer_start;

	// The last time an interrupt was handled.
	volatile unsigned long last_interrupt_time;

	// The width of the pulse in microseconds.
	volatile unsigned long pulse_width;

	// A user defined interrupt service routine.
	interrupt_service_routine custom_isr;

	// The mode in which the PWM should work.
	uint8_t pwm_mode;

public:
	// Initialises a new instance of the pwm_input class.
	// Takes a pin that should be monitored as an input, and sets it as an input (via pinMode(input_pin, INPUT)).
	explicit pwm_input(uint8_t monitored_input_pin);

	// Initialises a new instance of the pwm_input class.
	// Takes a pin that should be monitored as an input, and sets it as an input (via pinMode(input_pin, INPUT)).
	// Also takes the PWM mode on which the ISR should be executed.
	pwm_input(uint8_t monitored_input_pin, uint8_t pwm_mode);

	// Initialises a new instance of the pwm_input class.
	// Takes a pin that should be monitored as an input, and sets it as an input (via pinMode(input_pin, INPUT)).
	// Also takes a custom ISR, and the PWM mode on which the ISR should be executed.
	pwm_input(uint8_t monitored_input_pin, interrupt_service_routine isr, uint8_t pwm_mode);

	// Initialises a new instance of the pwm_input class via a copy constructor.
	// Takes a reference to a previous pwm_input instance.
	pwm_input(const pwm_input& other);

	// Initialises a new instance of the pwm_input class via a move constructor.
	// Takes a reference to a previous pwm_input instance.
	pwm_input(pwm_input&& other) noexcept;

	// Implementation of the copy assignment operator.
	pwm_input& operator= (const pwm_input& other);

	// Implementation of the move assignment operator.
	pwm_input& operator= (pwm_input&& other) noexcept;

	// Destroys an instance of the pwm_input class.
	// Detaches the attached interrupt from the monitored pin.
	~pwm_input() override;

	// Returns the pulse width that was last read.
	int read_pin() override;

	// Returns the lase pulse width.
	unsigned long read_pwm() const { return pulse_width; }

	// Reads the monitored input pin, caps the result between the minimum and maximum value
	// and returns the percentage of the way to the maximum value that the reading is.
	// Returns the percentage as a float between 0 and 1.
	float percentage_input() override;
};

// Represents an analog input that reads a pin and returns the read value.
class analog_input : public input
{
public:
	// Initialises a new instance of the analog_input class.
	// Takes a pin that should be monitored as an input, and sets it as an input (via pinMode(input_pin, INPUT)).
	explicit analog_input(uint8_t monitored_input_pin);

	// Initialises a new instance of the analog_input class.
	// Takes a pin that should be monitored as an input, and sets it as an input (via pinMode(input_pin, INPUT)).
	// Also takes a minimum input value and a maximum input value, to which the actual input reading will be capped.
	// This allows for 'dead-zones' in the input, giving a buffer between the actual maximum input and the read maximum input.
	analog_input(uint8_t monitored_input_pin, int minimum_value, int maximum_value);

	// Reads the monitored input pin, caps the result between the minimum and maximum value
	// and returns it.
	int read_pin() override;

	// Reads the monitored input pin, caps the result between the minimum and maximum value
	// and returns the percentage of the way to the maximum value that the reading is.
	// Returns the percentage as a float between 0 and 1.
	float percentage_input() override;
};

// Represents a digital input that reads a pin and returns the read value.
class digital_input : public input
{
public:
	// Initialises a new instance of the digital_input class.
	// Takes a pin that should be monitored as an input, and sets it as an input (via pinMode(input_pin, INPUT)).
	explicit digital_input(uint8_t monitored_input_pin);

	// Reads the monitored input pin, caps the result between the minimum and maximum value
	// and returns it.
	int read_pin() override;

	// Reads the monitored input pin, caps the result between the minimum and maximum value
	// and returns the percentage of the way to the maximum value that the reading is.
	// Returns the percentage as a float between 0 and 1.
	float percentage_input() override;
};

// Represents a button, with debounce features. Takes a type for the target variable that the button should
// edit.
template<typename T>
class button final : public digital_input
{
private:
	// Defines a typename alias for a callback function.
	using callback_func = void(*)(T& target_var_ptr);

	// The reading interval used to counter button bouncing.
	unsigned long DEBOUNCE_MS = 50;

	// The current reading of the monitored pin.
	int button_state;

	// The last reading of the monitored pin.
	int last_button_state;

	// The number of times the state of the button has changed.
	unsigned int state_change_count;

	// The delay in milliseconds between readings to ensure bounce protection.
	unsigned long debounce_delay_ms;

	// The last time the button was successfully read.
	unsigned long last_debounce_time_ms;

	// Whether we are waiting for the debounce interval to complete; stops millis() being called repeatedly.
	bool waiting_for_debounce = false;

	// Points to the variables that should be edited when the button is pressed.
	T* target_variable_ptr = nullptr;

	// Function to be invoked whenever the button state is checked, and the button is pressed.
	callback_func button_pressed_func = nullptr;

	// Function to be invoked whenever the button state is checked, and the button is not pressed.
	callback_func button_not_pressed_func = nullptr;

	// Whether any pointers are set to nullptr.
	bool pointers_null = true;

public:
	// Initialises a new instance of the button class.
	// Takes a pin that should be monitored as an input, and sets it as an input (via pinMode(input_pin, INPUT)).
	// No callback functions will be invoked when the button state changes.
	explicit button(const uint8_t monitored_input_pin) : digital_input(monitored_input_pin)
	{
		debounce_delay_ms = DEBOUNCE_MS;
		button_state = last_button_state = digitalRead(monitored_pin);
		last_debounce_time_ms = millis();
		state_change_count = 0;
	}

	// Initialises a new instance of the button class.
	// Takes a pin that should be monitored as an input, and sets it as an input (via pinMode(input_pin, INPUT)).
	// Also takes callback function pointers for functions to invoke whenever the button state is checked, and the
	// button is pressed and not pressed respectively, and a pointer to a variable that the callback functions
	// should operate on.
	button(const uint8_t monitored_input_pin, T* target_variable_pointer, const callback_func button_pressed_callback,
		const callback_func button_not_pressed_callback) : digital_input(monitored_input_pin)
	{
		debounce_delay_ms = DEBOUNCE_MS;
		button_state = last_button_state = digitalRead(monitored_pin);
		last_debounce_time_ms = millis();
		state_change_count = 0;

		target_variable_ptr = target_variable_pointer;
		button_pressed_func = button_pressed_callback;
		button_not_pressed_func = button_not_pressed_callback;

		pointers_null =
			target_variable_ptr == nullptr ||
			button_pressed_func == nullptr ||
			button_not_pressed_func == nullptr;
	}

	// Initialises a new instance of the button class.
	// Takes a pin that should be monitored as an input, and sets it as an input (via pinMode(input_pin, INPUT)).
	// Also takes the debounce delay in milliseconds to use.
	// No callback functions will be invoked when the button state changes.
	button(const uint8_t monitored_input_pin, const unsigned long debounce_delay_ms) : digital_input(monitored_input_pin)
	{
		this->debounce_delay_ms = debounce_delay_ms;
		button_state = last_button_state = digitalRead(monitored_pin);
		last_debounce_time_ms = millis();
		state_change_count = 0;
	}

	// Initialises a new instance of the button class.
	// Takes a pin that should be monitored as an input, and sets it as an input (via pinMode(input_pin, INPUT)).
	// Also takes the debounce delay in milliseconds to use, and callback function pointers for functions to invoke
	// whenever the button state is checked, and the button is pressed and not pressed respectively, and a pointer to
	// a variable that the callback functions should operate on.
	button(const uint8_t monitored_input_pin, const unsigned long debounce_delay_ms, T* target_variable_pointer,
		const callback_func button_pressed_callback, const callback_func button_not_pressed_callback) : digital_input(monitored_input_pin)
	{
		this->debounce_delay_ms = debounce_delay_ms;
		button_state = last_button_state = digitalRead(monitored_pin);
		last_debounce_time_ms = millis();
		state_change_count = 0;

		target_variable_ptr = target_variable_pointer;
		button_pressed_func = button_pressed_callback;
		button_not_pressed_func = button_not_pressed_callback;

		pointers_null =
			target_variable_ptr == nullptr ||
			button_pressed_func == nullptr ||
			button_not_pressed_func == nullptr;
	}

	// Reads the monitored input pin, caps the result between the minimum and maximum value
	// and returns it. Will invoke the button_pressed_callback function if the button is pressed,
	// or the button_not_pressed_callback function if it isn't.
	int read_pin() override
	{
		const int reading = digitalRead(monitored_pin);

		// debounce protection - if debounce interval hasn't completed, simply return false.
		if (reading != last_button_state)
		{
			last_debounce_time_ms = millis();
			waiting_for_debounce = true;
		}

		if (waiting_for_debounce && (millis() - last_debounce_time_ms) > debounce_delay_ms)
		{
			if (reading != last_button_state)
			{
				state_change_count++;
				button_state = reading;
				waiting_for_debounce = false;

				// button callback functions should only be invoked if not set to nullptr, and only when the button changes state.
				// otherwise the callbacks should never be invoked, due to undefined behaviour. shame there is no null dereference operator
				// such as in c#.

				if (!pointers_null)
				{
					if (button_state == HIGH)
					{
						button_pressed_func(*target_variable_ptr);
					}
					else if (button_state == LOW)
					{
						button_not_pressed_func(*target_variable_ptr);
					}
				}
			}
		}

		last_button_state = reading;
		return button_state;
	}

	// Returns the number of times that the button has been pressed.
	unsigned int count()
	{
		read_pin();
		return state_change_count / 2;
	}
};

#endif
