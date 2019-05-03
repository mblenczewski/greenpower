//
//
//

#include "StateMachine.h"
#include "Greenpower.h"

transition::transition(state* ending_state)
{
	this->ending_state = ending_state;
}

state::state(const unsigned long state_duration_ms, const transition ending_transition, bool(*transition_predicate)(unsigned long),
	void(*action)(unsigned long))
{
	this->state_duration_ms = state_duration_ms;
	this->ending_transition = ending_transition;
	this->transition_predicate = transition_predicate;
	this->action = action;
}

state_machine::state_machine(const state states[])
{
	milliseconds = 0;

	const size_t arr_len = array_length(states);

	memcpy(state_array, states, arr_len);

	// If we have a starting state, use it.
	if (arr_len >= 1)
	{
		current_state = &state_array[0];
	}
	// Otherwise use a null state. Note that the state machine will be unusable.
	else
	{
		current_state = const_cast<state*>(&NULL_STATE);
	}
}

void state_machine::update_state(const unsigned long elapsed_time_ms)
{
	// Avoid handling null pointers; exceptional behaviour
	if (current_state == nullptr)
	{
		return;
	}

	// The current state is considered as expired if either its duration has been reached, or
	// the transition predicate given in the constructor returns true.
	const bool current_state_expired = current_state->state_duration_ms <= elapsed_time_ms ||
		current_state->check_predicate();

	// Transition to the new state
	if (current_state_expired)
	{
		state* new_state = current_state->ending_transition.ending_state;
		current_state = new_state;
	}
	else
	{
		current_state->invoke_action(elapsed_time_ms);
	}
}