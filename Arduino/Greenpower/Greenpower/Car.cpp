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

CarMode CarState::get_car_mode() const
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
	battery_level = analogRead(get_pin(Pins::Ammeter)) * analogRead(get_pin(Pins::Voltmeter));
	battery_percentage = static_cast<float>(battery_level) / static_cast<float>(BATTERY_CAPACITY);
}

void CarState::update_screen()
{
}