#include "../include/GenList.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
// Generación de datos aleatoria
#include "quickcheck4c.h"

/*
  Función de inicialización de las pruebas.
 */
int init_suiteGenList(void)
{
	return 0;
}

/*
  Función de finalización de las pruebas.
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

	// Si llega aquí es que no ha crasheado
	CU_PASS("No crashea con this == null");

}

/*  C-GLIST-ADD-02  */
void test_AddNull(void) {

	GenList_add(GenList_newGenList(3), NULL);

	// Si llega aquí es que no ha crasheado
	CU_PASS("No crashea con element == null");

}

/*  C-GLIST-ADD-03  */
char fun(void *a, void *b) {
	int *c = (int *) a;
	int *d = (int *) b;
	return (*c == *d);
}

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
void test_AddWithSpace(void){

	GenList g = GenList_newGenList(3);
	int a = 2, b = -1;
	GenList_add(g, &a);

	CU_ASSERT_TRUE(GenList_getSize(g) < GenList_getBuffer(g));

	int old_size = GenList_getSize(g);

	GenList_add(g, &b);

	CU_ASSERT_TRUE(GenList_getSize(g) == old_size + 1);
	CU_ASSERT_TRUE(GenList_getExistingObject(g, &b, fun) == &b);

}

/*
  Función principal para la ejecución de las pruebas.
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

	/* añadir una suite de pruebas al registro */
	pSuite = CU_add_suite("Suite_GenList", init_suiteGenList, clean_suiteGenList);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* añadir las pruebas de la suite GenList */
	/* ATENCIÓN: EL ORDEN ES IMPORTANTE */
	if (NULL == CU_add_test(pSuite, "C-GLIST-NEW-02", test_NewGenListZeroBuffer)
	||  NULL == CU_add_test(pSuite, "C-GLIST-GBUF-01", test_GetBufferFromNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-GSIZ-01", test_GetSizeFromNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-ADD-01", test_AddFromNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-ADD-02", test_AddNull)
	||  NULL == CU_add_test(pSuite, "C-GLIST-ADD-03", test_AddToFullBuffer)
	||  NULL == CU_add_test(pSuite, "C-GLIST-ADD-04", test_AddWithSpace))
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
