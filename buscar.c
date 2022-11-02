#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Array.h"
#include "Tuple.h"

void initArray(Array *array, int initSize);
void insertArray(Array *array, struct Tuple* value);
void freeArray(Array *aray);

char* cutLine(char *file, int i, int n);
Tuple* createTuple(char* key, char* name, int number, char* type);
void createRecords(char filename[], struct Array* a, struct Array* b, char* type);
void searchKeys(char filename[], struct Array* a, struct Array* b, char* type);

int compareN(const void *a, const void *b);
int compareA(const void *a, const void *b);
void organizePairs(Array *b, char* type);

void SearchAlg(char* key, char* type, Array *a, Array *b, FILE* fp_binary, FILE* fp_linear);
void BinarySearch(Array* a, Array *b, char* key, char* type, FILE* fp);
void LinearSearch(Array *a, char* key, char* type, FILE* fp);

void BinaryPrint(Array* a, char* keyA, int keyN, int position, char* type, double time, int found, FILE* fp);
void LinearPrint(Array* a, char* keyA, int keyN, char* type, int i, double time, int found, FILE* fp);

/** ARREGLO DINAMICO **/

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
        printf("Error: No se pudo reservar memoria para el arreglo dinamico.");
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
void insertArray(Array* array, struct Tuple* value) {
    if (array->size == array->used) {
        array->size += array->size;
        array->data = realloc(array->data, array->size * sizeof(Tuple));

        if (!array->data) {
            printf("Error: No se pudo reservar más memoria para el arreglo dinamico.");
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

/** MANEJO DE REGISTROS **/
/**
 * Corta una sección de un string con ayuda de strncpy.
 * 
 * Entrada:
 * - line: cadena de caracteres a ser cortada.
 * - i: posición de la cadena desde donde se
 *      cortará.
 * - n: cantidad de caracteres a cortar.
 * 
 * Salida:
 *      Apuntador a cadena de caracteres.
 */ 
char* cutLine(char* line, int i, int n) {
    char* str = malloc((n + 1) * sizeof(char));

    if (!str) {
        printf("Error: No se pudo reservar memoria para el arreglo.");
        exit(1);
    }

    strncpy(str, &line[i], n);    
    str[n] = 0;

    if (!str) {
        exit(1);
    }
    
    return str;
}

/**
 * Crea las tuplas que se insertarán en los
 * arreglos dinámicos.
 * 
 * Entrada:
 * - key: clave de la tupla
 * - name: nombre de la tupla en caso de poseerla
 * - number: valor numérico de la tupla, puede ser
 *          tanto el dato de edad como la posición.
 * - type: tipo de clave que se está manejando
 * 
 * Salida: Apuntador a tupla con los datos de entrada.
*/
Tuple* createTuple(char* key, char* name, int number, char* type) {
    Tuple* newTuple = malloc(sizeof(Tuple)); 

    if (!newTuple) {
        printf("Error: No se pudo reservar memoria para la tupla");
        exit(1);
    }

    /* Define cómo guardar la tupla de acuerdo
    al tipo de clave. En caso alfanumérico, el
    valor de la clave keyN es el mayor acercamiento
    al valor infinito en C. */
    if (strcmp(type, "a") == 0) {
        newTuple->keyA = key;
        newTuple->keyN = 2147483647;
        newTuple->name = name;
        newTuple->number = number;
    } else if (strcmp(type, "n") == 0) {

        newTuple->keyN = atoi(key);
        newTuple->keyA = "";
        newTuple->name = name;
        newTuple->number = number;
    }

    return newTuple;
}

/**
 * Lee las líneas de un archivo, las divide y las
 * agrega en un arreglo dinámico. A su vez agrega
 * en otro array dinámico de tuplas las claves y
 * sus posiciones en el primer arreglo.
 * 
 * Entrada:
 * - filename: nombre del archivo a leer. 
 * - a: array dinámico donde se agregan los registros.
 * - b: array dinámico donde se agregan las claves.
 *      y sus posiciones.
 * - type: tipo de clave a usar (numérica o alfanumérica).
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
        char* name = cutLine(linea, 6, 20);
        char* number = cutLine(linea, 26, 2);

        Tuple* three = createTuple(key, name, atoi(number), type);
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
 * las líneas de un archivo, luego llama a los
 * algoritmos de búsqueda.
 * 
 * Entrada: 
 * - Filename: archivo donde se encuentran las claves.
 * - a: array dinámico donde se encuentran los registros.
 * - b: array dinámico donde se encuentran las claves y 
 *      sus posiciones.
 * - type: tipo de clave de los registros.
*/
void searchKeys(char filename[], struct Array* a, struct Array* b, char* type) {
    FILE *fp;
    FILE *fp_binary;
    FILE *fp_linear;

    char linea[6];
    fp = fopen(filename, "r");
    fp_binary = fopen("salidaIndice.txt", "w");
    fp_linear = fopen("salidaSecuencial.txt", "w");

    if (fp == NULL) {
        printf("Error al abrir el archivo");
        exit(1);
    }

    while(fgets(linea, sizeof(linea) + 1, fp)) {
        char* key = cutLine(linea, 0, 6);
        if (strcmp(key, "\n") > 0 || strcmp(key, "\n") < 0) {
            SearchAlg(key, type, a, b, fp_binary, fp_linear);
        }
    }

    fclose(fp);
}

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

/** ALGORITMOS DE BÚSQUEDA **/
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
 * - fp_binary: archivo donde se escribirá el resultado de
 *      la búsqueda binaria.
 * - fp_linear: archivo donde se escribirá el resultado de
 *      la búsqueda lineal.
*/
void SearchAlg(char* key, char* type, Array *a, Array *b,
                FILE *fp_binary, FILE *fp_linear) {

    BinarySearch(a, b, key, type, fp_binary);
    LinearSearch(a, key, type, fp_linear);
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
 * * fp: archivo donde se escribirá el resultado de
 *      la búsqueda.
*/
void BinarySearch(Array* a, Array* b, char* key, char* type, FILE *fp) {
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
            BinaryPrint(a, b->data[m].keyA, b->data[m].keyN, b->data[m].number, type, time_taken, found, fp);
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
        BinaryPrint(a, key, atoi(key), b->data[m].number, type, time_taken, found, fp);
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
 * - fp: archivo donde se escribirá el resultado
 *      de la búsqueda.
*/
void LinearSearch(Array *a, char* key, char* type, FILE *fp) {
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
            LinearPrint(a, a->data[i].keyA, a->data[i].keyN, type, i, time_taken, found, fp);
        }
        i++;
    }

    if (!found) {
        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC; 
        LinearPrint(a, key, atoi(key), type, i, time_taken, found, fp);
    }
}

/** IMPRESION **/
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
 * - fp: archivo donde se escribirá el resultado de la búsqueda.
*/
void BinaryPrint(Array* a, char* keyA, int keyN, int position, char* type,
                double time, int found, FILE* fp) {
    double ms = time * 1000;
    fp = fopen("salidaIndice.txt", "a+");

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
 * - found: variable que indica si se encontró o no la clave
 *     buscada.
 * - fp: archivo donde se escribirá el resultado de la búsqueda.
*/
void LinearPrint(Array* a, char* keyA, int keyN, char* type, int i,
                double time, int found, FILE *fp) {
    double ms = time * 1000;
    fp = fopen("salidaSecuencial.txt", "a+");

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

/** MAIN **/
int main(int argc, char **argv) {
    Array a;
    Array b;
    char* type = argv[1];

    initArray(&a, 5);
    initArray(&b, 5);

    createRecords(argv[2], &a, &b, type); 
    searchKeys(argv[3], &a, &b, type);

    freeArray(&a);
    freeArray(&b);

    return 0;
}