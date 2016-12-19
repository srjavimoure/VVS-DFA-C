#include <string.h>
#include "../include/State.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(State);

TEST_SETUP(State) {}

TEST_TEAR_DOWN(State) {}

/**********************************************

	PRUEBAS CON UNITY PARA EL MÓDULO STATE

**********************************************/

/*  C-ST-NEW-01  */
TEST(State, test_NewStateWithNullSequence)
{
	TEST_ASSERT_NULL_MESSAGE(State_newState(NULL), "C-ST-NEW-01: State not null");
}

/*  C-ST-NEW-02  */
TEST(State, test_NewStateWithVoidSequence)
{
	State s = State_newState("");

	TEST_ASSERT_NOT_NULL_MESSAGE(s, "C-ST-NEW-02: State is null with \"\" string");
	TEST_ASSERT_EQUAL_STRING_MESSAGE(State_getState(s), "",
		"C-ST-NEW-02: Strings are not equal");
	TEST_ASSERT_EQUAL_INT_MESSAGE(strlen(State_getState(s)), 0,
		"C-ST-NEW-02: Strings have different length");

	State_destroy(&s);

}

/*  C-ST-GST-01  */
TEST(State, test_GetStateFromNull)
{
	TEST_ASSERT_NULL_MESSAGE(State_getState(NULL),
		"C-ST-GST-01: State not null");
}

/*  C-ST-HASH-02  */
TEST(State, test_HashCodeFromNull)
{
	TEST_ASSERT_EQUAL_INT_MESSAGE(State_hashCode(NULL), -1,
		"C-ST-HASH-02: Hashcode for null is not -1");
}

/*  C-ST-EQ-04  */
TEST(State, test_EqualToNullObject)
{
	State s = State_newState("asdf");

	TEST_ASSERT_FALSE_MESSAGE(State_equals(s, NULL),
		"C-ST-EQ-04: State is equal to null");
	TEST_ASSERT_FALSE_MESSAGE(State_equals(NULL, s),
		"C-ST-EQ-04: null is equal to State");

	State_destroy(&s);
}



/*  C-ST-STR-01  */
TEST(State, test_ToString)
{
	char sec[] = "fdsa";

	State s = State_newState(sec);

	TEST_ASSERT_FALSE_MESSAGE(sec == State_toString(s),
		"C-SYM-STR-01: String pointers are equal");
	TEST_ASSERT_EQUAL_STRING_MESSAGE(sec, State_toString(s),
		"C-ST-STR-01: Strings are not equal");

	State_destroy(&s);
}

/*  C-ST-STR-02  */
TEST(State, test_ToStringFromNull)
{
	TEST_ASSERT_NULL_MESSAGE(State_toString(NULL),
		"C-ST-STR-02: String is not null");
}
