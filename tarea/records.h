/**
* CI3825: Sistemas de Operación
* Valeria Vera Herrera
* 16-11233
*
* Funciones y estructuras auxiliares que ayudan
* al manejo de los registros y claves proporcionados
* por el usuario.
*/

#ifndef __RECORDS_H__
#define __RECORDS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* cutLine(char *file, int i, int n);
Tuple* createTuple(char* key, char* name, int number, char* type);
void createRecords(char filename[], struct Array* a, struct Array* b, char* type);
void searchKeys(char filename[], char file_binary[], char file_linear[],struct Array* a, struct Array* b, char* type);

#endif