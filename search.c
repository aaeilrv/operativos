#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Node.h"
#include "Lista.h"
#include "Tupla.h"


/*
* Retorno: Pointer a nueva lista enlazada
* con una cabeza no nula de largo 0.
*/
Lista* CrearLista() {
    Lista *lista = malloc(sizeof(struct Lista));
    Node *cabeza = malloc(sizeof(struct Node));

    if (!lista) {
        return NULL;
    }
    if (!cabeza) {
        return NULL;
    }

    lista->head = cabeza;
    lista->head->value = 0;

    return lista;
}

/**
* Reads from file and saves every line of the file in
* a node of a linked list.
*/
void CrearTuplas(char filename[], struct Lista* lista) {
    FILE *fp;
    char data[28];

    fp = fopen(filename, "r");

    /*Reads until \n is found and writes in "data"*/
    while (fscanf(fp, "%s", data) != EOF) {
        char *line = malloc(sizeof(char) * 28 + 1);
        strcpy(line, data);
        printf("%s\n", line);
    }
}


int main(int argc, char **argv) {
    Lista *lista = CrearLista();
    CrearTuplas(argv[1], lista);

    /*CrearTuplas(argv[1], lista);*/
    /*ImprimirLista(lista);*/
    /*int *array = KeyArray(argv[2]);*/


    /*LinearSearch(valor a buscar, lista)*/

    return 0;
}