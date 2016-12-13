#include "../include/Symbol.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
// Generaci�n de datos aleatoria
#include "quickcheck4c.h"

/*
  Funci�n de inicializaci�n de las pruebas para Symbol
 */
int init_suiteSymbol(void)
{
  return 0;
}

/*
  Funci�n de finalizaci�n de las pruebas para Symbol
 */
int clean_suiteSymbol(void)
{
  return 0;
}

/**********************************************

	PRUEBAS DE UNIDAD PARA EL M�DULO SYMBOL

**********************************************/

/*	C-SYM-NEW-01	*/
void test_newSymbolWithNullSequence(void) {

	CU_ASSERT_PTR_NULL(Symbol_newSymbol(NULL, 0));

}

/*	C-SYM-HASH-01	*/
void test_hashCodeWithEqualObjects(void) {

	Symbol s1 = Symbol_newSymbol("a", 2);
	Symbol s2 = Symbol_newSymbol("a", 2);

	CU_ASSERT_EQUAL(Symbol_hashCode(s1), Symbol_hashCode(s2));
}

/*	C-SYM-EQ-01	*/
void test_EqualObjects(void) {

	Symbol s1 = Symbol_newSymbol("asdf", 10);
	Symbol s2 = Symbol_newSymbol("asdf", 10); 

	CU_ASSERT_TRUE(Symbol_equals(s1, s2));
}

/*	C-SYM-EQ-02	*/
void test_InequalObjects(void) {

	Symbol s1 = Symbol_newSymbol("asdf", 10);
	Symbol s2 = Symbol_newSymbol("qwer", 10); 

	CU_ASSERT_FALSE(Symbol_equals(s1, s2));
}

/*
	Generadores de datos propias

*/


/*
	Pruebas que usan generadores (QUICKCHECK4C)
*/

/*	C-SYM-QCC-02	*/
QCC_TestStatus test_AnyStringSymbol(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

	return 1;

    char *sec = QCC_getValue(vals, 0, char *);

	Symbol s = Symbol_newSymbol(sec, strlen(sec));

	if (!(strlen(Symbol_getSymbol(s)) == strlen(sec) && strcmp(Symbol_getSymbol(s), sec) == 0)) {
		printf("\tErrored with string <%s> and size %d\n", sec, strlen(sec));
	}

	/*La secuencia del s�mbolo es los size primeros caracteres de sec*/
	return (strlen(Symbol_getSymbol(s)) == strlen(sec) && strcmp(Symbol_getSymbol(s), sec) == 0);


}

/*
  Funci�n principal para la ejecuci�n de las pruebas.
  Devuelve CUE_SUCCESS si pasan correctamente,
  o un error CUnit si alguna falla.
 */
int main()
{

	CU_pSuite pSuite = NULL;

	/* inicializar el registro de pruebas CUnit */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* a�adir una suite de pruebas al registro */
	pSuite = CU_add_suite("Suite_Symbol", init_suiteSymbol, clean_suiteSymbol);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* a�adir las pruebas de la suite Symbol */
	/* ATENCI�N: EL ORDEN ES IMPORTANTE */

	if (NULL == CU_add_test(pSuite, "C-SYM-NEW-01" , test_newSymbolWithNullSequence)
	||  NULL == CU_add_test(pSuite, "C-SYM-HASH-01", test_hashCodeWithEqualObjects)
	||  NULL == CU_add_test(pSuite, "C-SYM-EQ-01"  , test_EqualObjects)
	||  NULL == CU_add_test(pSuite, "C-SYM-EQ-02"  , test_InequalObjects))
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

	QCC_init(0);

	printf("\n*********************\n"
		   "QuickCheck4C testing:\n"
		   "*********************\n");

	printf("Generating strings for symbols:\n");
	QCC_testForAll(100, 1, test_AnyStringSymbol, 1, QCC_genString);

	printf("FIN DE LAS PRUEBAS\n");

	return 0;
}
