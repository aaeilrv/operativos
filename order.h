/**
* CI3825: Sistemas de Operación
* Valeria Vera Herrera
* 16-11233
*
* Funciones auxiliares para la organización lineal
* ascendente de arreglos dinámicos.
*/

#ifndef __ORDER_H__
#define __ORDER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareN(const void *a, const void *b);
int compareA(const void *a, const void *b);
void organizePairs(Array *a, char* type);

#endif