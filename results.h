/**
* CI3825: Sistemas de Operación
* Valeria Vera Herrera
* 16-11233
*
* Procedimientos auxiliares para la escritura en archivos
* de los resultados de los algoritmos de búsqueda.
*/

#ifndef __RESULTS_H__
#define __RESULTS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void BinaryPrint(Array* a, char* keyA, int keyN, int position, char* type,
                double time, int found, FILE* fp, char filename[]);
                
void LinearPrint(Array* a, char* keyA, int keyN, char* type, int i,
                double time, int found, FILE *fp, char filename[]);

#endif