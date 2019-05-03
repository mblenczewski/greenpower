//
//
//

#include "Button.h"
#include "Car.h"

CarState::CarState()
{
	display.setup_display();
}

void CarState::update_buttons() const
{
	// Update the car's mode buttons
	for (Button<bool>* button : mode_buttons)
	{
		button->check_button();
	}

	// Update the car's increment buttons
	for (Button<int>* button : incrementation_buttons)
	{
		button->check_button();
	}
}

inline CarMode CarState::get_car_mode() const
{
	// Overtake mode trumps both idle mode and race mode
	if (in_overtake_mode)
	{
		return CarMode::Overtake;
	}

	// Race mode trumps idle mode but not overtake mode
	if (in_race_mode)
	{
		return CarMode::Race;
	}

	// Idle mode trumps no mode
	return CarMode::Idle;
}

void CarState::next_tick()
{
	update_buttons();

	CarMode mode = get_car_mode();

	battery_level = analogRead(get_pin(Pins::Ammeter)) * analogRead(get_pin(Pins::Voltmeter));
	battery_percentage = static_cast<float>(battery_level) / static_cast<float>(BATTERY_CAPACITY);
}

void CarState::update_screen()
{
	update_buttons();

	CarMode mode = get_car_mode();

	/* Display Settings. Measurements in pixels. */

	/* Border Settings. */
	const int border_thickness = 4, border_padding = 2, border_colour = GREEN;

	/* Text Settings. */
	const int text_start_x = 2 * border_padding + border_thickness, text_start_y = text_start_x;

	// Cache the display size in easy to use variable for convenience
	const vector2<int> display_size = display.get_display_size();

	/* Pretty Drawing of cars internal state :) */

	// Draws a border with padding on all sides.
	display.draw_hollow_rectangle(border_padding, border_padding,
		display_size.x - 2 * border_padding, display_size.y - 2 * border_padding, border_colour);

	char* battery_level_str = new char[30];
	sprintf(battery_level_str, "Battery Percentage: %f#000.1", battery_percentage);

	// Writes the current batter percentage to the top of the screen.
	display.write(battery_level_str, text_start_x, text_start_y);
}