#include "../include/State.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
// Generación de datos aleatoria
#include "quickcheck4c.h"

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

/*  C-ST-NEW-01  */
void test_NewStateWithNullSequence(void) {

	// Devuelve NULL como símbolo si intentamos crearlo con secuencia NULL
	CU_ASSERT_PTR_NULL(State_newState(NULL));

}

/*  C-ST-NEW-02  */
void test_NewStateWithVoidSequence(void) {

	// Devuelve un símbolo válido con tamaño 0 y secuencia ""

	State s = State_newState("");

	CU_ASSERT_PTR_NOT_NULL(s);
	CU_ASSERT_STRING_EQUAL(State_getState(s), "");
	CU_ASSERT_EQUAL(strlen(State_getState(s)), 0);

	State_destroy(&s);

}

/*  C-ST-NEW-03  */
QCC_TestStatus test_AnyStringState(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

    char *sec = QCC_getValue(vals, 0, char *);

	State s = State_newState(sec);

	if (strncmp(State_getState(s), sec, strlen(sec)) != 0) {
		printf("\tErrored with string <%s> and size %d\n", sec, strlen(sec));
		printf("\tstrcmp returns %d\n", strncmp(State_getState(s), sec, strlen(sec)));

		State_destroy(&s);

		return QCC_FAIL;
	}

	State_destroy(&s);

	return QCC_OK;


}

/*  C-ST-HASH-01  */
QCC_TestStatus test_HashCodeWithEqualObjects(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

    char *sec = QCC_getValue(vals, 0, char *);

	State s1 = State_newState(sec);
	State s2 = State_newState(sec);

	if (State_hashCode(s1) != State_hashCode(s2)) {
		printf("\tErrored with s1 <%s> and s2 <%s>. Hashcodes are %d and %d\n",
				 State_getState(s1), State_getState(s2), State_hashCode(s1), State_hashCode(s2));
	}

	if (State_hashCode(s1) == State_hashCode(s2)) {

		State_destroy(&s1);
		State_destroy(&s2);
		return QCC_OK;
	}
	else {

		State_destroy(&s1);
		State_destroy(&s2);
		return QCC_FAIL;
	}
}

/*  C-ST-EQ-01  */
QCC_TestStatus test_EqualByReferenceObjects(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

	char *sec = QCC_getValue(vals, 0, char *);

	State s1 = State_newState(sec);
	State s2 = s1; 

	if (!State_equals(s1, s2)) {
		printf("\tErrored with s1 being %p and s2 being %p\n", s1, s2);
	}

	if (State_equals(s1, s2)) {

		State_destroy(&s1);
		return QCC_OK;
	}
	else {

		State_destroy(&s1);
		return QCC_FAIL;
	}
}

/*  C-ST-EQ-02  */
QCC_TestStatus test_EqualByValueObjects(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

	char *sec = QCC_getValue(vals, 0, char *);

	State s1 = State_newState(sec);
	State s2 = State_newState(sec); 

	if (!State_equals(s1, s2)) {
		printf("\tErrored with s1 <%s> and s2 <%s>\n", State_getState(s1), State_getState(s2));
	}

	if (State_equals(s1, s2)) {

		State_destroy(&s1);
		State_destroy(&s2);
		return QCC_OK;
	}
	else {

		State_destroy(&s1);
		State_destroy(&s2);
		return QCC_FAIL;
	}
}

/*  C-ST-EQ-03  */
QCC_TestStatus test_InequalObjects(QCC_GenValue **vals, int len, QCC_Stamp **stamp) {

	char *sec1 = QCC_getValue(vals, 0, char *);
	char *sec2 = QCC_getValue(vals, 1, char *);

	if (strcmp(sec1, sec2) == 0) {
		// Modificamos manualmente una cadena si coincide que son la misma
		sec1[0] +=1;
	}

	State s1 = State_newState(sec1);
	State s2 = State_newState(sec2); 

	if (State_equals(s1, s2)) {
		printf("\tErrored with sec1 <%s> and sec2 <%s>\n", State_getState(s1), State_getState(s2));
	}

	if (State_equals(s1, s2)) {

		State_destroy(&s1);
		State_destroy(&s2);
		return QCC_FAIL;
	}
	else {

		State_destroy(&s1);
		State_destroy(&s2);
		return QCC_OK;
	}
}

/*  C-ST-EQ-04  */
void test_EqualToNullObject(void) {

	State s = State_newState("asdf");

	CU_ASSERT_FALSE(State_equals(s, NULL));
	CU_ASSERT_FALSE(State_equals(NULL, s));

	State_destroy(&s);
}

/*  C-ST-STR-01  */
void test_ToString(void) {

	char sec[] = "fdsa";

	State s = State_newState(sec);

	CU_ASSERT_PTR_NOT_EQUAL(sec, State_getState(s));
	CU_ASSERT_PTR_EQUAL(State_getState(s), State_toString(s));

	State_destroy(&s);
}

/*
  Función principal para la ejecución de las pruebas.
  Devuelve CUE_SUCCESS si pasan correctamente,
  o un error CUnit si alguna falla.
 */
int main()
{

	printf("\n\nBEGIN STATE MODULE'S UNIT TESTING\n");

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

	/* añadir las pruebas de la suite State */
	/* ATENCIÓN: EL ORDEN ES IMPORTANTE */

	if (NULL == CU_add_test(pSuite, "C-ST-NEW-01" , test_NewStateWithNullSequence)
	||  NULL == CU_add_test(pSuite, "C-ST-NEW-02", test_NewStateWithVoidSequence)
	||  NULL == CU_add_test(pSuite, "C-ST-EQ-04", test_EqualToNullObject)
	||  NULL == CU_add_test(pSuite, "C-ST-STR-01", test_ToString))
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

	printf("C-ST-NEW-03:\t");
	QCC_testForAll(1000, 1, test_AnyStringState, 1, QCC_genString);
	printf("C-ST-HASH-01:\t");
	QCC_testForAll(1000, 1, test_HashCodeWithEqualObjects, 1, QCC_genString);
	printf("C-ST-EQ-01:\t");
	QCC_testForAll(1000, 1, test_EqualByReferenceObjects, 1, QCC_genString);
	printf("C-ST-EQ-02:\t");
	QCC_testForAll(1000, 1, test_EqualByValueObjects, 1, QCC_genString);
	printf("C-ST-EQ-03:\t");
	QCC_testForAll(1000, 1, test_InequalObjects, 2, QCC_genString, QCC_genString);

	printf("\n\nEND STATE MODULE'S UNIT TESTING\n");

	return 0;
}
