//
//
//

#include "Car.h"

CarState::CarState()
{
	display.setup_display();
}

void CarState::next_tick()
{
	battery_level = analogRead(get_pin(Pins::Ammeter)) * analogRead(get_pin(Pins::Voltmeter));
	battery_percentage = static_cast<float>(battery_level) / static_cast<float>(BATTERY_CAPACITY);
}

void CarState::update_screen()
{
}