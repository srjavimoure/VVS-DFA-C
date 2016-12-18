#include "../include/GenList.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
// Generaci�n de datos aleatoria
#include "quickcheck4c.h"

/*
  Funci�n de inicializaci�n de las pruebas.
 */
int init_suiteGenList(void)
{
	return 0;
}

/*
  Funci�n de finalizaci�n de las pruebas.
 */
int clean_suiteGenList(void)
{
	return 0;
}

/*
	Generador de numeros negativos
 */
QCC_GenValue *QCC_genNegativeInt(void) {
	return QCC_genIntR(-50, -1);
}

/*
	Generador de numeros positivos
 */
QCC_GenValue *QCC_genPositiveInt(void) {
	return QCC_genIntR(1, 50);
}

/*
	Funci�n de b�squeda para las pruebas
 */
char fun(void *a, void *b) {
	int *c = (int *) a;
	int *d = (int *) b;
	return (*c == *d);
}

/*
	Funci�n de paso a string para las pruebas
 */
char *str(void *element) {
	return ((char *) element);
}

/*  C-GLIST-NEW-01  */
QCC_TestStatus test_NewGenListNegBuffer(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

    int buf = *QCC_getValue(vals, 0, int *);

	GenList g = GenList_newGenList(buf);

	if (GenList_getBuffer(g) == 5 && GenList_getSize(g) == 0) {

		return QCC_OK;
	}
	else {

		printf("Failed with buffer %d (real buffer %d)\n",
				buf, GenList_getBuffer(g));

		return QCC_FAIL;
	}

}

/*  C-GLIST-NEW-02  */
void test_NewGenListZeroBuffer(void) {

	GenList g = GenList_newGenList(0);

	CU_ASSERT_PTR_NOT_NULL(g);
	CU_ASSERT_EQUAL(GenList_getSize(g), 0);
	CU_ASSERT_EQUAL(GenList_getBuffer(g), 5);

}

/*  C-GLIST-NEW-03  */
QCC_TestStatus test_NewGenListPosBuffer(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

    int buf = *QCC_getValue(vals, 0, int *);

	GenList g = GenList_newGenList(buf);

	if (GenList_getBuffer(g) == buf && GenList_getSize(g) == 0) {

		return QCC_OK;
	}
	else {

		printf("Failed with buffer %d (real buffer %d)\n",
				buf, GenList_getBuffer(g));

		return QCC_FAIL;
	}

}

/*  C-GLIST-GBUF-01  */
void test_GetBufferFromNull(void) {

	CU_ASSERT_EQUAL(GenList_getBuffer(NULL), -1);
}

/*  C-GLIST-GSIZ-01  */
void test_GetSizeFromNull(void) {

	CU_ASSERT_EQUAL(GenList_getSize(NULL), -1);
}

/*  C-GLIST-ADD-01  */
void test_AddFromNull(void) {

	int a = 4;
	GenList_add(NULL, &a);

	// Si llega aqu� es que no ha crasheado
	CU_PASS("Failed with null list");

}

/*  C-GLIST-ADD-02  */
void test_AddNull(void) {

	GenList_add(GenList_newGenList(3), NULL);

	// Si llega aqu� es que no ha crasheado
	CU_PASS("Failed with null element");

}

/*  C-GLIST-ADD-03  */
void test_AddToFullBuffer(void) {

	GenList g = GenList_newGenList(3);
	int a = 2, b = 1, c = 4, d = -1;
	GenList_add(g, &a);
	GenList_add(g, &b);
	GenList_add(g, &c);

	CU_ASSERT_EQUAL(GenList_getSize(g), GenList_getBuffer(g));

	int old_size = GenList_getSize(g);

	GenList_add(g, &d);

	CU_ASSERT_TRUE(GenList_getSize(g) == old_size + 1);
	CU_ASSERT_TRUE(GenList_getExistingObject(g, &d, fun) == &d);

}

/* C-GLIST-ADD-04  */
void test_AddWithSpace(void) {

	GenList g = GenList_newGenList(3);
	int a = 2, b = -1;
	GenList_add(g, &a);

	CU_ASSERT_TRUE(GenList_getSize(g) < GenList_getBuffer(g));

	int old_size = GenList_getSize(g);

	GenList_add(g, &b);

	CU_ASSERT_TRUE(GenList_getSize(g) == old_size + 1);
	CU_ASSERT_TRUE(GenList_getExistingObject(g, &b, fun) == &b);

}

/*  C-GLIST-REM-01  */
void test_RemoveFromNull(void) {

	GenList_remove(NULL, 2);

	// Si llega aqu� es que no ha crasheado
	CU_PASS("Failed with null list");
}

/*  C-GLIST-REM-02  */
void test_RemoveOutofBounds(void) {

	GenList g = GenList_newGenList(3);
	GenList_remove(g, -5);

	// Si llega aqu� es que no ha crasheado
	CU_PASS("Failed with negative position");
	
	GenList_remove(g, 15);

	// Si llega aqu� es que no ha crasheado
	CU_PASS("Failed with out of bounds position");
}

/*  C-GLIST-REM-03  */
void test_RemoveExistingElement(void) {

	GenList g = GenList_newGenList(3);
	int a = 1, b = 2, c = 4;
	GenList_add(g, &a);
	GenList_add(g, &b);
	GenList_add(g, &c);
	
	CU_ASSERT_PTR_NOT_NULL(GenList_getExistingObject(g, &a, fun));
	
	GenList_remove(g, 0);
	
	CU_ASSERT_PTR_NULL(GenList_getExistingObject(g, &a, fun));

}

/*  C-GLIST-ELEM-01  */
void test_GetElementFromNull(void) {

	CU_ASSERT_PTR_NULL(GenList_getElement(NULL, 2));
}

/*  C-GLIST-ELEM-02  */
void test_GetElementFromOutofBounds(void) {

	GenList g = GenList_newGenList(3);

	CU_ASSERT_PTR_NULL(GenList_getElement(g, -5));
	CU_ASSERT_PTR_NULL(GenList_getElement(g, 15));
}

/*  C-GLIST-ELEM-03  */
void test_GetExistingElement(void) {

	GenList g = GenList_newGenList(3);
	int a = 2;
	GenList_add(g, &a);
	
	CU_ASSERT_PTR_NOT_NULL(GenList_getElement(g, 0));
	CU_ASSERT_PTR_EQUAL(GenList_getElement(g, 0), &a);
}

/*  C-GLIST-EXOB-01  */
void test_GExObFromNull(void) {

	int a = 4;
	CU_ASSERT_PTR_NULL(GenList_getExistingObject(NULL, &a, fun));

}

/*  C-GLIST-EXOB-02  */
void test_GExObNull(void) {

	GenList g = GenList_newGenList(3);
	CU_ASSERT_PTR_NULL(GenList_getExistingObject(g, NULL, fun));

}

/*  C-GLIST-EXOB-03  */
void test_GExObFunctionNull(void) {

	GenList g = GenList_newGenList(3);
	int a = 4;
	GenList_add(g, &a);
	CU_ASSERT_PTR_NULL(GenList_getExistingObject(g, &a, NULL));

}

/*  C-GLIST-EXOB-04  */
void test_GExObNotExisting(void) {

	GenList g = GenList_newGenList(3);
	int a = 4;
	
	CU_ASSERT_PTR_NULL(GenList_getExistingObject(g, &a, fun));
}

/*  C-GLIST-EXOB-05  */
void test_GExObExisting(void) {

	GenList g = GenList_newGenList(3);
	int a = 4;
	GenList_add(g, &a);
	
	CU_ASSERT_PTR_NOT_NULL(GenList_getExistingObject(g, &a, fun));
	CU_ASSERT_PTR_EQUAL(GenList_getExistingObject(g, &a, fun), &a);
}

/*  C-GLIST-STR-01  */
void test_ToStringFromNull(void) {

	CU_ASSERT_PTR_NULL(GenList_toString(NULL, str));
}

/*  C-GLIST-STR-02  */
void test_ToStringFunctionNull(void) {

	GenList g = GenList_newGenList(3);

	CU_ASSERT_PTR_NULL(GenList_toString(g, NULL));
}

/*  C-GLIST-STR-03  */
void test_ToStringNormal(void) {

	GenList g = GenList_newGenList(3);
	char a[] = "a";
	GenList_add(g, &a);
	char *r = GenList_toString(g, str);

	CU_ASSERT_STRING_EQUAL(r, r);
}

/*
  Funci�n principal para la ejecuci�n de las pruebas.
  Devuelve CUE_SUCCESS si pasan correctamente,
  o un error CUnit si alguna falla.
 */
int main()
{

	printf("\n\nBEGIN GENLIST MODULE'S UNIT TESTING\n");

	CU_pSuite pSuite = NULL;

	/* inicializar el registro de pruebas CUnit */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* a�adir una suite de pruebas al registro */
	pSuite = CU_add_suite("Suite_GenList", init_suiteGenList, clean_suiteGenList);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* a�adir las pruebas de la suite GenList */
	/* ATENCI�N: EL ORDEN ES IMPORTANTE */
	if (NULL == CU_add_test(pSuite, "C-GLIST-NEW-02", test_NewGenListZeroBuffer)
	||  NULL == CU_add_test(pSuite, "C-GLIST-GBUF-01", test_GetBufferFromNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-GSIZ-01", test_GetSizeFromNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-ADD-01", test_AddFromNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-ADD-02", test_AddNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-ADD-03", test_AddToFullBuffer)
	||  NULL == CU_add_test(pSuite, "C-GLIST-ADD-04", test_AddWithSpace)
	||  NULL == CU_add_test(pSuite, "C-GLIST-REM-01", test_RemoveFromNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-REM-02", test_RemoveOutofBounds)
	||  NULL == CU_add_test(pSuite, "C-GLIST-REM-03", test_RemoveExistingElement)
	||  NULL == CU_add_test(pSuite, "C-GLIST-ELEM-01", test_GetElementFromNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-ELEM-02", test_GetElementFromOutofBounds)
	||  NULL == CU_add_test(pSuite, "C-GLIST-ELEM-03", test_GetExistingElement)
	||  NULL == CU_add_test(pSuite, "C-GLIST-EXOB-01", test_GExObFromNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-EXOB-02", test_GExObNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-EXOB-03", test_GExObFunctionNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-EXOB-04", test_GExObNotExisting)
	||  NULL == CU_add_test(pSuite, "C-GLIST-EXOB-05", test_GExObExisting)
	||  NULL == CU_add_test(pSuite, "C-GLIST-STR-01", test_ToStringFromNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-STR-02", test_ToStringFunctionNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-STR-02", test_ToStringNormal))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* ejecutar las pruebas usando la interfaz CUnit Basic */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();

	QCC_init(0);

	printf("\n\t\t*************************************\n\n"
		   "\t\t\tQuickCheck4C testing:\n\n"
		   "\t\t*************************************\n\n");

	printf("C-GLIST-NEW-01:\t");
	QCC_testForAll(1000, 1, test_NewGenListNegBuffer, 1, QCC_genNegativeInt);
	printf("C-GLIST-NEW-03:\t");
	QCC_testForAll(1000, 1, test_NewGenListPosBuffer, 1, QCC_genPositiveInt);

	printf("\n\nEND GENLIST MODULE'S UNIT TESTING\n");

	return CU_get_error();
}
