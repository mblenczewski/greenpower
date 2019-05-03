// StateMachine.h

#ifndef _STATEMACHINE_h
#define _STATEMACHINE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Represents a single, basic state of a state machine.
// Supports a transition predicate, and a duration. Additional functionality can be implemented
// by inheriting State and adding extra checks.
struct state;

// Represents a transition to a new state.
struct transition;

struct transition
{
	// The final state for this transition.
	state* ending_state;

	// Initialises a null instance of the Transition struct.
	transition()
	{
		ending_state = nullptr;
	}

	// Initialises a new instance of the Transition struct.
	transition(state* ending_state);
};

// Represents a null transition.
const transition NULL_TRANSITION{};

struct state
{
private:
	// The predicate that determines whether to transition to the next state. Invoked with the current
	// remaining duration (in milliseconds) as an argument.
	bool(*transition_predicate)(unsigned long);

	// The action to perform whilst the state is active. Will be invoked whenever the state machine
	// assigned this state updates itself, and finds that this state's duration has not yet elapsed.
	// Takes the remaining duration (in milliseconds) as an argument.
	void(*action)(unsigned long);

public:
	// The time for which the state is active, in milliseconds.
	unsigned long state_duration_ms;

	// The transition to be performed when the state ends its allotted time slice.
	transition ending_transition;

	// Initialises a null instance of the State struct.
	state()
	{
		state_duration_ms = 0;
		ending_transition = NULL_TRANSITION;
		transition_predicate = nullptr;
		action = nullptr;
	}

	// Initialises a new instance of the State struct.
	state(unsigned long state_duration_ms, transition ending_transition, bool(*transition_predicate)(unsigned long),
		void(*action)(unsigned long));

	// Destroys the State instance, and frees up any used resources.
	virtual ~state() = default;

	// Checks whether the transition predicate given in the constructor has had its conditions met. Uses the
	// current remaining state duration as argument to the transition predicate. When overriden by a child class,
	// base->check_predicate(elapsed_time_ms) should be invoked.
	virtual bool check_predicate() const
	{
		return transition_predicate(state_duration_ms);
	}

	// Reduces the remaining duration by the given elapsed time, and invokes the action associated with the
	// state with the remaining duration. When overriden by a child class, base->invoke_action(elapsed_time_ms)
	// should be invoked.
	virtual void invoke_action(const unsigned long elapsed_time_ms)
	{
		state_duration_ms -= elapsed_time_ms;
		action(state_duration_ms);
	}
};

// Represents a null state.
const state NULL_STATE{};

// Represents a state machine, holding an array of states and an array of transitions between those states.
class state_machine
{
private:
	// The amount of milliseconds that have elapsed since the Arduino was started..
	unsigned long long milliseconds;

	// The current state of the state machine.
	state* current_state;

	// The state array, storing all possible states for this state machine.
	state state_array[];

public:
	// Initialises a new instance of the StateMachine class.
	// Sets up the state array and initialises the current state to the first element in the state array.
	state_machine(const state states[]);

	// Updates the internal state of the state machine. Given the milliseconds from Arduino power-on (using millis()),
	// will update the internal state of the state machine. If the current state has expired will transition to the next
	// state.
	void update_state(unsigned long elapsed_time_ms);
};

#endif
