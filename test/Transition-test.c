#include <string.h>
#include "unity.h"
#include "unity_fixture.h"
#include "../include/Transition.h"
#include "../mocks/MockState.h"
#include "../mocks/MockSymbol.h"
#include "../mocks/MockGenList.h"

TEST_GROUP(Transition);

TEST_SETUP(Transition) {}

TEST_TEAR_DOWN(Transition) {}

TEST(Transition, test_Transition)
{
	int a = 2, b = 1;
	void *p = (void *) &a;
	void *q = (void *) &b;

	Symbol_newSymbol_ExpectAndReturn("fdsa", q);
	State_newState_ExpectAndReturn("asdf", p);
	State_newState_ExpectAndReturn("qwer", p);

	Symbol_hashCode_ExpectAndReturn(q, 15);
	State_hashCode_ExpectAndReturn(p, 32);
	State_hashCode_ExpectAndReturn(p, 32);

	Transition t = Transition_newTransition(Symbol_newSymbol("fdsa"), State_newState("asdf"), State_newState("qwer"));

	TEST_ASSERT_EQUAL_INT_MESSAGE(Transition_hashCode(t), 45, "ASDF");
}

