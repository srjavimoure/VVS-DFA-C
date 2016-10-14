/*
  FILE: Alphabet-test.c
  DESCRIPTION: Fichero de pruebas de unidad cUnit para Alphabet.
  AUTHOR: 
  LICENSE:
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Alphabet.h"
#include "mocks/MockSymbol.c"
#include "mocks/MockGenList.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

/*
  Función de inicialización de las pruebas.
 */
int init_suite1(void)
{
  return 0;
}

/*
  Función de finalización de las pruebas.
 */
int clean_suite1(void)
{
  return 0;
}

/*
  Prueba de unidad.
 */
void test_Alphabet(void)
{
	CU_PASS("Alphabet passed.\n");
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
   pSuite = CU_add_suite("Suite_Alphabet", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* añadir las pruebas al conjunto */
   /* ATENCIÓN: EL ORDEN ES IMPORTANTE */
   if (NULL == CU_add_test(pSuite, "Prueba de Alphabet", test_Alphabet))
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
