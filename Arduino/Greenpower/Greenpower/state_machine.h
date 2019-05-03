// StateMachine.h

#ifndef _STATEMACHINE_h
#define _STATEMACHINE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Represents a single state of a state machine.
struct State;

// Represents a transition to a new state.
struct Transition;

struct Transition
{
	// The final state for this transition.
	State* ending_state;

	// Initialises a null instance of the Transition struct.
	Transition()
	{
		ending_state = nullptr;
	}

	// Initialises a new instance of the Transition struct.
	Transition(State* ending_state);
};

// Represents a null transition.
const Transition NULL_TRANSITION{};

struct State
{
	// The time for which the state is active, in milliseconds.
	unsigned long state_duration_ms;

	// The transition to be performed when the state ends its allotted time slice.
	Transition ending_transition;

	// The action to perform whilst the state is active. Will be invoked whenever the state machine
	// assigned this state updates itself, and finds that this state's duration has not yet elapsed.
	// Takes the remaining duration (in milliseconds) as an argument.
	void(*action)(unsigned long);

	// Initialises a null instance of the State struct.
	State()
	{
		state_duration_ms = 0;
		ending_transition = NULL_TRANSITION;
		action = nullptr;
	}

	// Initialises a new instance of the State struct.
	State(unsigned long state_duration_ms, Transition ending_transition, void(*action)(unsigned long));

	// Reduces the remaining duration by the given elapsed time, and invokes the action associated with the
	// state with the remaining duration.
	void invoke_action(const unsigned long elapsed_time_ms)
	{
		state_duration_ms -= elapsed_time_ms;
		action(state_duration_ms);
	}
};

// Represents a null state.
const State NULL_STATE{};

// Represents a state machine, holding an array of states and an array of transitions between those states.
class state_machine
{
private:
	// The amount of milliseconds that have elapsed since the Arduino was started..
	unsigned long long milliseconds;

	// The current state of the state machine.
	State* current_state;

	// The state array, storing all possible states for this state machine.
	State state_array[];

public:
	// Initialises a new instance of the StateMachine class.
	// Sets up the state array and initialises the current state to the first element in the state array.
	state_machine(const State states[]);

	// Updates the internal state of the state machine. Given the milliseconds from Arduino power-on (using millis()),
	// will update the internal state of the state machine. If the current state has expired will transition to the next
	// state.
	void update_state(unsigned long elapsed_time_ms);
};

#endif
