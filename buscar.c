#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Array.h"
#include "Triplet.h"

void BinarySearch(Array *a, char* key, char* type);
void LinearSearch(Array *a, char* key, char* type);

/** ARREGLO DINAMICO **/
void initArray(Array *array, int initSize) {
    array->size = initSize;
    array->used = 0;
    array->data = malloc(10 * sizeof(Triplet));
}

void insertArray(Array *array, struct Triplet* value) {
    if (array->size == array->used) {
        array->size += array->size;
        array->data = realloc(array->data, array->size * sizeof(Triplet));
    }
    array->data[array->used++] = *value;
}

void freeArray(Array *array) {
    free(array->data);
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
Triplet* createTriplet(char* key, char* name, char* age) {
    Triplet* newTriplet = malloc(sizeof(Triplet)); 

    newTriplet->key = key;
    newTriplet->name = name;
    newTriplet->age = age;

    return newTriplet;
}

/**
 * Lee las líneas de un archivo. Dependiendo del tipo
 * indicado, la función crea una tripleta con los datos
 * que posteriormente agrega a un arreglo dinámico o
 * llama a la función "Search".
*/
void createRecords(char filename[], int data, struct Array* a, char* type) {
    FILE *fp;
    char linea[29];

    fp = fopen(filename, "r");

    while(fgets(linea, sizeof(linea) + 1, fp)) {

        if (data == 0) {
            char* key = cutLine(linea, 0, 6);
            char* name = cutLine(linea, 6, 20);
            char* age = cutLine(linea, 26, 2);

            Triplet* three = createTriplet(key, name, age);

            insertArray(a, three);
            
        } else if (data == 1) {
            char* key = cutLine(linea, 0, 6);
            printf("key: %s\n", key);
            BinarySearch(a, key, type);
            LinearSearch(a, key, type);
        }
    }
}

/** ALGORITMOS DE BÚSQUEDA **/
void BinarySearch(Array *a, char* key, char* type) {
    int i = 0;
    int j = a->used - 1;
    int m = (i + j) / 2;

    if (strcmp(type, "a") == 0) {
        while (i <= j) {
            if (strcmp(a->data[m].key, key) < 0) {
                i = m + 1;
            } else if (strcmp(a->data[m].key, key) == 0) {
                printf("Nombre: %s\n", a->data[m].name);
                printf("Edad: %s\n", a->data[m].age);
                break;
            } else {
                j = m - 1;
            }
            m = (i + j) / 2;
        }
        if (i > j) {
            printf("No se encontró el registro.\n");
        }
    } else if (strcmp(type, "n") == 0) {

    }
}

void LinearSearch(Array *a, char* key, char* type) {
    int i = 0;
    int found = 0;

    if (strcmp(type, "a") == 0) {
        while (i < a->used && !found) {
            if (strcmp(a->data[i].key, key) == 0) {
                printf("Nombre: %s\n", a->data[i].name);
                printf("Edad: %s\n", a->data[i].age);
                found = 1;
            }
            i++;
        }
        if (!found) {
            printf("No se encontró el registro.\n");
        }
    } else if (strcmp(type, "n") == 0) {

    }
}

int main(int argc, char **argv) {
    Array a;
    char* type = argv[1];

    initArray(&a, 10);
    createRecords(argv[2], 0, &a, type);

    printf("%s\n", a.data[0].key);
    printf("%d\n", a.used);
    
    createRecords(argv[3], 1, &a, type);

    return 0;
}