#include <stdlib.h>
#include <string.h>

#ifndef DEFBUFFER
	#define DEFBUFFER 5
#endif

struct ST_GenList {
	int32_t size;
	int32_t buffer;
	int32_t realSize; // Allocated size of the list, in bytes.
	void **list;
};
typedef struct ST_GenList *GenList;


GenList GenList_newGenList(int buffer) {

	return NULL;
}

int GenList_getSize(GenList this) {

	return 0;
}

void GenList_add(GenList this, void *element) {

	return;
}

void GenList_remove(GenList this, int position) {

	return;
}

void *GenList_getElement(GenList this, int position) {

	return NULL;
}

void *GenList_getExistingObject(GenList this, void *element, char (*function)(void *a, void *b)) {

	return NULL;
}

void GenList_clearNulls(GenList this) {

	return;
}

char *GenList_toString(GenList this, char *(*toString)(void *element)) {

	char *string = (char *) malloc(sizeof(char) * 100);

	string = strcpy(string, "GenListString");

	return string;
}
