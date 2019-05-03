//
//
//

#include "Button.h"
#include "Car.h"

car_state::car_state()
{
	display.setup_display();
}

void car_state::update_buttons() const
{
	// Update the car's mode buttons
	for (button<bool>* button : mode_buttons)
	{
		button->check_button();
	}

	// Update the car's increment buttons
	for (button<int>* button : incrementation_buttons)
	{
		button->check_button();
	}
}

inline car_mode car_state::get_car_mode() const
{
	// Overtake mode trumps both idle mode and race mode
	if (in_overtake_mode)
	{
		return car_mode::overtake;
	}

	// Race mode trumps idle mode but not overtake mode
	if (in_race_mode)
	{
		return car_mode::race;
	}

	// Idle mode trumps no mode
	return car_mode::idle;
}

void car_state::next_tick(const unsigned long delta_time_ms)
{
	update_buttons();

	const car_mode mode = get_car_mode();

	const float battery_energy = 0;
	const float battery_current = static_cast<float>(analogRead(get_pin(pins::ammeter)));
	const float battery_voltage = static_cast<float>(analogRead(get_pin(pins::voltmeter)));

	battery_level = battery_current * battery_voltage * static_cast<float>(delta_time_ms);
	battery_percentage = battery_level / BATTERY_CAPACITY;
}

void car_state::update_screen()
{
	update_buttons();

	car_mode mode = get_car_mode();

	/* Display Settings. Measurements in pixels. */

	/* Border Settings. */
	const int border_thickness = 4, border_padding = 2, border_colour = GREEN;

	/* Text Settings. */
	const int text_start_x = 2 * border_padding + border_thickness, text_start_y = text_start_x;

	// Cache the display size in easy to use variable for convenience
	const vec2<int> display_size = display.get_display_size();

	/* Pretty Drawing of cars internal state :) */

	// Draws a border with padding on all sides.
	display.draw_hollow_rectangle(border_padding, border_padding,
		display_size.x - 2 * border_padding, display_size.y - 2 * border_padding, border_colour);

	char* battery_level_str = new char[30];
	sprintf(battery_level_str, "Battery Percentage: %f#000.1", battery_percentage);

	// Writes the current batter percentage to the top of the screen.
	display.write(battery_level_str, text_start_x, text_start_y);
}