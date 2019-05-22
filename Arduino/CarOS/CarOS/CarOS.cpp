//
//
//

#include "CarOS.h"
#include "builtin_button_callbacks.h"
#include "inputs.h"

// Microseconds for event loop - currently 100Hz
const long EVENT_TICK_MICROS = 10000L;

// Records idle time during event loop in microseconds
long idle_time = 0;

int press_counter = 0;
button<int> incrementer{ A1, &press_counter, &increment_by_1_debug, &null_func };

pwm_input pwm_reader{ 21, nullptr, RISING }; // on an arduino mega, pin 21 has interrupt functionality

input* inputs[] = { &incrementer, &pwm_reader };

int t = 0;

long rpm_from_pwm(long pwm) {
  return (60 * 1000000L) / pwm;
}

int loop_()
{
	// read inputs and update their state; buttons will invoke callback functions
	for (input* input_ : inputs)
	{
		input_->read_pin();
	}

  if((t % 20) == 0) {
    Serial.print("RPM:");
    Serial.print(rpm_from_pwm(pwm_reader.read_pwm()));
    Serial.print(" Idle:");
    Serial.print(idle_time);
    Serial.println();
  }

  t++;
	return 0;
}

int main()
{
	init();

  // Setup
	Serial.begin(115200);
	Serial.println("Hello, World!");

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  accurate_microsecond_timer.setup();

  // Event loop 
  unsigned long tick = micros();
  
	for (;;)
	{
		const int ret_code = loop_();

		if (ret_code != 0)
		{
			Serial.print("Error, non-zero return code: ");
			Serial.println(ret_code, DEC);
#ifdef _DEBUG
			break;
#endif
		}

    // When should next loop run?
    tick += EVENT_TICK_MICROS;

    // Record time left (or overrun if -ve)
    idle_time = (long)(tick - micros());

    // Wait until next loop (cast to signed to cope with wraparound)
    //
    // XXX If power becomes an issue, use a timer interrupt for event tick, and 'sleep' instruction here
    //
    while( (long)(micros() - tick) < 0)
      ; 
	}

	Serial.println("Goodbye, World!");
	Serial.flush();
	return 0;
}
