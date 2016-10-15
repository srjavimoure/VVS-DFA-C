#include "Symbol.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

/*
  Función de inicialización de las pruebas para Symbol
 */
int init_suiteSymbol(void)
{
  return 0;
}

/*
  Función de finalización de las pruebas para Symbol
 */
int clean_suiteSymbol(void)
{
  return 0;
}

/**********************************************

	PRUEBAS DE UNIDAD PARA EL MÓDULO SYMBOL

**********************************************/

/*	SYM-NEW-01	*/
void test_newSymbolWithNullSequence(void) {

	CU_ASSERT_PTR_NULL(Symbol_newSymbol(NULL, 0));

}

/*	SYM-HASH-01	*/
void test_hashCodeWithEqualObjects(void) {

	Symbol s1 = Symbol_newSymbol("a", 2);
	Symbol s2 = Symbol_newSymbol("a", 2);

	CU_ASSERT_EQUAL(Symbol_hashCode(s1), Symbol_hashCode(s2));
}

/*	SYM-EQ-01	*/
void test_EqualObjects(void) {

	Symbol s1 = Symbol_newSymbol("asdf", 10);
	Symbol s2 = Symbol_newSymbol("asdf", 10); 

	CU_ASSERT_TRUE(Symbol_equals(s1, s2));
}

/*	SYM-EQ-02	*/
void test_InequalObjects(void) {

	Symbol s1 = Symbol_newSymbol("asdf", 10);
	Symbol s2 = Symbol_newSymbol("qwer", 10); 

	CU_ASSERT_FALSE(Symbol_equals(s1, s2));
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
   pSuite = CU_add_suite("Suite_Symbol", init_suiteSymbol, clean_suiteSymbol);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* añadir las pruebas al conjunto */
   /* ATENCIÓN: EL ORDEN ES IMPORTANTE */
   
   if (NULL == CU_add_test(pSuite, "SYB-NEW-01" , test_newSymbolWithNullSequence)
   ||  NULL == CU_add_test(pSuite, "SYB-HASH-01", test_hashCodeWithEqualObjects)
   ||  NULL == CU_add_test(pSuite, "SYB-EQ-01"  , test_EqualObjects)
   ||  NULL == CU_add_test(pSuite, "SYB-EQ-02"  , test_InequalObjects))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }
   

   /* ejecutar las pruebas usando la interfaz CUnit Basic */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_number_of_failures() != 0;
}
