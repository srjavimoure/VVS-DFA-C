#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(GenList)
{
	RUN_TEST_CASE(GenList, test_NewGenListZeroBuffer);
	RUN_TEST_CASE(GenList, test_GetBufferFromNull);
	RUN_TEST_CASE(GenList, test_GetSizeFromNull);
	RUN_TEST_CASE(GenList, test_AddFromNull);
	RUN_TEST_CASE(GenList, test_AddNull);
	RUN_TEST_CASE(GenList, test_AddToFullBuffer);
	RUN_TEST_CASE(GenList, test_AddWithSpace);
	RUN_TEST_CASE(GenList, test_RemoveFromNull);
	RUN_TEST_CASE(GenList, test_RemoveOutofBounds);
	RUN_TEST_CASE(GenList, test_RemoveExistingElement);
	RUN_TEST_CASE(GenList, test_GetElementFromNull);
	RUN_TEST_CASE(GenList, test_GetElementFromOutofBounds);
	RUN_TEST_CASE(GenList, test_GetExistingElement);
	RUN_TEST_CASE(GenList, test_GExObFromNull);
	RUN_TEST_CASE(GenList, test_GExObNull);
	RUN_TEST_CASE(GenList, test_GExObFunctionNull);
	RUN_TEST_CASE(GenList, test_GExObNotExisting);
	RUN_TEST_CASE(GenList, test_GExObExisting);
	RUN_TEST_CASE(GenList, test_ToStringFromNull);
	RUN_TEST_CASE(GenList, test_ToStringFunctionNull);
	RUN_TEST_CASE(GenList, test_ToStringNormal);
}
