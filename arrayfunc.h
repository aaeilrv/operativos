/**
* CI3825: Sistemas de Operación
* Valeria Vera Herrera
* 16-11233
*
* Procedimientos auxiliares para la creación, inserción y
* eliminación de arreglos dinámicos. 
*/

#ifndef __ARRAYFUNC_H__
#define __ARRAYFUNC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void initArray(Array *array, int initSize);
void insertArray(Array *array, struct Tuple* value);
void freeArray(Array *aray);

#endif