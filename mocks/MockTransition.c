#include <stdlib.h>
#include <string.h>

struct ST_Transition {
	Symbol input;
	State initialState;
	State endingState;
};
typedef struct ST_Transition *Transition;

Transition Transition_newTransition(Symbol input, State initialState, State endState) {

	return NULL;
}

State Transition_getInitialState(Transition this) {
	return NULL;
}

State Transition_getEndingState(Transition this) {
	return NULL;
}

Symbol Transition_getInputSymbol(Transition this) {
	return NULL;
}

int Transition_hashCode(Transition this) {

	return -1;
}

char Transition_equals(void *this, void *other) {
	
	return 0;

}

char *Transition_toString(void *this) {

	return NULL;
}
