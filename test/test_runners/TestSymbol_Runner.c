#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Symbol)
{
	RUN_TEST_CASE(Symbol, test_NewSymbolWithNullSequence);
	RUN_TEST_CASE(Symbol, test_NewSymbolWithVoidSequence);
	RUN_TEST_CASE(Symbol, test_GetSymbolFromNull);
	RUN_TEST_CASE(Symbol, test_HashCodeFromNull);
	RUN_TEST_CASE(Symbol, test_EqualToNullObject);
	RUN_TEST_CASE(Symbol, test_ToString);
	RUN_TEST_CASE(Symbol, test_ToStringFromNull);
}
