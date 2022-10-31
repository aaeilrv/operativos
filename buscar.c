#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ArrayT.h"
#include "ArrayP.h"
#include "Pair.h"
#include "Triplet.h"

void initArray_T(ArrayT *array, int initSize);
void insertArray_T(ArrayT *array, struct Triplet* value);

void initArray_P(ArrayP *array, int initSize);
void insertArray_P(ArrayP *array, struct Pair* value);

char* cutLine(char *file, int i, int n);
Triplet* createTriplet(char* key, char* name, char* age, char* type);
Pair* createPair(char* key, int position, char* type);
void createRecords(char filename[], struct ArrayT* a, struct ArrayP* b, char* type);
void searchKeys(char filename[], struct ArrayT* a, struct ArrayP* b, char* type);

int compareN(const void *a, const void *b);
int compareA(const void *a, const void *b);
void organizePairs(ArrayP *b, char* type);

void SearchAlg(char* key, char* type, ArrayT *a, ArrayP *b);
void BinarySearch(ArrayP *a, char* key, char* type);
void LinearSearch(ArrayT *a, char* key, char* type);

/** ARREGLO DINAMICO DE TRIPLETAS **/

void initArray_T(ArrayT *array, int initSize) {
    array->size = initSize;
    array->used = 0;
    array->data = malloc(10 * sizeof(Triplet));
}

void insertArray_T(ArrayT *array, struct Triplet* value) {
    if (array->size == array->used) {
        array->size += array->size;
        array->data = realloc(array->data, array->size * sizeof(Triplet));
    }
    array->data[array->used++] = *value;
}

/* ARREGLO DINAMICO DE PARES */
void initArray_P(ArrayP *array, int initSize) {
    array->size = initSize;
    array->used = 0;
    array->data = malloc(10 * sizeof(Triplet));
}

void insertArray_P(ArrayP *array, struct Pair* value) {
    if (array->size == array->used) {
        array->size += array->size;
        array->data = realloc(array->data, array->size * sizeof(Pair));
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
 * Salida: tripleta con los datos de entrada.
*/
Triplet* createTriplet(char* key, char* name, char* age, char* type) {
    Triplet* newTriplet = malloc(sizeof(Triplet)); 

    if (strcmp(type, "a") == 0) {
        newTriplet->keyA = key;
        newTriplet->keyN = 0;
        newTriplet->name = name;
        newTriplet->age = atoi(age);
    } else if (strcmp(type, "n") == 0) {

        newTriplet->keyN = atoi(key);
        newTriplet->keyA = "";
        newTriplet->name = name;
        newTriplet->age = atoi(age);
    }

    return newTriplet;
}

Pair* createPair(char* key, int position, char* type) {
    Pair* newPair = malloc(sizeof(Pair)); 

    if (strcmp(type, "a") == 0) {
        newPair->keyA = key;
        newPair->keyN = 0;
        newPair->position = position;
    } else if (strcmp(type, "n") == 0) {
        newPair->keyN = atoi(key);
        newPair->keyA = "";
        newPair->position = position;
    }

    return newPair;
}

/**
 * Lee las líneas de un archivo, las divide y las
 * agrega en un arreglo dinámico. A su vez agrega
 * en un array dinámico los pares con las claves y
 * sus posiciones en el array de tripletas.
 * Entrada:
 *      filename: nombre del archivo a leer. 
 *      a: array dinámico donde se agregan las tripletas
 *      b: array dinámico donde se agregan los pares
 *      type: tipo de clave a usar (numérica o alfanumérica)
*/
void createRecords(char filename[], struct ArrayT* a, struct ArrayP* b, char* type) {
    FILE *fp;
    char linea[29];
    int i = 0;

    fp = fopen(filename, "r");

    /*agregar vaina por si no se abre el archivo o si no existe*/

    while(fgets(linea, sizeof(linea) + 1, fp)) {
        char* key = cutLine(linea, 0, 6);
        char* name = cutLine(linea, 6, 20);
        char* age = cutLine(linea, 26, 2);

        Triplet* three = createTriplet(key, name, age, type);
        Pair* two = createPair(key, i, type);

        insertArray_T(a, three);
        insertArray_P(b, two);

        i++;
    }

    organizePairs(b, type);

    fclose(fp);
}

void searchKeys(char filename[], struct ArrayT* a, struct ArrayP* b, char* type) {
    FILE *fp;
    char linea[6];
    fp = fopen(filename, "r");

    while(fgets(linea, sizeof(linea) + 1, fp)) {
        char* key = cutLine(linea, 0, 6);
        SearchAlg(key, type, a, b);
    }
}

/** ORDENAMIENTO ACORDE A LA CLAVE**/
int compareN(const void *a, const void *b) {
    Pair *ia = (Pair *)a;
    Pair *ib = (Pair *)b;

    return ia->keyN - ib->keyN;
}

int compareA(const void *a, const void *b) {
    Pair *ia = (Pair *)a;
    Pair *ib = (Pair *)b;

    return strcmp(ia->keyA, ib->keyA);
}

void organizePairs(ArrayP *b, char* type) {
    if (strcmp(type, "a") == 0) {
        qsort(b->data, b->used, sizeof(Pair), compareA);
    } else if (strcmp(type, "n") == 0) {
        qsort(b->data, b->used, sizeof(Pair), compareN);
    }
}


/** ALGORITMOS DE BÚSQUEDA **/
void SearchAlg(char* key, char* type, ArrayT *a, ArrayP *b) {

    int i = 0;
    while (i < b->size) {
        i++;
    }

    LinearSearch(a, key, type);
    BinarySearch(b, key, type);
}

void BinarySearch(ArrayP *b, char* key, char* type) {
    int i = 0;
    int j = b->used - 1;
    int m = 0;
    int found = 0;

    while (i <= j && !found) {
        m = (i + j) / 2;

        if (strcmp(type, "a") == 0) {
            if (strcmp(b->data[m].keyA, key) == 0) {
                printf("(%s, %d);\n", b->data[m].keyA, b->data[m].position);
                found = 1;
            } else if (strcmp(b->data[m].keyA, key) < 0) {
                i = m + 1;
            } else {
                j = m - 1;
            }
        } else if (strcmp(type, "n") == 0) {
            if (b->data[m].keyN == atoi(key)) {
                printf("(%d, %d);\n", b->data[m].keyN, b->data[m].position);
                found = 1;
            } else if (b->data[m].keyN < atoi(key)) {
                i = m + 1;
            } else {
                j = m - 1;
            }
        }
    }
}

void LinearSearch(ArrayT *a, char* key, char* type) {
    int i = 0;
    int found = 0;

    if (strcmp(type, "a") == 0) {
        while (i < a->used && !found) {
            if (strcmp(a->data[i].keyA, key) == 0) {
                printf("Nombre: %s\n", a->data[i].name);
                printf("Edad: %d\n", a->data[i].age);
                found = 1;
            }
            i++;
        }
        if (!found) {
            printf("No se encontró el registro.\n");
        }
    } else if (strcmp(type, "n") == 0) {
        while (i < a->used && !found) {
            if (a->data[i].keyN == atoi(key)) {
                printf("Nombre: %s\n", a->data[i].name);
                printf("Edad: %d\n", a->data[i].age);
                found = 1;
            }
            i++;
        }
        if (!found) {
            printf("searched key: %d\n", atoi(key));
            printf("No se encontró el registro.\n");
        }
    }
}


int main(int argc, char **argv) {
    ArrayT a;
    ArrayP b;
    char* type = argv[1];

    initArray_T(&a, 5);
    initArray_P(&b, 5);

    createRecords(argv[2], &a, &b, type); 
    searchKeys(argv[3], &a, &b, type);

    return 0;
}