#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(State)
{
	RUN_TEST_CASE(State, test_NewStateWithNullSequence);
	RUN_TEST_CASE(State, test_NewStateWithVoidSequence);
	RUN_TEST_CASE(State, test_GetStateFromNull);
	RUN_TEST_CASE(State, test_HashCodeFromNull);
	RUN_TEST_CASE(State, test_EqualToNullObject);
	RUN_TEST_CASE(State, test_ToString);
	RUN_TEST_CASE(State, test_ToStringFromNull);
}
