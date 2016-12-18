#include <stdio.h>
#include <string.h>
#include "../include/State.h"
#include "quickcheck4c.h"

/**************************************************
	PRUEBAS CON QUICKCHECK PARA EL MÓDULO STATE
***************************************************/

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

/*
  Función principal para la ejecución de las pruebas.
  Devuelve CUE_SUCCESS si pasan correctamente,
  o un error CUnit si alguna falla.
 */
int main()
{
	QCC_init(0);

	printf("\n*************************************\n\n"
		   "   QuickCheck4C testing for State:\n\n"
		   "*************************************\n\n");

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

	return 0;
}
