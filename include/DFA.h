/**
 * 	DFA:
 *
 * 	Defines a data type to represent a DFA
 */
#include "Alphabet.h"
#include "GenList.h"
#include "State.h"

typedef struct ST_DFA *DFA;

extern DFA DFA_newDFA(GenList states, Alphabet alph, State initialState,
					GenList finalStates, GenList transitions);

extern GenList DFA_getAllConnectedStates(DFA this);

extern DFA DFA_getConnectedDFA(DFA this);

extern char *DFA_getTransitionsTable(DFA this);

extern char *DFA_toString(DFA this);
