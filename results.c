/**
 * CI3825: Sistemas de Operación
 * Valeria Vera
 * 16-11233
 * 
 * - results.h: Funciones utilizadas para captar y
 *    guardar los resultados de las búsquedas en un archivo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Array.h"
#include "Tuple.h"

#include "arrayfunc.h"
#include "records.h"
#include "order.h"
#include "searchalg.h"
#include "results.h"

/**
 * Función que imprime el resultado de la búsqueda binaria.
 * 
 * Entrada:
 * - a: arreglo dinámico de valores.
 * - keyA: clave alfanumérica a buscar en caso de ser claves
 *     de tipo alfanumérica.
 * - keyN: clave numérica a buscar en caso de ser claves de
 *     tipo numérica.
 * - position: posición en el arreglo a donde se encuentra
 *     la clave buscada.
 * - type: tipo de clave.
 * - time: tiempo en segundos que tomó la búsqueda.
 * - found: variable que indica si se encontró o no la clave
 *     buscada.    
 * - fp: apuntador del archivo donde se escribirá el resultado
 *     de la búsqueda.
 * - filename: nombre del archivo donde se escribirá el resultado.
*/
void BinaryPrint(Array* a, char* keyA, int keyN, int position, char* type,
                double time, int found, FILE* fp, char filename[]) {

    double ms = time * 1000;
    fp = fopen(filename, "a+");

    if (found) {
        if (strcmp(type, "a") == 0) {
            fprintf(fp, "%s: (%s, %s, %d) %gms\n", keyA, a->data[position].keyA,
                    a->data[position].name, a->data[position].number, ms);
        } else if (strcmp(type, "n") == 0) {
            fprintf(fp, "%d: (%d, %s, %d) %gms\n", keyN, a->data[position].keyN,
                    a->data[position].name, a->data[position].number, ms);
        }
    } else if (!found) {
        if (strcmp(type, "a") == 0) {
            fprintf(fp, "%s: (No existe) %gms\n", keyA, ms);
        } else if (strcmp(type, "n") == 0) {
            fprintf(fp, "%d: (No existe) %gms\n", keyN, ms);
        }
    }

    fclose(fp);
}

/**
 * Función que imprime el resultado de la busqueda lineal.
 * 
 * Entrada:
 * - a: array donde se implementó la búsqueda.
 * - keyA: clave alfanumérica a buscar en caso de ser claves
 *     de tipo alfanumérica.
 * - keyN: clave numérica a buscar en caso  de ser claves de
 *     tipo numérica.
 * - type: tipo de clave.
 * - position: posición en el arreglo a donde se encuentra la
 *     clave buscada.
 * - time: tiempo en segundos que tomó la búsqueda.
 * - found: variable que indica si se encontró o no la clave buscada.
 * - filename: nombre archivo donde se escribirá el resultado de la búsqueda.
*/
void LinearPrint(Array* a, char* keyA, int keyN, char* type, int i,
                double time, int found, FILE* fp, char filename[]) {

    double ms = time * 1000;
    fp = fopen(filename, "a+");

    if (found) {
        if (strcmp(type, "a") == 0) {
            fprintf(fp, "%s: (%s, %s, %d) %gms\n", keyA, a->data[i].keyA,
                    a->data[i].name, a->data[i].number, ms);
        } else if (strcmp(type, "n") == 0) {
            fprintf(fp, "%d: (%d, %s, %d) %gms\n", keyN, a->data[i].keyN,
                    a->data[i].name, a->data[i].number, ms);
            
        }  
    } else if (!found) {
        if (strcmp(type, "a") == 0) {
            fprintf(fp, "%s: (No existe) %gms\n", keyA, ms);
        } else if (strcmp(type, "n") == 0) {
            fprintf(fp, "%d: (No existe) %gms\n", keyN, ms);
        }
    }

    fclose(fp);
}