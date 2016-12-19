#include <string.h>
#include "../include/Symbol.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Symbol);

TEST_SETUP(Symbol) {}

TEST_TEAR_DOWN(Symbol) {}

/**********************************************

	PRUEBAS CON UNITY PARA EL MÓDULO SYMBOL

**********************************************/


/*  C-SYM-NEW-01  */
TEST(Symbol, test_NewSymbolWithNullSequence)
{
	TEST_ASSERT_NULL_MESSAGE(Symbol_newSymbol(NULL),
		"C-SYM-NEW-01: Symbol not null");
}

/*  C-SYM-NEW-02  */
TEST(Symbol, test_NewSymbolWithVoidSequence)
{

	Symbol s = Symbol_newSymbol("");

	TEST_ASSERT_NOT_NULL_MESSAGE(s,
		"C-SYM-NEW-02: Symbol is null with \"\" string");
	TEST_ASSERT_EQUAL_STRING_MESSAGE(Symbol_getSymbol(s), "",
		"C-SYM-NEW-02: Strings are not equal");
	TEST_ASSERT_EQUAL_INT_MESSAGE(strlen(Symbol_getSymbol(s)), 0,
		"C-SYM-NEW-02: Strings have different length");

	Symbol_destroy(&s);

}

/*  C-SYM-GSYM-01  */
TEST(Symbol, test_GetSymbolFromNull)
{
	TEST_ASSERT_NULL_MESSAGE(Symbol_getSymbol(NULL),
		"C-SYM-GSYM-01: Symbol not null");
}

/*  C-SYM-HASH-02  */
TEST(Symbol, test_HashCodeFromNull)
{
	TEST_ASSERT_EQUAL_INT_MESSAGE(Symbol_hashCode(NULL), -1,
		"C-SYM-HASH-02: Hashcode for null is not -1");
}

/*  C-SYM-EQ-04  */
TEST(Symbol, test_EqualToNullObject)
{
	Symbol s = Symbol_newSymbol("asdf");

	TEST_ASSERT_FALSE_MESSAGE(Symbol_equals(s, NULL),
		"C-SYM-EQ-04: Symbol is equal to null");
	TEST_ASSERT_FALSE_MESSAGE(Symbol_equals(NULL, s),
		"C-SYM-EQ-04: null is equal to Symbol");
		
	Symbol_destroy(&s);
}

/*  C-SYM-STR-01  */
TEST(Symbol, test_ToString)
{

	char sec[] = "fdsa";

	Symbol s = Symbol_newSymbol(sec);

	TEST_ASSERT_FALSE_MESSAGE(sec == Symbol_toString(s),
		"C-SYM-STR-01: String pointers are equal");
	TEST_ASSERT_EQUAL_STRING_MESSAGE(sec, Symbol_toString(s),
		"C-SYM-STR-01: Strings are not equal");

	Symbol_destroy(&s);
}

/*  C-SYM-STR-02  */
TEST(Symbol, test_ToStringFromNull)
{

	TEST_ASSERT_NULL_MESSAGE(Symbol_toString(NULL),
		"C-SYM-STR-02: String is not null");
}
