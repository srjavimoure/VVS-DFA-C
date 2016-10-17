#include <string.h> // Defines NULL
#include <stdlib.h>
#include "Alphabet.h"
#include "GenList.h"
#include "Symbol.h"

#ifndef ALBUFFER
	#define ALBUFFER 5
#endif

typedef GenList Alphabet;

Alphabet Alphabet_newAlphabet() {
	return GenList_newGenList(ALBUFFER);
}

Alphabet Alphabet_newAlphabetWithSize(int size) {
	return GenList_newGenList(size);
}

void Alphabet_addNewSymbol(Alphabet this, Symbol symbol) {
	GenList_add(this, symbol);
}

Symbol Alphabet_getExistingObject(Alphabet this, Symbol symbol, char (*function)(void *a, void *b)) {
	return GenList_getExistingObject(this, symbol, function);
}

GenList Alphabet_getAlphabet(Alphabet this) {
	return (GenList) this;
}

char *Alphabet_toString(Alphabet this) {

	char *string = (char *) malloc(sizeof(char) * 100);

	string = strcat(string, "Alphabet{");

	GenList gl = Alphabet_getAlphabet(this);

	int i;
	for (i = 0; i < GenList_getSize(gl); i++) {
		string = strcat(string, Symbol_toString(GenList_getElement(gl, i)));
		if (i != GenList_getSize(gl)-1)	string = strcat(string, ", ");
	}

	string = strcat(string, "}");

	return string;
}
