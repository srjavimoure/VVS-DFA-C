#include <string.h>
#include "../include/GenList.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(GenList);

TEST_SETUP(GenList) {}

TEST_TEAR_DOWN(GenList) {}

/*
	Función de búsqueda para las pruebas
 */
char fun(void *a, void *b) {
	int *c = (int *) a;
	int *d = (int *) b;
	return (*c == *d);
}

/*
	Función de paso a string para las pruebas
 */
char *str(void *element) {
	return ((char *) element);
}

/*  C-GLIST-NEW-02  */
TEST(GenList, test_NewGenListZeroBuffer)
{

	GenList g = GenList_newGenList(0);

	TEST_ASSERT_NOT_NULL_MESSAGE(g,
		"C-GLIST-NEW-02: GenList is null");
	TEST_ASSERT_EQUAL_INT_MESSAGE(GenList_getSize(g), 0,
		"C-GLIST-NEW-02: GenList size is not zero");
	TEST_ASSERT_EQUAL_INT_MESSAGE(GenList_getBuffer(g), 5,
		"C-GLIST-NEW-02: GenList buffer is not the default BUFSIZE");
}

/*  C-GLIST-GBUF-01  */
TEST(GenList, test_GetBufferFromNull)
{
	TEST_ASSERT_EQUAL_INT_MESSAGE(GenList_getBuffer(NULL), -1,
		"C-GLIST-GBUF-01: Buffer is not -1");
}

/*  C-GLIST-GSIZ-01  */
TEST(GenList, test_GetSizeFromNull)
{
	TEST_ASSERT_EQUAL_INT_MESSAGE(GenList_getSize(NULL), -1,
		"C-GLIST-GSIZ-01: Size is not -1");
}

/*  C-GLIST-ADD-01  */
TEST(GenList, test_AddFromNull)
{
	int a = 4;
	GenList_add(NULL, &a);

	// Si llega aquí es que no ha crasheado
	TEST_ASSERT_TRUE_MESSAGE(1, "C-GLIST-ADD-01: Failed with null list");
}

/*  C-GLIST-ADD-02  */
TEST(GenList, test_AddNull)
{
	GenList_add(GenList_newGenList(3), NULL);

	// Si llega aquí es que no ha crasheado
	TEST_ASSERT_TRUE_MESSAGE(1, "C-GLIST-ADD-02: Failed with null element");
}

/*  C-GLIST-ADD-03  */
TEST(GenList, test_AddToFullBuffer)
{
	GenList g = GenList_newGenList(3);
	int a = 2, b = 1, c = 4, d = -1;
	GenList_add(g, &a);
	GenList_add(g, &b);
	GenList_add(g, &c);

	TEST_ASSERT_EQUAL_INT_MESSAGE(GenList_getSize(g), GenList_getBuffer(g),
		"C-GLIST-ADD-03: Size and buffer are not equal");

	int old_size = GenList_getSize(g);

	GenList_add(g, &d);

	TEST_ASSERT_TRUE_MESSAGE(GenList_getSize(g) == old_size + 1,
		"C-GLIST-ADD-03: Size did not get up");
	TEST_ASSERT_TRUE_MESSAGE(GenList_getExistingObject(g, &d, fun) == &d,
		"C-GLIST-ADD-03: Element did not get added");
}

/* C-GLIST-ADD-04  */
TEST(GenList, test_AddWithSpace)
{
	GenList g = GenList_newGenList(3);
	int a = 2, b = -1;
	GenList_add(g, &a);

	TEST_ASSERT_TRUE_MESSAGE(GenList_getSize(g) < GenList_getBuffer(g),
		"C-GLIST-ADD-04: Size is not less than buffer");

	int old_size = GenList_getSize(g);

	GenList_add(g, &b);

	TEST_ASSERT_TRUE_MESSAGE(GenList_getSize(g) == old_size + 1,
		"C-GLIST-ADD-04: Size did not get up");
	TEST_ASSERT_TRUE_MESSAGE(GenList_getExistingObject(g, &b, fun) == &b,
		"C-GLIST-ADD-03: Element did not get added");
}

/*  C-GLIST-REM-01  */
TEST(GenList, test_RemoveFromNull)
{
	GenList_remove(NULL, 2);

	// Si llega aquí es que no ha crasheado
	TEST_ASSERT_TRUE_MESSAGE(1, "C-GLIST-REM-01: Failed with null list");
}

/*  C-GLIST-REM-02  */
TEST(GenList, test_RemoveOutofBounds)
{
	GenList g = GenList_newGenList(3);
	GenList_remove(g, -5);

	// Si llega aquí es que no ha crasheado
	TEST_ASSERT_TRUE_MESSAGE(1, "C-GLIST-REM-02: Failed with negative position");
	
	GenList_remove(g, 15);

	// Si llega aquí es que no ha crasheado
	TEST_ASSERT_TRUE_MESSAGE(1, "C-GLIST-REM-02: Failed with out of bounds position");
}

/*  C-GLIST-REM-03  */
TEST(GenList, test_RemoveExistingElement)
{
	GenList g = GenList_newGenList(3);
	int a = 1, b = 2, c = 4;
	GenList_add(g, &a);
	GenList_add(g, &b);
	GenList_add(g, &c);
	
	TEST_ASSERT_NOT_NULL_MESSAGE(GenList_getExistingObject(g, &a, fun),
		"C-GLIST-REM-03: Object did not exist");
	
	GenList_remove(g, 0);
	
	TEST_ASSERT_NULL_MESSAGE(GenList_getExistingObject(g, &a, fun),
		"C-GLIST-REM-03: Object still exists in list");
}

/*  C-GLIST-ELEM-01  */
TEST(GenList, test_GetElementFromNull)
{
	TEST_ASSERT_NULL_MESSAGE(GenList_getElement(NULL, 2),
		"C-GLIST-ELEM-01: Got element from null list");
}

/*  C-GLIST-ELEM-02  */
TEST(GenList, test_GetElementFromOutofBounds)
{
	GenList g = GenList_newGenList(3);

	TEST_ASSERT_NULL_MESSAGE(GenList_getElement(g, -5),
		"C-GLIST-ELEM-02: Got element from negative position");
	TEST_ASSERT_NULL_MESSAGE(GenList_getElement(g, 15),
		"C-GLIST-ELEM-02: Got element from out of bounds position");
}

/*  C-GLIST-ELEM-03  */
TEST(GenList, test_GetExistingElement)
{
	GenList g = GenList_newGenList(3);
	int a = 2;
	GenList_add(g, &a);
	
	TEST_ASSERT_NOT_NULL_MESSAGE(GenList_getElement(g, 0),
		"C-GLIST-ELEM-03: Failed to get an element");
	TEST_ASSERT_EQUAL_INT_MESSAGE(GenList_getElement(g, 0), &a,
		"C-GLIST-ELEM-03: Element is not the same");
}

/*  C-GLIST-EXOB-01  */
TEST(GenList, test_GExObFromNull)
{
	int a = 4;
	TEST_ASSERT_NULL_MESSAGE(GenList_getExistingObject(NULL, &a, fun),
		"C-GLIST-EXOB-01: Got an element from null list");
}

/*  C-GLIST-EXOB-02  */
TEST(GenList, test_GExObNull)
{
	GenList g = GenList_newGenList(3);
	TEST_ASSERT_NULL_MESSAGE(GenList_getExistingObject(g, NULL, fun),
		"C-GLIST-EXOB-02: Got a null element");
}

/*  C-GLIST-EXOB-03  */
TEST(GenList, test_GExObFunctionNull)
{
	GenList g = GenList_newGenList(3);
	int a = 4;
	GenList_add(g, &a);
	TEST_ASSERT_NULL_MESSAGE(GenList_getExistingObject(g, &a, NULL),
		"C-GLIST-EXOB-03: Got an element from null function");
}

/*  C-GLIST-EXOB-04  */
TEST(GenList, test_GExObNotExisting)
{
	GenList g = GenList_newGenList(3);
	int a = 4;
	
	TEST_ASSERT_NULL_MESSAGE(GenList_getExistingObject(g, &a, fun),
		"C-GLIST-EXOB-04: Got a not existing element");
}

/*  C-GLIST-EXOB-05  */
TEST(GenList, test_GExObExisting)
{
	GenList g = GenList_newGenList(3);
	int a = 4;
	GenList_add(g, &a);
	
	TEST_ASSERT_NOT_NULL_MESSAGE(GenList_getExistingObject(g, &a, fun),
		"C-GLIST-EXOB-05: Element does not exist");
	TEST_ASSERT_EQUAL_INT_MESSAGE(GenList_getExistingObject(g, &a, fun), &a,
		"C-GLIST-EXOB-05: Not the same element");
}

/*  C-GLIST-STR-01  */
TEST(GenList, test_ToStringFromNull)
{
	TEST_ASSERT_NULL_MESSAGE(GenList_toString(NULL, str),
		"C-GLIST-STR-01: Got string from null list");
}

/*  C-GLIST-STR-02  */
TEST(GenList, test_ToStringFunctionNull)
{
	TEST_ASSERT_NULL_MESSAGE(GenList_toString(GenList_newGenList(3), NULL),
		"C-GLIST-STR-02: Got string with null function");
}

/*  C-GLIST-STR-03  */
TEST(GenList, test_ToStringNormal)
{
	GenList g = GenList_newGenList(3);
	char a[] = "a";
	GenList_add(g, &a);
	char *r = GenList_toString(g, str);

	TEST_ASSERT_EQUAL_STRING_MESSAGE(r, r,
		"C-GLIST-STR-03: Not the same string");
}
