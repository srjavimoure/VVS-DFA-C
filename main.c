#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Symbol.h"
#include "State.h"
#include "Alphabet.h"
#include "Transition.h"
#include "GenList.h"
#include "DFA.h"

DFA DFAasString(char *string) {

	if (string == NULL) {
		printf("You need to give a dfa as input\n");
	}

	char *buffer = malloc(sizeof(char) * 100);

	// States
	int i = 0, u = 0;
	GenList states = GenList_newGenList(10);
	while(string[i] != ';') {
		if(string[i] == ' ') {
			if (u != 0)	GenList_add(states, State_newState(buffer, u));
			u = 0;
		}
		else {
			buffer[u++] = string[i];
		}
		i++;
	}
	i++;

	if (u != 0) {
		GenList_add(states, State_newState(buffer, u));
		u = 0;
	}

	printf("%s\n", GenList_toString(states, State_toString));

	// Alphabet
	GenList alph = Alphabet_newAlphabet();
	while(string[i] != ';') {
		if(string[i] == ' ') {
			if (u != 0)	Alphabet_addNewSymbol(alph, Symbol_newSymbol(buffer, u));
			u = 0;
		}
		else {
			buffer[u++] = string[i];
		}
		i++;
	}
	i++;

	if (u != 0) {
		Alphabet_addNewSymbol(alph, Symbol_newSymbol(buffer, u));
		u = 0;
	}

	printf("%s\n", Alphabet_toString(alph));

	// Initial state
	while(string[i] != ';') {
		if (string[i] != ' ')	buffer[u++] = string[i];
		i++;
	}
	i++;

	State initial = State_newState(buffer, u);
	u = 0;

	printf("%s\n", State_toString(initial));

	// Final states
	GenList final = GenList_newGenList(10);
	while(string[i] != ';') {
		if(string[i] == ' ') {
			if (u != 0)	GenList_add(final, State_newState(buffer, u));
			u = 0;
		}
		else {
			buffer[u++] = string[i];
		}
		i++;
	}
	i++;

	if (u != 0) {
		GenList_add(final, State_newState(buffer, u));
		u = 0;
	}

	printf("%s\n", GenList_toString(final, State_toString));


	// Transitions
	GenList trans = GenList_newGenList(20);
	State begin, end;
	Symbol input;
	int j = 0;
	while(string[i] != '\0') {

		while(string[i] == ' ' || string[i] == ';') {
			i++;
		}

		while(string[i] != ' ') {
			buffer[u++] = string[i];
			i++;
		}
		begin = State_newState(buffer, u);
		u = 0;
		i++;

		while(string[i] != ' ') {
			buffer[u++] = string[i];
			i++;
		}
		end = State_newState(buffer, u);
		u = 0;
		i++;

		while(string[i] != ';') {
			buffer[u++] = string[i];
			i++;
		}
		
		input = Symbol_newSymbol(buffer, u);
		u = 0;
		i++;

		GenList_add(trans, Transition_newTransition(input, begin, end));

		i++;
	}

	printf("%s\n", GenList_toString(trans, Transition_toString));

	return DFA_newDFA(states, alph, initial, final, trans);
}

DFA DFAasFile(char *filename) {

	FILE *file = fopen(filename, "r");

	if (file == NULL) {
		printf("Could not open file\n");
		return NULL;
	}

	char *string = malloc(sizeof(char)*100);
	int i = 0;
	char c = 'a';
	int size = 100;
	while (c != EOF) {
		c = fgetc(file);
		string[i++] = c;
		if (i == size) {
			size += 100;
			string = realloc(string, sizeof(char) * size);
		}
	}
	string[i-1] = '\0';

	printf("%s", string);

	return DFAasString(string);
}

int main(int argc, char **argv)
{

	DFA dfa;

	// The dfa was given as a file
	if (argc > 1 && strcmp(argv[1], "-f") == 0) {
		dfa = DFAasFile(argv[2]);
		if (dfa == NULL) {
			return -1;
		}
	}
	// The dfa was given as a string
	else {
		dfa = DFAasString(argv[1]);
		if (dfa == NULL) {
			return -1;
		}
	}
	
	printf("**--INPUT DFA--**\n%s\n", DFA_toString(dfa));

	DFA conDfa = DFA_getConnectedDFA(dfa);

	printf("**--OUTPUT DFA--**\n%s\n", DFA_toString(conDfa));

	return 0;
}

