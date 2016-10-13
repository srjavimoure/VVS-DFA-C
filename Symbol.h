/**
 * SYMBOL:
 *
 * 	This data type represents one of the input possibilities of any
 * given DFA.
 */

typedef struct ST_Symbol *Symbol;
 
/**
 * 	Creates a new symbol based on a char secuence (the symbol allocates its own
 * memory).
 *
 * IN:
 * 	-The char sequence that will represent the symbol.
 *
 * OUT:
 * 	-The symbol itself.
 */
extern Symbol Symbol_newSymbol(char *sequence, int size);

/**
 * Returns the char sequence that represents this symbol
 */
extern char *Symbol_getSymbol(Symbol this);

/**
 * Returns the hashcode of this symbol. This will be used by the equals()
 * method to determine if two given symbols are equal.
 */
extern int Symbol_hashCode(Symbol this);

/**
 * Determines if two given symbols are equal.
 */
extern char Symbol_equals(void *this, void *other);

/**
 * Returns the String representation of this object
 */
extern char *Symbol_toString(Symbol this);
