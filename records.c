/**
 * CI3825: Sistemas de Operación
 * Valeria Vera
 * 16-11233
 * 
 * - records.h: Funciones auxiliares para la lectura de datos,
 *   creación de tuplas y guardado de ellas en arreglos dinámicos.
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

void insertArray(Array *array, struct Tuple* value);

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
        printf("Error al abrir el archivo de datos.");
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
 * - dilename: nombre del archivo donde se encuentran las
    claves.
 * - file_binary: nombre del archivo a crear donde se
 *  guardarán los resultados de la búsqueda binaria.
* - file_linear: nombre del archivo a crear donde se
 *  guardarán los resultados de la búsqueda secuencial.
 * - a: array dinámico donde se encuentran los registros.
 * - b: array dinámico donde se encuentran las claves y 
 *      sus posiciones.
 * - type: tipo de clave de los registros.
*/
void searchKeys(char filename[], char file_binary[], char file_linear[],
                struct Array* a, struct Array* b, char* type) {
    FILE *fp;
    FILE *fp_binary;
    FILE *fp_linear;

    char linea[6];
    fp = fopen(filename, "r");
    fp_binary = fopen(file_binary, "w");
    fp_linear = fopen(file_linear, "w");

    if (fp == NULL) {
        printf("Error al abrir el archivo de claves.");
        exit(1);
    }

    while(fgets(linea, sizeof(linea) + 1, fp)) {
        char* key = cutLine(linea, 0, 6);
        if (strcmp(key, "\n") > 0 || strcmp(key, "\n") < 0) {
            SearchAlg(key, type, a, b, fp_binary, fp_linear, file_binary, file_linear);
        }
    }

    fclose(fp);
}