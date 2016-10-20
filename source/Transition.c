#include <stdlib.h>
#include <string.h>
#include "../include/State.h"
#include "../include/Symbol.h"
#include "../include/Transition.h"

struct ST_Transition {
	Symbol input;
	State initialState;
	State endingState;
};
typedef struct ST_Transition *Transition;

Transition Transition_newTransition(Symbol input, State initialState, State endState) {

	Transition trans = malloc(sizeof(struct ST_Transition));

	if (trans == NULL)	return NULL;

	trans->input = input;
	trans->initialState = initialState;
	trans->endingState = endState;

	return trans;
}

State Transition_getInitialState(Transition this) {
	return this->initialState;
}

State Transition_getEndingState(Transition this) {
	return this->endingState;
}

Symbol Transition_getInputSymbol(Transition this) {
	return this->input;
}

int Transition_hashCode(Transition this) {

	int32_t hash = 13;
	hash = 79 * hash + Symbol_hashCode(this->input) * 19;
	hash = 79 * hash + State_hashCode(this->initialState) * 19;
	hash = 79 * hash + State_hashCode(this->endingState) * 19;

	return hash;
}

char Transition_equals(void *this, void *other) {
	
	// Reference equality
	if (this == other) {
		return 1;
	}

	Transition th = (Transition) this;
	Transition ot = (Transition) other;

	// For our algorithm, we are only interested in check that the initial
	// states AND the input are equal.
	return State_equals(th->initialState, ot->initialState)
		&& Symbol_equals(th->input, ot->input);

}

char *Transition_toString(void *this) {

	int size = 100;

	char *string = malloc(sizeof(char) * size);

	Transition th = (Transition) this;

	string = strcat(string, State_toString(th->initialState));
	string = strcat(string, "->");
	string = strcat(string, State_toString(th->endingState));
	string = strcat(string, " USING ");
	string = strcat(string, Symbol_toString(th->input));

	return string;
}
