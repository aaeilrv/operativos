/**
* CI3825: Sistemas de Operación
* Valeria Vera Herrera
* 16-11233
*
* Implementación de algoritmos de búsqueda linear
* y binaria.
*/

#ifndef __SEARCHALG_H__
#define __SEARCHALG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void SearchAlg(char* key, char* type, Array *a, Array *b, FILE *fp_binary,
            FILE *fp_linear, char filename_binary[], char filename_linear[]);
void BinarySearch(Array* a, Array* b, char* key, char* type, FILE *fp, char filename[]);
void LinearSearch(Array *a, char* key, char* type, FILE *fp, char filename[]);

#endif