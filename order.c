/**
 * CI3825: Sistemas de Operación
 * Valeria Vera
 * 16-11233
 * 
 * - order.h: Funciones utilizadas para organizar
 *   ascendentemente el arreglo dinámico de claves y posiciones.
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

/** ORDENAMIENTO ACORDE A LA CLAVE**/
/**
 * Función de comparación para qsort en el caso de
 * clave numérica.
 * 
 * Entrada:
 *  - Dos apuntadores void que tomarán los valores
 *    de las claves numéricas a comparar.
 * 
 * Salida: Entero que indica si la primera
 *  clave es menor, igual o mayor a la segunda.
*/
int compareN(const void *a, const void *b) {
    Tuple *ia = (Tuple *)a;
    Tuple *ib = (Tuple *)b;

    return ia->keyN - ib->keyN;
}

/**
 * Función de comparación para qsort en el caso de
 * clave alfanumérica.
 * 
 * Entrada:
 * - Dos apuntadores void que tomarán los valores
 *   de las claves alfanuméricas a comparar.
 * 
 * Salida: Entero que indica si la primera
 *  clave es menor, igual o mayor a la
 *  segunda.
*/
int compareA(const void *a, const void *b) {
    Tuple *ia = (Tuple *)a;
    Tuple *ib = (Tuple *)b;

    return strcmp(ia->keyA, ib->keyA);
}

/**
 * Función que organiza el arreglo dinámico de claves
 * y posiciones con ayuda de qsort de acuerdo al valor
 * de las claves de c/u.
 * 
 * Entrada:
 * - a: arreglo dinámico a organizar.
 * - type: tipo de clave del arreglo a ordenar.
*/
void organizePairs(Array *a, char* type) {
    if (strcmp(type, "a") == 0) {
        qsort(a->data, a->used, sizeof(Tuple), compareA);
    } else if (strcmp(type, "n") == 0) {
        qsort(a->data, a->used, sizeof(Tuple), compareN);
    }
}
