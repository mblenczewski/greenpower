//
//
//

#include "Button.h"
#include "Car.h"
#include "Display.h"

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
	const car_mode mode = get_car_mode();

	const float battery_energy = 0;
	const float battery_current = static_cast<float>(analogRead(get_pin(pins::ammeter)));
	const float battery_voltage = static_cast<float>(analogRead(get_pin(pins::voltmeter)));

	battery_level = battery_current * battery_voltage * static_cast<float>(delta_time_ms);
	battery_percentage = battery_level / BATTERY_CAPACITY;

	switch (mode)
	{
	case car_mode::idle:
		break;
	case car_mode::race:
		break;
	case car_mode::overtake:
		speed_controller = SPEED_CONTROLLER_MAX;
		break;
	default:
		break;
	}
}

void car_state::update_screen()
{
	update_buttons();

	car_mode mode = get_car_mode();

	// Display Settings. Measurements in pixels.

	// Border Settings.
	const int border_padding = 2, border_thickness = border_padding * 2 + 1, border_colour = GREEN;

	// Text Settings.
	const int text_start_x = border_thickness, text_start_y = border_thickness;
	const int text_height = lcd_display.get_font_height(), text_width = lcd_display.get_font_width();

	// Cache the display size in easy to use variable for convenience
	vec2<int> display_size = lcd_display.get_display_size();

	// Double the display_size width to correct for screen error.
	display_size.x *= 2;

	// Pretty Drawing of cars internal state :)

	// Draws a border with padding on all sides.
	lcd_display.draw_hollow_rectangle(border_padding, border_padding, display_size.x - 4, display_size.y - 4, border_colour);

	char battery_length_str[26];
	const float battery_level_normalised = battery_level * 100;

	sprintf(battery_length_str, "Battery Level: %d.%.2d", static_cast<int>(battery_level_normalised), static_cast<int>(battery_level_normalised * 100));

	// Writes the current batter percentage to the top of the screen.
	lcd_display.write(battery_length_str, text_start_x, text_start_y);

	char mode_str[26];
	char* car_mode_str;

	switch (mode) {
	case car_mode::idle:
		car_mode_str = "Idle";
		break;
	case car_mode::race:
		car_mode_str = "Race";
		break;
	case car_mode::overtake:
		car_mode_str = "Overtake";
		break;
	default:
		car_mode_str = "Invalid Mode";
		break;
	}

	sprintf(mode_str, "Mode: %s", car_mode_str);

	lcd_display.write(mode_str, text_start_x, text_start_y + text_height);
}