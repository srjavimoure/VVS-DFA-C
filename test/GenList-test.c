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


/*  C-GLIST-NEW-01  */
QCC_TestStatus test_NewGenListNegBuffer(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

    int buf = QCC_getValue(vals, 0, int);

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
	if (NULL == CU_add_test(pSuite, "C-GLIST-NEW-02", test_NewGenListZeroBuffer))
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

	printf("\n\nEND GENLIST MODULE'S UNIT TESTING\n");

	return CU_get_error();
}
