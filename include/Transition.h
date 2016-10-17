/**
 * 	TRANSITION:
 *
 * 	This data type represents a valid movement between two states, using a
 * input symbol.
 */
#include "GenList.h"
#include "State.h"
#include "Symbol.h"

typedef struct ST_Transition *Transition;

/**
 * 	Creates a new transition
 *
 * IN:
 * -The input symbol
 * -The initial state
 * -The ending state
 */
extern Transition Transition_newTransition(Symbol input, State initialState, State endState);

/**
 * 	Returns the initial state
 */
extern State Transition_getInitialState(Transition this);

/**
 * 	Returns the ending state
 */
extern State Transition_getEndingState(Transition this);

/**
 * 	Returns the input symbol
 */
extern Symbol Transition_getInputSymbol(Transition this);

/**
 * Returns the hashcode of this transition. This will be used by the equals()
 * method to determine if two given transitions are equal.
 */
extern int Transition_hashCode(Transition this);

/**
 * Determines if two given transitions are equal.
 */
extern char Transition_equals(void *this, void *other);

/**
 * Returns the String representation of this object
 */
extern char *Transition_toString(void *this);
