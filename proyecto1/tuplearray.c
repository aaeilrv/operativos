#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "Tuple.h"
#include "Array.h"
#include "Pair.h"

/**
 * Inicializa un arreglo dinámico.
 * 
 * Entrada:
 *  - array: Apuntador al arreglo dinámico a inicializar.
 *  - initSize: Tamaño inicial del arreglo.
*/
void initArray(Array *array, int initSize) {
    array->size = initSize;
    array->used = 0;
    array->data = malloc(10 * sizeof(Tuple));

    if (!array->data) {
        printf("Error: No se pudo reservar memoria para el arreglo.");
        exit(1);
    }
}

/**
 * Inserta un elemento al arreglo dinamico y
 * reserva más memoria en caso de que este esté
 * lleno.
 * 
 * Entrada:
 * - array: arreglo dinamico.
 * - value: elemento a insertar.
 */
void insertArray(Array* array, Tuple* value) {
    if (array->size == array->used) {
        array->size += array->size;
        array->data = realloc(array->data, array->size * sizeof(Tuple));

        if (!array->data) {
            printf("Error: No se pudo reservar más memoria para el arreglo.");
            exit(1);
        }
    }
    array->data[array->used++] = *value;
}

/**
 * Libera espacio de memoria reservado para
 * el arreglo dinámico.
 * 
 * Entrada: 
 * - array: Apuntador al arreglo dinámico.
 */
void freeArray(Array* array) {
    free(array->data);
    array->data = NULL;
    array->used = array->size = 0;
}
