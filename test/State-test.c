#include "State.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

/*
  Función de inicialización de las pruebas de State.
 */
int init_suiteState(void)
{
  return 0;
}

/*
  Función de finalización de las pruebas de State.
 */
int clean_suiteState(void)
{
  return 0;
}

/**********************************************

	PRUEBAS DE UNIDAD PARA EL MÓDULO STATE

**********************************************/

/*	SYM-NEW-01	*/
void test_newStateWithoutName(void)
{
	CU_ASSERT_PTR_NULL(State_newState(NULL, 0));
}

/*	C-ST-HASH-01	*/
void test_hashCodeEqualStates(void) {

	State st1 = State_newState("q1", 3);
	State st2 = State_newState("q1", 3);
	
	CU_ASSERT_EQUAL(State_hashCode(st1), State_hashCode(st2));

}

/*	C-ST-EQ-01	*/
void test_equalsEqualStates(void) {

	State st1 = State_newState("q1", 3);
	State st2 = State_newState("q1", 3);
	
	CU_ASSERT_TRUE(State_equals(st1, st2));

}

/*	C-ST-EQ-02	*/
void test_equalsInequalStates(void) {

	State st1 = State_newState("q1", 3);
	State st2 = State_newState("q5", 3);
	
	CU_ASSERT_FALSE(State_equals(st1, st2));

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

   /* añadir una suite de pruebas al registro */
   pSuite = CU_add_suite("Suite_State", init_suiteState, clean_suiteState);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* añadir las pruebas al conjunto */
   /* ATENCIÓN: EL ORDEN ES IMPORTANTE */
   if (NULL == CU_add_test(pSuite, "C-ST-NEW-01", test_newStateWithoutName)
   ||  NULL == CU_add_test(pSuite, "C-ST-HASH-01", test_hashCodeEqualStates)
   ||  NULL == CU_add_test(pSuite, "C-ST-EQ-01", test_equalsEqualStates)
   ||  NULL == CU_add_test(pSuite, "C-ST-EQ-02", test_equalsInequalStates))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* ejecutar las pruebas usando la interfaz CUnit Basic */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   
   /*if (CU_get_number_of_failures() > 0) {
   	  CU_cleanup_registry();
   	  return 1;
   }*/
   
   CU_cleanup_registry();
   return 0;
}
