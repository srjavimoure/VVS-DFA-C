/**
 *	ALPHABET:
 *
 * 	Symbol set defining all the symbols accepted by a given DFA.
 */
#include "GenList.h"
#include "Symbol.h"

typedef GenList Alphabet;

/**
 * 	Inits a new alphabet
 */
extern Alphabet Alphabet_newAlphabet();

/**
 * 	Inits a new alphabet, with preallocated memory for a number of symbols.
 * You still can add more symbols later, it'll just allocate more memory for them.
 *
 * IN:
 * -The expected size of the alphabet, to have the memory already allocated.
 */
extern Alphabet Alphabet_newAlphabetWithSize(int size);

/**
 *	Adds a new symbol to this alphabet. Be careful, the alphabet WON'T check
 * if the new symbol is already in the alphabet (so there can be duplicates).
 *
 * IN:
 * -The alphabet.
 * -The symbol to add.
 */
extern void Alphabet_addNewSymbol(Alphabet this, Symbol symbol);

/**
 * 	Checks if a symbol is included in the alphabet.
 *
 * IN:
 * -The alphabet to check.
 * -The symbol to find.
 *
 * OUT:
 * -The symbol if found, NULL otherwise.
 */
extern Symbol Alphabet_getExistingObject(Alphabet this, Symbol symbol, char (*function)(void *a, void *b));

/**
 * 	Returns the GenList representing this alphabet. IT IS NOT A COPY, so any
 * changes made in the GenList returned will be reflected it the alphabet.
 */
extern GenList Alphabet_getAlphabet(Alphabet this);

/**
 * 	Returns the string representing the Alphabet.
 */
extern char *Alphabet_toString(Alphabet this);
