#include <string.h>
#include <stdio.h>
#include "../include/GenList.h"
// Generación de datos aleatoria
#include "quickcheck4c.h"

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

int main()
{

	QCC_init(0);

	printf("\n*************************************\n\n"
		   "   QuickCheck4C testing for GenList:\n\n"
		   "*************************************\n\n");

	printf("C-GLIST-NEW-01:\t");
	QCC_testForAll(1000, 1, test_NewGenListNegBuffer, 1, QCC_genNegativeInt);
	printf("C-GLIST-NEW-03:\t");
	QCC_testForAll(1000, 1, test_NewGenListPosBuffer, 1, QCC_genPositiveInt);

	return 0;
}
