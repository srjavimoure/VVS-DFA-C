#include <stdlib.h>
#include <string.h>
#include "../include/GenList.h"

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

	GenList genList = (GenList) malloc(sizeof(struct ST_GenList));

	if (genList == NULL)	return NULL;

	genList->buffer = buffer <= 0 ? DEFBUFFER : buffer;
	genList->size = 0;
	genList->realSize = genList->buffer;

	genList->list = (void *) malloc(sizeof(void *) * genList->realSize);

	if (genList->list == NULL)	return NULL;

	return genList;
}

int GenList_getBuffer(GenList this) {

	if (this == NULL)	return -1;

	return this->buffer;
}

int GenList_getSize(GenList this) {

	if (this == NULL)	return -1;

	return this->size;
}

void GenList_add(GenList this, void *element) {

	if (this == NULL || element == NULL)	return;

	// Inserting the element goes FIRST to adding to the size
	this->list[this->size++] = element;

	if (this->size >= this->realSize) {
		this->realSize += this->buffer;
		this->list = realloc(this->list, sizeof(void *) * this->realSize);
	}

	return;
}

void GenList_remove(GenList this, int position) {

	if (this == NULL)	return;

	// Index out of bounds
	if (position < 0 || position > this->size)	return;

	int i;
	for (i = position; i < this->size - 1; i++) {
		this->list[i] = this->list[i+1];
	}

	this->list[i] = NULL;
	this->size--;

	// Free excess of space
	if (this->realSize > this->size + this->buffer) {
		this->realSize = this->size + this->buffer;
		this->list = realloc(this->list, this->realSize);
	}

	return;
}

void *GenList_getElement(GenList this, int position) {

	if (this == NULL)	return NULL;

	// Index out of bounds
	if (position < 0 || position > this->size)	return NULL;

	return this->list[position];
}

void *GenList_getExistingObject(GenList this, void *element, char (*function)(void *a, void *b)) {

	if (this == NULL || element == NULL || function == NULL)	return NULL;

	int i = 0;
	for (i = 0; i < this->size; i++) {
		if (function(this->list[i], element) != 0) {
			return this->list[i];
		}
	}

	return NULL;
}

char *GenList_toString(GenList this, char *(*toString)(void *element)) {

	if (this == NULL || toString == NULL)	return NULL;

	char *string = (char *) malloc(sizeof(char) * 100);

	string = strcpy(string, "{");

	int i;
	for (i = 0; i < GenList_getSize(this); i++) {
		string = strcat(string, toString(GenList_getElement(this, i)));
		if (i != GenList_getSize(this)-1)	string = strcat(string, ", ");
	}

	string = strcat(string, "}");

	return string;
}
