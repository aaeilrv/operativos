/**
 * CI3825: Sistemas de Operación
 * Valeria Vera
 * 16-11233
 * 
 * - searchalg.h: Algoritmos de búsqueda.
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
 * Función que llama a los algoritmos de búsqueda.
 * 
 * Entrada:
 * - key: clave a buscar.
 * - type: tipo de clave a buscar.
 * - a: arreglo dinámico donde se implementará la
 *      búsqueda lineal y en el cual se hallarán las
 *      posiciones del resultado de la búsqueda binaria.
 * - b: arreglo dinámico donde se implementará la búsqueda
 *      binaria.
 * - fp_binary: apuntador al archivo donde se escribirá el
 *  resultado de la búsqueda binaria.
 * - fp_linear: apuntador al archivo donde se escribirá el
 *   resultado de la búsqueda lineal.
 * - filename_binary: nombre del archivo donde se escribirá
 *   el resultado de la búsqueda binaria.
 * - filename_linear: nombre del archivo donde se escribirá
 *   el resultado de la búsqueda secuencial.
*/
void SearchAlg(char* key, char* type, Array *a, Array *b,
                FILE *fp_binary, FILE *fp_linear, char filename_binary[], char filename_linear[]) {

    BinarySearch(a, b, key, type, fp_binary, filename_binary);
    LinearSearch(a, key, type, fp_linear, filename_linear);
}

/**
 * Algoritmo de búsqueda binaria.
 * 
 * Entrada: 
 * - a: arreglo de valores donde se se verá el
 *      resultado en caso de ser hallado.
 * - b: arreglo de claves y sus posiciones en el
 *      arreglo a.
 * - key: clave a buscar.
 * - type: tipo de clave a buscar.
 * - fp: apuntador al archivo donde se escribirá
 *   el resultado de la búsqueda.
 * - filename: nombre del archivo donde se escribirá
 *   el resultado de la búsqueda.
*/
void BinarySearch(Array* a, Array* b, char* key, char* type, FILE *fp, char filename[]) {
    int i = 0;
    int j = b->used - 1;
    int m = 0;
    int found = 0;

    clock_t t;
    double time_taken;
    t = clock();

    while (i <= j && !found) {
        m = (i + j) / 2;
        if ((strcmp(type, "a") == 0 && strcmp(b->data[m].keyA, key) == 0) ||
            (strcmp(type, "n") == 0 && b->data[m].keyN == atoi(key))) {
            found = 1;

            t = clock() - t;
            time_taken = ((double)t)/CLOCKS_PER_SEC; 
            BinaryPrint(a, b->data[m].keyA, b->data[m].keyN, b->data[m].number, type, time_taken, found, fp, filename);
        } else if (((strcmp(type, "a") == 0 && strcmp(b->data[m].keyA, key) < 0) ||
            (strcmp(type, "n") == 0 && b->data[m].keyN < atoi(key)))) {
            i = m + 1;
        } else {
            j = m - 1;
        }
    }

    if (!found) {
        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC; 
        BinaryPrint(a, key, atoi(key), b->data[m].number, type, time_taken, found, fp, filename);
    }
}

/**
 * Algoritmo de búsqueda lineal.
 * 
 * Entrada:
 * - a: arreglo de valores donde se implementará
 *      la búsqueda.
 * - key: clave a buscar.
 * - type: tipo de clave a buscar.
 * - fp: apuntador al archivo donde se escribirá
 *   el resultado de la búsqueda.
 * - filename: nombre del archivo donde se escribirá
 *   el resultado de la búsqueda.
*/
void LinearSearch(Array *a, char* key, char* type, FILE *fp, char filename[]) {
    int i = 0;
    int found = 0;

    clock_t t;
    double time_taken;
    t = clock();

    while (i < a->used && !found) {
        if ((strcmp(type, "a") == 0 && strcmp(a->data[i].keyA, key) == 0) ||
            (strcmp(type, "n") == 0 && a->data[i].keyN == atoi(key))) {
            found = 1;
            t = clock() - t;
            time_taken = ((double)t)/CLOCKS_PER_SEC;
            LinearPrint(a, a->data[i].keyA, a->data[i].keyN, type, i, time_taken, found, fp, filename);
        }
        i++;
    }

    if (!found) {
        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC; 
        LinearPrint(a, key, atoi(key), type, i, time_taken, found, fp, filename);
    }
}