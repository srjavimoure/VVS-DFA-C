#include <stdlib.h>
#include <string.h>
#include "../include/Symbol.h"

struct ST_Symbol {
	int32_t size;
	char *sequence;
};

typedef struct ST_Symbol *Symbol;

Symbol Symbol_newSymbol(char *sequence) {

	// Esto cascaría fuertemente si dejase que haga strlen de NULL
	if (sequence == NULL)	return NULL;

	Symbol this = (Symbol) malloc(sizeof(struct ST_Symbol));

	if (this == NULL)	return NULL;

	this->size = strlen(sequence);
	this->sequence = (char *) malloc(sizeof(char) * this->size);

	if (this->sequence == NULL)	return NULL;

	memcpy(this->sequence, sequence, this->size);

	return this;
}

char *Symbol_getSymbol(Symbol this) {

	return this->sequence;
}

int Symbol_hashCode(Symbol this) {

	int32_t hash = 13;
	int i;
	for (i = 0; i < this->size; i++) {
		hash = 79 * hash + this->sequence[i] * 19;
	}

	return hash;
}

char Symbol_equals(void *this, void *other) {

	// Reference equality
	if (this == other) {
		return 1;
	}

	Symbol th = (Symbol) this;
	Symbol ot = (Symbol) other;

	if (Symbol_hashCode(th) != Symbol_hashCode(ot)) {
		return 0;
	}

	if(th->size == ot->size
	&& memcmp(th->sequence, ot->sequence, th->size) == 0) {
		return 1;
	}

	return 0;

}

char *Symbol_toString(Symbol this) {

	return this->sequence;
}

