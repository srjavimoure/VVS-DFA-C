#include <string.h> // Defines NULL
#include <stdlib.h>

#ifndef ALBUFFER
	#define ALBUFFER 5
#endif

typedef GenList Alphabet;

Alphabet Alphabet_newAlphabet() {
	return NULL;
}

Alphabet Alphabet_newAlphabetWithSize(int size) {
	return NULL;
}

void Alphabet_addNewSymbol(Alphabet this, Symbol symbol) {
	return;
}

Symbol Alphabet_getExistingObject(Alphabet this, Symbol symbol, char (*function)(void *a, void *b)) {
	return NULL;
}

GenList Alphabet_getAlphabet(Alphabet this) {
	return NULL;
}

char *Alphabet_toString(Alphabet this) {

	return NULL;
}
