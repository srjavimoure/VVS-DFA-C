/**
 * STATE:
 *
 * 	This data type represents one of the nodes of a given DFA.
 */

typedef struct ST_State *State;
 
/**
 * 	Creates a new state based on a char secuence (the state allocates its own
 * memory).
 *
 * IN:
 * 	-The char sequence that will represent the state.
 *
 * OUT:
 * 	-The state itself.
 */
extern State State_newState(char *sequence);

/**
 * Returns the char sequence that represents this state
 */
extern char *State_getState(State this);

/**
 * Returns the hashcode of this state. This will be used by the equals()
 * method to determine if two given states are equal.
 */
extern int State_hashCode(State this);

/**
 * Determines if two given states are equal.
 */
extern char State_equals(void *this, void *other);

/**
 * Returns the String representation of this object
 */
extern char *State_toString(void *this);

/**
 * Frees the memory used by this State and sets the pointer to null
 */
extern void State_destroy(State *this);
