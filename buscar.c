#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Array.h"
#include "Tuple.h"

void initArray(Array *array, int initSize);
void insertArray(Array *array, struct Tuple* value);

char* cutLine(char *file, int i, int n);
Tuple* createTuple(char* key, char* second, int first, char* type);
void createRecords(char filename[], struct Array* a, struct Array* b, char* type);
void searchKeys(char filename[], struct Array* a, struct Array* b, char* type);

int compareN(const void *a, const void *b);
int compareA(const void *a, const void *b);
void organizePairs(Array *b, char* type);

void SearchAlg(char* key, char* type, Array *a, Array *b);
void BinarySearch(Array* a, Array *b, char* key, char* type);
void LinearSearch(Array *a, char* key, char* type);

/** ARREGLO DINAMICO DE TupleAS **/
void initArray(Array *array, int initSize) {
    array->size = initSize;
    array->used = 0;
    array->data = malloc(10 * sizeof(Tuple));
}

void insertArray(Array *array, struct Tuple* value) {
    if (array->size == array->used) {
        array->size += array->size;
        array->data = realloc(array->data, array->size * sizeof(Tuple));
    }
    array->data[array->used++] = *value;
}

/** MANEJO DE REGISTROS **/
char* cutLine(char *file, int i, int n) {
    char *str = malloc((n + 1) * sizeof(char));

    strncpy(str, &file[i], n);    
    str[n] = 0;

    if (!str) {
        exit(1);
    }
    
    return str;
}

/**
 * Entrada: Apuntadores a cadenas de caracteres.
 * Salida: Tuplea con los datos de entrada.
*/
Tuple* createTuple(char* key, char* second, int first, char* type) {
    Tuple* newTuple = malloc(sizeof(Tuple)); 

    if (strcmp(type, "a") == 0) {
        newTuple->keyA = key;
        newTuple->keyN = -1;
        newTuple->second = second;
        newTuple->first = first;
    } else if (strcmp(type, "n") == 0) {

        newTuple->keyN = atoi(key);
        newTuple->keyA = "";
        newTuple->second = second;
        newTuple->first = first;
    }

    return newTuple;
}

/**
 * Lee las líneas de un archivo, las divide y las
 * agrega en un arreglo dinámico. A su vez agrega
 * en un array dinámico los pares con las claves y
 * sus posiciones en el array de Tupleas.
 * Entrada:
 *      filename: nombre del archivo a leer. 
 *      a: array dinámico donde se agregan las Tupleas
 *      b: array dinámico donde se agregan los pares
 *      type: tipo de clave a usar (numérica o alfanumérica)
*/
void createRecords(char filename[], struct Array* a, struct Array* b, char* type) {
    FILE *fp;
    char linea[29];
    int i = 0;

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error al abrir el archivo");
        exit(1);
    }

    while(fgets(linea, sizeof(linea) + 1, fp)) {
        char* key = cutLine(linea, 0, 6);
        char* second = cutLine(linea, 6, 20);
        char* first = cutLine(linea, 26, 2);

        Tuple* three = createTuple(key, second, atoi(first), type);
        Tuple* two = createTuple(key, "", i, type);

        insertArray(a, three);
        insertArray(b, two);

        i++;
    }

    organizePairs(b, type);

    fclose(fp);
}

/**
 * Lee las claves a buscar a partir de dividir
 *  las líneas de un archivo, luego llama a los
 * algoritmos de búsqueda.
 * Entrada: archivo donde se encuentran las claves,
 * dos arreglos de tuplas (uno con los datos y otro
 * con las claves y las posiciones -utilizado para
 * la búsqueda lineal-) y el tipo de clave.
*/
void searchKeys(char filename[], struct Array* a, struct Array* b, char* type) {
    FILE *fp;
    char linea[6];
    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error al abrir el archivo");
        exit(1);
    }

    while(fgets(linea, sizeof(linea) + 1, fp)) {
        char* key = cutLine(linea, 0, 6);
        SearchAlg(key, type, a, b);
    }
}

/** ORDENAMIENTO ACORDE A LA CLAVE**/
/**
 * Función de comparación para qsort en
 * el caso de clave numérica.
 * Entrada: Dos apuntadores a void.
 * Salida: Entero que indica si el primer
 * elemento es menor, igual o mayor-
*/
int compareN(const void *a, const void *b) {
    Tuple *ia = (Tuple *)a;
    Tuple *ib = (Tuple *)b;

    return ia->keyN - ib->keyN;
}

/**
 * Función de comparación para qsort en
 * el caso de clave alfanumérica.
 * Entrada: Dos apuntadores a void.
 * Salida: Entero que indica si el primer
 * elemento es menor, igual o mayor-
*/
int compareA(const void *a, const void *b) {
    Tuple *ia = (Tuple *)a;
    Tuple *ib = (Tuple *)b;

    return strcmp(ia->keyA, ib->keyA);
}

/**
 * Ordena el array de tuplas acorde a la clave.
 * Entrada: Array de tuplas, tipo de clave.
*/
void organizePairs(Array *b, char* type) {
    if (strcmp(type, "a") == 0) {
        qsort(b->data, b->used, sizeof(Tuple), compareA);
    } else if (strcmp(type, "n") == 0) {
        qsort(b->data, b->used, sizeof(Tuple), compareN);
    }
}

/* IMPRESION*/
void BinaryPrint(Array* a, char* keyA, int keyN, int position, char* type) {
    if (strcmp(type, "a") == 0) {
        printf("binary: %s: (%s, %s, %d)\n", keyA, a->data[position].keyA, a->data[position].second, a->data[position].first);
    } else if (strcmp(type, "n") == 0) {
        printf("binary: %d: (%d, %s, %d)\n", keyN, a->data[position].keyN, a->data[position].second, a->data[position].first);
    } else if (strcmp(type, "c") == 0) {
        printf("binary: %s, %d: (No existe)\n", keyA, keyN);
    }
}

void LinearPrint(Array* a, char* keyA, int keyN, char* type, int i) {
    if (strcmp(type, "a") == 0) {
        printf("linear: %s: (%s, %s, %d)\n", keyA, a->data[i].keyA, a->data[i].second, a->data[i].first);
    } else if (strcmp(type, "n") == 0) {
        printf("linear: %d: (%d, %s, %d)\n", keyN, a->data[i].keyN, a->data[i].second, a->data[i].first);
        
    } else if (strcmp(type, "c") == 0) {
        printf("linear: %s, %d: (No existe)\n", keyA, keyN);
    }
}

/** ALGORITMOS DE BÚSQUEDA **/
void SearchAlg(char* key, char* type, Array *a, Array *b) {

    int i = 0;
    while (i < b->size) {
        i++;
    }

    LinearSearch(a, key, type);
    BinarySearch(a, b, key, type);
    printf("\n");
}

/**
 * Algoritmo de búsqueda binaria.
 * Entrada: Dos array de tuplas, uno donde
 * están los datos y otro con las claves y
 * sus posiciones en el array de datos; clave
 * a buscar y tipo de clave.
*/
void BinarySearch(Array* a, Array* b, char* key, char* type) {
    int i = 0;
    int j = b->used - 1;
    int m = 0;
    int found = 0;

    while (i <= j && !found) {
        m = (i + j) / 2;

        if (strcmp(type, "a") == 0) {
            if (strcmp(b->data[m].keyA, key) == 0) {
                BinaryPrint(a, b->data[m].keyA, b->data[m].keyN, b->data[m].first, type);
                found = 1;
            } else if (strcmp(b->data[m].keyA, key) < 0) {
                i = m + 1;
            } else {
                j = m - 1;
            }
        } else if (strcmp(type, "n") == 0) {
            if (b->data[m].keyN == atoi(key)) {
                BinaryPrint(a, b->data[m].keyA, b->data[m].keyN, b->data[m].first, type);
                found = 1;
            } else if (b->data[m].keyN < atoi(key)) {
                i = m + 1;
            } else {
                j = m - 1;
            }
        }
    }

    if (!found) {
        BinaryPrint(a, key, atoi(key), b->data[m].first, "c");
    }
}

/**
 * Algoritmo de implementación de búsqueda lineal.
 * Este lo hace en el arreglo de strings y su forma
 * de buscar el valor pedido es de acuerdo a la clave.
 * Entrada: array de strings, clave buscada, tipo de clave.
*/
void LinearSearch(Array *a, char* key, char* type) {
    int i = 0;
    int found = 0;

    if (strcmp(type, "a") == 0) {
        while (i < a->used && !found) {
            if (strcmp(a->data[i].keyA, key) == 0) {
                LinearPrint(a, a->data[i].keyA, i, type, i);
                found = 1;
            }
            i++;
        }
        if (!found) {
            printf("Linear: No se encontró el registro.\n");
        }
    } else if (strcmp(type, "n") == 0) {
        while (i < a->used && !found) {
            if (a->data[i].keyN == atoi(key)) {
                LinearPrint(a, a->data[i].keyA, a->data[i].keyN, type, i);
                found = 1;
            }
            i++;
        }
        if (!found) {
            LinearPrint(a, key, atoi(key), "c", 0);
        }
    }
}

int main(int argc, char **argv) {
    Array a;
    Array b;
    char* type = argv[1];

    initArray(&a, 5);
    initArray(&b, 5);

    createRecords(argv[2], &a, &b, type); 
    searchKeys(argv[3], &a, &b, type);

    return 0;
}