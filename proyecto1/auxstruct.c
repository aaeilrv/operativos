/**
 * Valeria Vera
 * 16-11233
 *
 * Funciones para la creación de tuplas
 * y la creación de pares.
*/

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "Tuple.h"
#include "Array.h"
#include "Pair.h"
#include "ListaChar.h"

#define MAX 500

/**
 * Nos permite crear una tupla con todos
 * sus elementos enteros inicializados en 0
 * y espacio reservado para sus elementos de tipo
 * char.
*/
Tuple* createTuple() {
    struct Tuple* tuple = malloc(sizeof(struct Tuple));
    char* dirname = malloc(sizeof(char) * MAX + 1);
    char* indent = malloc(sizeof(char) * MAX + 1);

    if (!tuple) {
        printf("Error: No se pudo reservar memoria\n");
        exit(1);
    }

    if (!dirname) {
        printf("Error: No se pudo reservar memoria\n");
        exit(1);
    }

    if (!indent) {
        printf("Error: No se pudo reservar memoria\n");
        exit(1);
    }

    tuple->regular_files = 0;
    tuple->directories = 0;
    tuple->symbolic_links = 0;
    tuple->bytes = 0;
    tuple->dir_name = dirname;
    tuple->indent = indent;

    return tuple;
}

/**
 * Nos permite crear un par de un entero
 * representando el número de inodo y una lista
 * de caracteres representando los archivos que
 * comparten ese inodo.
 * 
 * Entrada:
 * - int inode: número de inodo
 * - dirnames: lista de caracteres.
*/
Pair* createPair(int inode, ListaChar* dirnames) {
    struct Pair* pair = malloc(sizeof(struct Pair));

    if (!pair) {
        printf("Error: No se pudo reservar memoria para el par");
        exit(1);
    }

    pair->inode_number = inode;
    pair->dirnames = dirnames;

    return pair;
}
