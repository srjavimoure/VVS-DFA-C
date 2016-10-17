/**
 * 	DFA:
 *
 * 	Defines a data type to represent a DFA
 */
#include <stdlib.h>
#include <string.h>
#include "Transition.h"
#include "Alphabet.h"
#include "GenList.h"
#include "Symbol.h"
#include "State.h"

struct ST_DFA {
	GenList states;
	Alphabet alph;
	State initialState;
	GenList finalStates;
	GenList transitions;
};
typedef struct ST_DFA *DFA;

DFA DFA_newDFA(GenList states, Alphabet alph, State initialState,
		GenList finalStates, GenList transitions) {

	DFA dfa = malloc(sizeof(struct ST_DFA));

	if (dfa == NULL)	return NULL;

	dfa->states = states;
	dfa->alph = alph;
	dfa->initialState = initialState;
	dfa->finalStates = finalStates;
	dfa->transitions = transitions;

	return dfa;
}

GenList DFA_getAllConnectedStates(DFA this) {

	GenList visitedStates = GenList_newGenList(GenList_getSize(this->states));
	GenList_add(visitedStates, this->initialState);

	GenList statesQueue = GenList_newGenList(GenList_getSize(this->states));
	GenList_add(statesQueue, this->initialState);

	GenList alphabetList = GenList_newGenList(GenList_getSize(this->alph));
	int i;
	for (i = 0; i < GenList_getSize(this->alph); i++) {
		GenList_add(alphabetList, GenList_getElement(this->alph, i));
	}

	State currentState;
	Transition rTransition;
	
	// Breadth First Search
	while (GenList_getSize(statesQueue)) {

		// Taking the head
		currentState = GenList_getElement(statesQueue, 0);
		GenList_remove(statesQueue, 0);

		for(i = 0; i < GenList_getSize(alphabetList); i++) {
			Symbol symbol = GenList_getElement(alphabetList, i);

			Transition t = Transition_newTransition(symbol, currentState, NULL);

			rTransition = (Transition) GenList_getExistingObject(this->transitions, t, Transition_equals);
			if (rTransition != NULL) {
				State end = Transition_getEndingState(rTransition);
				if (GenList_getExistingObject(visitedStates, end, State_equals) == NULL) {
					GenList_add(visitedStates, end);
					GenList_add(statesQueue, end);
				}
			}
		}
	}

	return visitedStates;
}

DFA DFA_getConnectedDFA(DFA this) {

	GenList q = DFA_getAllConnectedStates(this); // Connected states
	
	/* Build the new connected DFA */

	// F (get rid of unreachable states)
	int i;
	GenList f = GenList_newGenList(GenList_getSize(this->finalStates));
	for (i = 0; i < GenList_getSize(this->finalStates); i++) {
		State s = GenList_getElement(this->finalStates, i);
		// This final state does not exist in the connected states list
		if (GenList_getExistingObject(q, s, State_equals) != NULL) {
			GenList_add(f, s);
		}
	}

	GenList t = GenList_newGenList(GenList_getSize(this->transitions));
	for (i = 0; i < GenList_getSize(this->transitions); i++) {
		Transition tr = GenList_getElement(this->transitions, i);
		// This final state does not exist in the connected states list
		if (GenList_getExistingObject(q, Transition_getInitialState(tr), State_equals) != NULL) {
			GenList_add(t, tr);
		}
	}

	return DFA_newDFA(q, this->alph, this->initialState, f, t);
}

char *DFA_getTransitionsTable(DFA this) {

	char *string = (char *) malloc(sizeof(char) * 1000);

	GenList tr = this->transitions;

	string = strcat(string, "\n|\t");

	// Alphabet
	int i;
	for (i = 0; i < GenList_getSize(tr); i++) {
		Transition t = (Transition) GenList_getElement(tr, i);
		string = strcat(string, Symbol_toString(Transition_getInputSymbol(t)));
		string = strcat(string, "\t|\t");
	}

	return string;

}

char *DFA_toString(DFA this) {

	char *string = (char *) malloc(sizeof(char) * 1000);

	// States
	string = strcat(string, "DFA{\n   States{");
	int i;
	for (i = 0; i < GenList_getSize(this->states); i++) {
		string = strcat(string, State_toString(GenList_getElement(this->states, i)));
		if (i != GenList_getSize(this->states)-1)	string = strcat(string, ", ");
	}

	// Initial state
	string = strcat(string, "}\n   Initial{");
	string = strcat(string, State_toString(this->initialState));

	// Final states
	string = strcat(string, "}\n   Final");
	string = strcat(string, GenList_toString(this->finalStates, State_toString));

	// Alphabet
	string = strcat(string, "\n   ");
	string = strcat(string, Alphabet_toString(this->alph));

	// Transitions
	string = strcat(string, "\n   Transitions{");

	for (i = 0; i < GenList_getSize(this->transitions); i++) {
		string = strcat(string, Transition_toString(GenList_getElement(this->transitions, i)));
		if (i != GenList_getSize(this->transitions)-1)	string = strcat(string, ", ");
	}

	string = strcat(string, "}\n}");

	return string;
}
