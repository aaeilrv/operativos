/**
* CI3825: Sistemas de Operación
* Valeria Vera Herrera
* 16-11233
*
* EDITAR 
*/

#ifndef __AUXESTRUCT_H__
#define __AUXESTRUCT_H__

#include <stdio.h>

void initArray(Array *array, int initSize);
void insertArray(Array* array, Tuple* value);
void freeArray(Array* array);

#endif