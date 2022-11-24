/**
 * Valeria Vera
 * 16-11233
 * Estructuras definidas
*/

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "Tuple.h"
#include "Array.h"
#include "Pair.h"
#include "ListaChar.h"

#define MAX 500

Tuple* createTuple() {
    struct Tuple* tuple = malloc(sizeof(struct Tuple));
    char* dirname = malloc(sizeof(char) * MAX);
    char* indent = malloc(sizeof(char) * MAX);

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
