#include <stdlib.h>
#include <string.h>

struct ST_State {
	int32_t size;	// Explicitly defined size for memory aligment purposes
	char *sequence;
};
typedef struct ST_State *State;

State State_newState(char *sequence, int size) {

	return NULL;
}

char *State_getState(State this) {

	return NULL;
}

int State_hashCode(State this) {

	return -1;
}

char State_equals(void *this, void *other) {

	return 0;

}

char *State_toString(void *this) {

	return NULL;
}
