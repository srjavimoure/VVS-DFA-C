#include <string.h>
#include <stdio.h>
#include "../include/Symbol.h"
// Generación de datos aleatoria
#include "quickcheck4c.h"

/**********************************************

	PRUEBAS DE UNIDAD PARA EL MÓDULO SYMBOL

**********************************************/

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

/*
  Función principal para la ejecución de las pruebas.
  Devuelve CUE_SUCCESS si pasan correctamente,
  o un error CUnit si alguna falla.
 */
int main()
{
	QCC_init(0);

	printf("\n*************************************\n\n"
		   "   QuickCheck4C testing for Symbol:\n\n"
		   "*************************************\n\n");

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

	return 0;
}
