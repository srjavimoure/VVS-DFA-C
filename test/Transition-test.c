#include "../include/Transition.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

/*
  Función de inicialización de las pruebas.
 */
int init_suiteTransition(void)
{
  return 0;
}

/*
  Función de finalización de las pruebas.
 */
int clean_suiteTransition(void)
{
  return 0;
}

/*
  Prueba de unidad.
 */
void test_Transition(void)
{
	CU_PASS("Transition passed.\n");
}

/*
  Función principal para la ejecución de las pruebas.
  Devuelve CUE_SUCCESS si pasan correctamente,
  o un error CUnit si alguna falla.
 */
int main()
{

	CU_pSuite pSuite = NULL;

	/* inicializar el registro de pruebas CUnit */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* añadir un conjunto de pruebas al registro */
	pSuite = CU_add_suite("Suite_Transition", init_suiteTransition, clean_suiteTransition);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* añadir las pruebas al conjunto */
	/* ATENCIÓN: EL ORDEN ES IMPORTANTE */
	if (NULL == CU_add_test(pSuite, "Prueba de Transition", test_Transition))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* ejecutar las pruebas usando la interfaz CUnit Basic */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
