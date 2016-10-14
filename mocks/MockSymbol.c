#include <string.h>
#include <stdlib.h>

struct ST_Symbol {
	int32_t size;
	char *sequence;
};
typedef struct ST_Symbol *Symbol;

Symbol Symbol_newSymbol(char *sequence, int size) {

	return NULL;
}

char *Symbol_getSymbol(Symbol this) {

	return NULL;
}

int Symbol_hashCode(Symbol this) {

	return -1;
}

char Symbol_equals(void *this, void *other) {

	return 0;

}

char *Symbol_toString(Symbol this) {

	char *value = (char *) malloc(sizeof(char) * 13);
	strcpy(value, "SymbolString");

	return value;
}

