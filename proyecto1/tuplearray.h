/**
 * Valeria Vera
 * 16-11233
 * Sistemas de Operación
 * 
 * Funciones para la inicialización,
 * inserción y liberación de un arreglo dinámico de tuplas.
*/

#ifndef __TUPLEARRAY_H__
#define __TUPLEARRAY_H__

#include <stdio.h>

void initArray(Array *array, int initSize);
void insertArray(Array* array, Tuple* value);
void freeArray(Array* array);

#endif