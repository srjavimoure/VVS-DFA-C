#include <stdlib.h>
#include <string.h>
#include "../include/State.h"

struct ST_State {
	int32_t size;	// Explicitly-defined size for memory aligment purposes
	char *sequence;
};

typedef struct ST_State *State;

State State_newState(char *sequence) {

	// Esto cascaría fuertemente si dejase que haga strlen de NULL
	if (sequence == NULL)	return NULL;

	State this = (State) malloc(sizeof(struct ST_State));

	if (this == NULL)	return NULL;

	this->size = strlen(sequence);

	// Cadena vacía
	if (this->size == 0) {
		this->sequence = (char *) malloc(sizeof(char));
		this->sequence[0] = '\0';
	}
	else {
		this->sequence = (char *) malloc(sizeof(char) * this->size);
	}
	if (this->sequence == NULL)	return NULL;

	memcpy(this->sequence, sequence, this->size);

	return this;
}

char *State_getState(State this) {

	return this->sequence;
}

int State_hashCode(State this) {

	int32_t hash = 17;
	int i;
	for (i = 0; i < this->size; i++) {
		hash = 23 * hash + this->sequence[i] * 11;
	}

	return hash;
}

char State_equals(void *this, void *other) {

	// Reference equality
	if (this == other)	return 1;

	if (this == NULL || other == NULL)	return 0;

	State th = (State) this;
	State ot = (State) other;

	if (State_hashCode(th) != State_hashCode(ot)) {
		return 0;
	}

	if(th->size == ot->size
	&& memcmp(th->sequence, ot->sequence, th->size) == 0) {
		return 1;
	}

	return 0;

}

char *State_toString(void *this) {

	return ((State) this)->sequence;
}
