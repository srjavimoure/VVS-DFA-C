# VVS-DFA-C
[![Build Status](https://travis-ci.org/srjavimoure/VVS-DFA-C.svg?branch=master)](https://travis-ci.org/srjavimoure/VVS-DFA-C)

Práctica para la asignatura de Validación y Verificación Software.  

Integrantes:  
-*Francisco Javier López Moure*  
-*Emma Oitaven Carracedo*  
-*Xoán Andreu Barro Torres*  

La aplicación sobre la que haremos tests simplifica DFA (Autómatas Finitos Deterministas), eliminando transiciones redundantes y estados inalcanzables, para obtener un DFA equivalente (capaz de aceptar el mismo lenguaje).  

Esta aplicación fue programada en tres lenguajes distintos:  

C: Este repositorio  
Java: https://github.com/andreu-barro/VVS-DFA-JAVA  
Ocaml: https://github.com/andreu-barro/VVS-DFA-OCAML  

### Ejecución y creación de documentos

Para la ejecución de las pruebas, se emplea el siguiente comando:  

`make tests`  

Esto lanzará todas las pruebas encontradas en la carpeta `test/`. Sin embargo, esto no generará la documentación de cobertura y cppcheck.  

Para generar la documentación, se emplea el siguiente comando:  

`make doc`  

Por último, para ejecutar la aplicación con los autómatas de ejemplo en la carpeta `resources/`, se emplea el siguiente comando:  

`make run file=*nombre_archivo*`

O también, para compilar previamente (lo cual incluye ejecutar las pruebas):  

`make file=*nombre_archivo*`

No es necesario especificar la carpeta `resources/` a la hora de dar el nombre del archivo del autómata.  
