#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "Tuple.h"
#include "Array.h"
#include "Pair.h"

#define LEN 10
#define INIT 5

/**     ESTRUCTURAS     **/
Tuple* createTuple() {
    struct Tuple* tuple = malloc(sizeof(struct Tuple));

    if (!tuple) {
        printf("Error: No se pudo reservar memoria para la tupla");
        exit(1);
    }

    tuple->regular_files = 0;
    tuple->directories = 0;
    tuple->symbolic_links = 0;
    tuple->bytes = 0;

    return tuple;
}

Pair* createPair(char* dir_name, char* ind) {
    struct Pair* pair = malloc(sizeof(struct Pair));

    if (!pair) {
        printf("Error: No se pudo reservar memoria para el par");
        exit(1);
    }

    strcpy(pair->dir_name, dir_name);
    strcpy(pair->indent, ind);

    return pair;
}

/**     ARREGLO DE TUPLAS    **/
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
void insertArray(Array* array, struct Tuple* value) {
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

/**     TIPOS DE ARCHIVO    **/
/*
Entrada: apuntador a char: path
Salida: entero que representa si el archivo es un
        directorio o no.
    0 = no es directorio.
    dist. 0 = es directorio.
*/
int is_directory(char* path) {
    struct stat st;
    if (stat(path, &st) != 0) return 0;
   
    return S_ISDIR(st.st_mode);
}

/*
Entrada: apuntador a char: path
Salida: entero que representa si el archivo es un
        archivo regular o no.
    0 = no es archivo regular.
    dist. 0 = es un archivo regular.
*/
int is_reg_file(char* path) {
    struct stat st;
    if (stat(path, &st) != 0) return -1;

    return S_ISREG(st.st_mode);
}

int is_symbolic_link(char* path) {
    struct stat st;
    if (stat(path, &st) != 0) return -1;

    return S_ISLNK(st.st_mode);
}

/**     RECORRIDO RECURSIVO     **/
int recursiveVisit(char* dirname, char* indent, Array* array) {
    DIR* dir = opendir(dirname);
    struct dirent* entry;

    Tuple* in_dir = createTuple();
    int emptyDir = 1;

    if (!dir) return -1;

    while ((entry = readdir(dir))) {
        char *d_name = entry->d_name;
        Pair* pair;

        if (strcmp(d_name, ".") == 0 || strcmp(d_name, "..") == 0) {
            continue;
        } else {
            char* path = malloc(sizeof(char) *               
                (strlen(dirname) + strlen(d_name) + 2));  /* Obtengo espacio para nuevo path */
            
            char* new_indent = malloc(sizeof(char) *
                (strlen(indent) + 4));  /* Obtengo espacio para el indentado */

            if (!path) {
                printf("Error: No se pudo reservar memoria para el path");
                exit(1);
            }

            if (!new_indent) {
                printf("Error: No se pudo reservar memoria para el indentado");
                exit(1);
            }

            sprintf(path, "%s/%s", dirname, d_name);
            sprintf(new_indent, "%s    ", indent);

            pair = createPair(dirname, new_indent);
            in_dir->pair = pair;

            if (is_directory(path)) {
                in_dir->directories++;
                recursiveVisit(path, new_indent, array);

            } else {
                if (is_reg_file(path)) {
                    in_dir->regular_files++;
                } 
                
                if (is_symbolic_link(path)) {
                    in_dir->symbolic_links++;
                }
            }

            free(path);
            free(new_indent);

            emptyDir = -1;
        }
    }
    
    entry = readdir(dir);

    if (emptyDir) { /* Crea par para los directorios vacíos */
        Pair* pair = createPair(dirname, indent);
        in_dir->pair = pair;
    }

    if (closedir(dir) == -1) {
        printf("ERROR: No se pudo cerrar el directorio\n");
        return -1;
    }

    insertArray(array, in_dir);

    return 0;
}

/**     ORDENAMIENTO     **/
void sort(Array* array) {
    int i, j;
    Tuple temp;

    for (i = 0; i < array->used; i++) {
        for (j = i + 1; j < array->used; j++) {
            if (strcmp(array->data[i].pair->dir_name, array->data[j].pair->dir_name) > 0) {
                temp = array->data[i];
                array->data[i] = array->data[j];
                array->data[j] = temp;
            }
        }
    }
}

/**     IMPRESION DE ARBOL     **/
void hierarchyTree(Array* values, FILE* fp) {

    Tuple* total_tree = createTuple(); /* Guarda la suma total de los datos del árbol*/

    int i = 0;
    
    while (i < values->used) {
        fprintf(fp, "%sDirectorio: %s\n", values->data[i].pair->indent,
                values->data[i].pair->dir_name);

        fprintf(fp, "    %sNumero de archivos regulares: %d\n",
                values->data[i].pair->indent, values->data[i].regular_files);

        fprintf(fp, "    %sNumero de archivos enlaces simbolicos: %d\n",
                values->data[i].pair->indent, values->data[i].symbolic_links);

        fprintf(fp, "    %sNumero de directorios: %d\n",
                values->data[i].pair->indent, values->data[i].directories);

        /*fprintf(fp, "    %sNumero de Bytes en disco: TO DO\n",
                values->data[i].pair->indent);*/

        total_tree->regular_files += values->data[i].regular_files;
        total_tree->directories += values->data[i].directories;

        i++;
    }
    
    /*fprintf(fp, "\n");
    fprintf(fp, "Los siguientes conjuntos de archivos son
            enlaces fuertes entre si: TO DO\n");*/

    fprintf(fp, "\n");

    fprintf(fp, "Numero total de archivos regulares bajo %s: %d\n",
            values->data[0].pair->dir_name, total_tree->regular_files);

    /*fprintf(fp, "Numero total de enlaces simbolicos bajo %s: TO DO\n",
            values->data[0].dir_name);*/

    fprintf(fp, "Numero total de directorios bajo %s: %d\n",
            values->data[0].pair->dir_name, total_tree->directories);

    /*fprintf(fp, "Numero total de Bytes en disco: TO DO bytes\n");*/
}

/**     OBTENCIÓN DE PARAMETROS     **/
char* beggining(int argc, char** argv) {
    char* tree_beggining = malloc(sizeof(char) * (INIT + 1));
    int found_d = 0;
    int i = 0;

    if (argc == 1) {
        strcpy(tree_beggining, ".");
    } else {
        while (i < argc) {
            if (strcmp(argv[i], "-d") == 0) {
                tree_beggining = realloc(tree_beggining,
                    sizeof(char) * (strlen(argv[i + 1]) + 1));

                if (!tree_beggining) {
                    printf("Error: No se pudo reservar más memoria.\n");
                    exit(1);
                }   

                strcpy(tree_beggining, argv[i + 1]);
                found_d = 1;
            }
            i++;
        }
    }

    if (!found_d) {
        tree_beggining = realloc(tree_beggining, sizeof(char) * (strlen(".") + 1));

        if (!tree_beggining) {
            printf("Error: No se pudo reservar más memoria.\n");
            exit(1);
        }

        strcpy(tree_beggining, ".");
    }

    return tree_beggining;
}

FILE* output(int argc, char** argv) {
    FILE *fp;
    int found_f = 0;
    int i = 0;

    if (argc == 1) {    /* En caso de que no existan flags en la línea de comando */
        fp = stdout;

        if (!fp) {
            printf("Error al imprimir en terminal\n");
            exit(1);
        }
    } else {    /* En caso de tener flags en la línea de comando */
        while (i < argc) {
            if (strcmp(argv[i], "-f") == 0) {
                fp = fopen(argv[i + 1], "w+");

                if (!fp) {
                    printf("Error al crear el archivo %s\n", argv[i + 1]);
                    exit(1);
                }

                found_f = 1;

                return fp;
            }
            i++;
        }
    }

    if (!found_f) { /* En caso de que -f no estè en */
        fp = stdout;

        if (!fp) {
            printf("Error al imprimir en terminal\n");
            exit(1);
        }

        return fp;
    }
    return fp;
}

int main(int argc, char** argv) {
    Array dir_tree;
    char* tree_beggining = beggining(argc, argv);
    FILE* output_file = output(argc, argv);

    initArray(&dir_tree, LEN);

    recursiveVisit(tree_beggining, "", &dir_tree);

    sort(&dir_tree);

    hierarchyTree(&dir_tree, output_file);

    return 0;
}