#include "../include/Symbol.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
// Generación de datos aleatoria
#include "quickcheck4c.h"

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

/*  C-SYM-NEW-01  */
void test_NewSymbolWithNullSequence(void) {

	// Devuelve NULL como símbolo si intentamos crearlo con secuencia NULL
	CU_ASSERT_PTR_NULL(Symbol_newSymbol(NULL));

}

/*  C-SYM-NEW-02  */
void test_NewSymbolWithVoidSequence(void) {

	Symbol s = Symbol_newSymbol("");

	CU_ASSERT_PTR_NOT_NULL(s);
	CU_ASSERT_STRING_EQUAL(Symbol_getSymbol(s), "");
	CU_ASSERT_EQUAL(strlen(Symbol_getSymbol(s)), 0);

	Symbol_destroy(&s);

}

/*  C-SYM-NEW-03  */
QCC_TestStatus test_AnyStringSymbol(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

    char *sec = QCC_getValue(vals, 0, char *);

	Symbol s = Symbol_newSymbol(sec);

	if (strncmp(Symbol_getSymbol(s), sec, strlen(sec)) != 0) {
		printf("\tErrored with string <%s> and size %d\n", sec, strlen(sec));
		printf("\tstrcmp returns %d\n", strncmp(Symbol_getSymbol(s), sec, strlen(sec)));

		Symbol_destroy(&s);

		return QCC_FAIL;
	}

	Symbol_destroy(&s);
	return QCC_OK;


}

/*  C-SYM-GSYM-01  */
void test_GetSymbolFromNull(void) {

	CU_ASSERT_PTR_NULL(Symbol_getSymbol(NULL));
}

/*  C-SYM-HASH-01  */
QCC_TestStatus test_HashCodeWithEqualObjects(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

    char *sec = QCC_getValue(vals, 0, char *);

	Symbol s1 = Symbol_newSymbol(sec);
	Symbol s2 = Symbol_newSymbol(sec);

	if (Symbol_hashCode(s1) != Symbol_hashCode(s2)) {
		printf("\tErrored with s1 <%s> and s2 <%s>. Hashcodes are %d and %d\n",
				 Symbol_getSymbol(s1), Symbol_getSymbol(s2), Symbol_hashCode(s1), Symbol_hashCode(s2));
	}

	if (Symbol_hashCode(s1) == Symbol_hashCode(s2)) {

		Symbol_destroy(&s1);
		Symbol_destroy(&s2);
		return QCC_OK;
	}
	else {

		Symbol_destroy(&s1);
		Symbol_destroy(&s2);
		return QCC_FAIL;
	}
}

/*  C-SYM-HASH-02  */
void test_HashCodeFromNull(void) {

	CU_ASSERT_EQUAL(Symbol_hashCode(NULL), -1);
}

/*  C-SYM-EQ-01  */
QCC_TestStatus test_EqualByReferenceObjects(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

	char *sec = QCC_getValue(vals, 0, char *);

	Symbol s1 = Symbol_newSymbol(sec);
	Symbol s2 = s1; 

	if (!Symbol_equals(s1, s2)) {
		printf("\tErrored with s1 being %p and s2 being %p\n", s1, s2);
	}

	if (Symbol_equals(s1, s2)) {

		Symbol_destroy(&s1);
		return QCC_OK;
	}
	else {

		Symbol_destroy(&s1);
		return QCC_FAIL;
	}
}

/*  C-SYM-EQ-02  */
QCC_TestStatus test_EqualByValueObjects(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

	char *sec = QCC_getValue(vals, 0, char *);

	Symbol s1 = Symbol_newSymbol(sec);
	Symbol s2 = Symbol_newSymbol(sec); 

	if (!Symbol_equals(s1, s2)) {
		printf("\tErrored with s1 <%s> and s2 <%s>\n", Symbol_getSymbol(s1), Symbol_getSymbol(s2));
	}

	if (Symbol_equals(s1, s2)) {

		Symbol_destroy(&s1);
		Symbol_destroy(&s2);
		return QCC_OK;
	}
	else {

		Symbol_destroy(&s1);
		Symbol_destroy(&s2);
		return QCC_FAIL;
	}
}

/*  C-SYM-EQ-03  */
QCC_TestStatus test_InequalObjects(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

	char *sec1 = QCC_getValue(vals, 0, char *);
	char *sec2 = QCC_getValue(vals, 1, char *);

	if (strcmp(sec1, sec2) == 0) {
		// Modificamos manualmente una cadena si coincide que son la misma
		sec1[0] +=1;
	}

	Symbol s1 = Symbol_newSymbol(sec1);
	Symbol s2 = Symbol_newSymbol(sec2); 

	if (Symbol_equals(s1, s2)) {
		printf("\tErrored with sec1 <%s> and sec2 <%s>\n", Symbol_getSymbol(s1), Symbol_getSymbol(s2));
	}

	if (Symbol_equals(s1, s2)) {

		Symbol_destroy(&s1);
		Symbol_destroy(&s2);
		return QCC_FAIL;
	}
	else {

		Symbol_destroy(&s1);
		Symbol_destroy(&s2);
		return QCC_OK;
	}
}

/*  C-SYM-EQ-04  */
void test_EqualToNullObject(void) {

	Symbol s = Symbol_newSymbol("asdf");

	CU_ASSERT_FALSE(Symbol_equals(s, NULL));
	CU_ASSERT_FALSE(Symbol_equals(NULL, s));

	Symbol_destroy(&s);
}

/*  C-SYM-STR-01  */
void test_ToString(void) {

	char sec[] = "fdsa";

	Symbol s = Symbol_newSymbol(sec);

	CU_ASSERT_PTR_NOT_EQUAL(sec, Symbol_getSymbol(s));
	CU_ASSERT_PTR_EQUAL(Symbol_getSymbol(s), Symbol_toString(s));

	Symbol_destroy(&s);
}

/*  C-SYM-STR-02  */
void test_ToStringFromNull(void) {

	CU_ASSERT_PTR_NULL(Symbol_toString(NULL));
}

/*
  Función principal para la ejecución de las pruebas.
  Devuelve CUE_SUCCESS si pasan correctamente,
  o un error CUnit si alguna falla.
 */
int main()
{

	printf("\n\nBEGIN SYMBOL MODULE'S UNIT TESTING\n");

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

	/* añadir las pruebas de la suite Symbol */
	/* ATENCIÓN: EL ORDEN ES IMPORTANTE */

	if (NULL == CU_add_test(pSuite, "C-SYM-NEW-01" , test_NewSymbolWithNullSequence)
	||  NULL == CU_add_test(pSuite, "C-SYM-NEW-02", test_NewSymbolWithVoidSequence)
	||  NULL == CU_add_test(pSuite, "C-SYM-GSYM-01", test_GetSymbolFromNull)
	||  NULL == CU_add_test(pSuite, "C-SYM-HASH-02", test_HashCodeFromNull)
	||  NULL == CU_add_test(pSuite, "C-SYM-EQ-04", test_EqualToNullObject)
	||  NULL == CU_add_test(pSuite, "C-SYM-STR-01", test_ToString)
	||  NULL == CU_add_test(pSuite, "C-SYM-STR-02", test_ToStringFromNull))
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

	printf("C-SYM-NEW-03:\t");
	QCC_testForAll(1000, 1, test_AnyStringSymbol, 1, QCC_genString);
	printf("C-SYM-HASH-01:\t");
	QCC_testForAll(1000, 1, test_HashCodeWithEqualObjects, 1, QCC_genString);
	printf("C-SYM-EQ-01:\t");
	QCC_testForAll(1000, 1, test_EqualByReferenceObjects, 1, QCC_genString);
	printf("C-SYM-EQ-02:\t");
	QCC_testForAll(1000, 1, test_EqualByValueObjects, 1, QCC_genString);
	printf("C-SYM-EQ-03:\t");
	QCC_testForAll(1000, 1, test_InequalObjects, 2, QCC_genString, QCC_genString);

	printf("\n\nEND SYMBOL MODULE'S UNIT TESTING\n");

	return 0;
}
