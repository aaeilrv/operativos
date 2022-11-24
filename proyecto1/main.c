/**
 * Valeria Vera
 * 16-11233
 * Sistemas de Operación I
 * 
 * El objetivo del programa es iterar
 * recursivamente en un directorio y obtener
 * la cantidad de archivos (regulares, enlaces simbólicos
 * y directorios) que hay en cada subdirectorio. Así
 * como conocer el tamaño total del directorio y los enlaces
 * fuertes que hay en el mismo.
*/

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "Tuple.h"
#include "Array.h"
#include "Pair.h"
#include "Lista.h"
#include "Node.h"
#include "ListaChar.h"
#include "NodeChar.h"

#include "auxstruct.h"
#include "tuplearray.h"
#include "linkedlist.h"
#include "auxfunctions.h"

#define LEN 10

int main(int argc, char** argv) {
    Lista *inodes_list = CrearLista();
    Array dir_tree;
    char* tree_beggining = beggining(argc, argv);
    FILE* output_file = output(argc, argv);

    initArray(&dir_tree, LEN);

    recursiveVisit(tree_beggining, "", &dir_tree, inodes_list);

    sort(&dir_tree);

    hierarchyTree(&dir_tree, output_file, inodes_list);

    return 0;
}