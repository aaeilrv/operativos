/**
 * Valeria Vera
 * 16-11233
 * Sistemas de Operación I
 * 
 * -------
*/

#define _DEFAULT_SOURCE /* macro añadido para utilizar lstat*/

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

#define LEN 10
#define INIT 5

/**
 * La función nos permite buscar un inodo en una lista
 * para saber si ya existe en ella.
 * Entrada:
 *      - inode_list: lista donde se busca el inodo.
 *      - inode: valor del inodo a buscar.
 * Salida: Nodo de la lista donde se encuentra el inodo
 *        o NULL si no se encuentra.
*/
Node* searchInode(int inode, Lista* inode_list) {
    Node* temp = inode_list->head;

    while (temp->next != NULL) {
        if (temp->data->inode_number == inode) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

/**
 * Nos permite saber si un archivo es un directorio.
 * Entrada:
 *     - path: ruta del archivo.
 * Salida: 1 si es un directorio, 0 si no lo es.
*/
int is_directory(char* path) {
    struct stat st;
    if (stat(path, &st) != 0) return 0;
   
    return S_ISDIR(st.st_mode);
}

/**
 * Nos permite saber si un archivo es regular.
 * Entrada:
 *    - path: ruta del archivo.
 * Salida: 1 si es un archivo regular, 0 si no lo es.
*/
int is_reg_file(char* path) {
    struct stat st;
    if (stat(path, &st) != 0) return -1;

    return S_ISREG(st.st_mode);
}

/**
 * Nos permite saber si un archivo es un enlace simbólico.
 * Entrada:
 *    - path: ruta del archivo.
 * Salida: 1 si es un enlace simbólico, 0 si no lo es.
*/
int is_symbolic_link(char* path) {
    struct stat st;
    if (stat(path, &st) != 0) return -1;

    return S_ISLNK(st.st_mode);
}

/**
 * Nos permite calcular el tamaño en bytes
 * de un archivo.
 * Entrada:
 *   - path: ruta del archivo.
 * Salida: tamaño en bytes del archivo.
*/
int calc_size(char* path) {
    struct stat st;

    lstat(path, &st);
    return st.st_size;
}

/**
 * Nos permite saber en qué inodo se encuentra
 * un archivo.
 * Entrada:
 *  - path: ruta del archivo.
 * Salida: inodo del archivo.
*/
int inode_number(char* path) {
    struct stat st;  
    if (stat(path, &st) != 0) return -1;

    return st.st_ino;
}

/**
 * Se busca un inodo en la lista con la función
 * searchInode() y en caso de estar ahí, se añade
 * el nombre del archivo a la listaChar de nombres
 * de archivos que se encuentran en ese inodo.
 * 
 * En caso contrario, se crea un nuevo par con el
 * inodo y la listaChar con el nombre del archivo y se
 * calculan los bytes de dicho archivo.
 * 
 * Entrada:
 *  - inode_list: lista de pares inodo-nombres de archivos.
 *  - path: ruta del archivo.
 * 
 * Salida: entero expresando el tamaño en bytes del archivo.
 * en caso de no estar duplicado o cero en caso de estarlo.
*/
int duplicated_inode(Lista* inodes_list, char* path) {
    int inodo = inode_number(path);
    Node* nodo_inodo = searchInode(inodo, inodes_list);

    if (nodo_inodo == NULL) {
        ListaChar* lista = CrearListaChar();
        Pair* pair;
        Node* nodo;
        NodeChar* nodo_char = CrearNodoChar(path);

        InsertarNodoChar(nodo_char, lista);

        pair = createPair(inodo, lista);
        nodo = CrearNodo(pair);
        InsertarNodo(nodo, inodes_list);
        return(calc_size(path));
    } else {
        InsertarNodoChar(CrearNodoChar(path), nodo_inodo->data->dirnames);
        nodo_inodo->duplicated = 1;
    }
    return 0;
}

/**
 * Permite recorrer un directorio recursivamente,
 * viendo los archivos que contiene y sus propiedades.
 * 
 * Entrada:
 * - dirname: ruta del directorio a recorrer.
 * - indent: número de espacios que se van a imprimir.
 * - array: array de tuplas que contiene el nombre de los
 *         directorios, subdirectorios y caracteristicas.
 * - inodes_list: lista de pares inodo-nombres de archivos.
*/
int recursiveVisit(char* dirname, char* indent, Array* array, Lista* inodes_list) {
    DIR* dir = opendir(dirname);
    struct dirent* entry;

    Tuple* in_dir = createTuple();

    int emptyDir = 1;

    if (!dir) return -1;

    while ((entry = readdir(dir))) {
        char *d_name = entry->d_name;

        if (strcmp(d_name, ".") == 0 || strcmp(d_name, "..") == 0) {
            continue;
        } else {
            int bytesPerDisk = 0;

            char* path = malloc(sizeof(char) *               
                (strlen(dirname) + strlen(d_name) + 2));
            
            char* new_indent = malloc(sizeof(char) *
                (strlen(indent) + 4));

            if (!path) {
                printf("Error: No se pudo reservar memoria.\n");
                exit(1);
            }

            if (!new_indent) {
                printf("Error: No se pudo reservar memoria.\n");
                exit(1);
            }

            sprintf(path, "%s/%s", dirname, d_name);
            sprintf(new_indent, "%s    ", indent);

            strcpy(in_dir->dir_name, dirname);
            strcpy(in_dir->indent, new_indent);

            if (is_directory(path)) {
                in_dir->directories++;
                bytesPerDisk += calc_size(path);
                recursiveVisit(path, new_indent, array, inodes_list);
            } else {
                bytesPerDisk += duplicated_inode(inodes_list, path);

                if (is_reg_file(path)) {
                    in_dir->regular_files++;
                } 
                
                if (is_symbolic_link(path)) {
                    in_dir->symbolic_links++;
                }
            }

            in_dir->bytes += bytesPerDisk;

            free(path);
            free(new_indent);

            emptyDir = -1;
        }
    }
    
    entry = readdir(dir);

    if (emptyDir) { /* Agrea nombre de directorio e indentacion de dir. vacio */
        strcpy(in_dir->dir_name, dirname);
        strcpy(in_dir->indent, indent);
    }

    if (closedir(dir) == -1) {
        printf("ERROR: No se pudo cerrar el directorio\n");
        return -1;
    }

    insertArray(array, in_dir);

    return 0;
}

/**
 * Ordena ascendentemente los elementos
 * de un array de tuplas de acuerdo a su
 * nombre.
 * Entrada: array de tuplas.
*/
void sort(Array* array) {
    int i, j;
    Tuple temp;

    for (i = 0; i < array->used; i++) {
        for (j = i + 1; j < array->used; j++) {
            if (strcmp(array->data[i].dir_name, array->data[j].dir_name) > 0) {
                temp = array->data[i];
                array->data[i] = array->data[j];
                array->data[j] = temp;
            }
        }
    }
}

/**
 * Imprime los elementos de un array de tuplas en orden
 * de jerarquia (desde el directorio raiz hasta los subdirectorios).
 * Luego imprime el total de los distintos tipos de archivos, los bytes
 * totales y los enlaces fuertes.
 * 
 * Entrada:
 * - values: array de tuplas.
 * -fp: file pointer al archivo donde se va a imprimir.
 * - inodes_list: lista de pares inodo-nombres de archivos.
*/
void hierarchyTree(Array* values, FILE* fp, Lista* inodes_list) {
    Node* temp = inodes_list->head;
    Tuple* total_tree = createTuple(); /* Guarda la suma total de los datos del árbol*/
    char* root_tree = values->data[0].dir_name;

    int i = 0;
    
    while (i < values->used) {
        fprintf(fp, "%sDirectorio: %s\n", values->data[i].indent,
                values->data[i].dir_name);

        fprintf(fp, "    %sNumero de archivos regulares: %d\n",
                values->data[i].indent, values->data[i].regular_files);

        fprintf(fp, "    %sNumero de archivos enlaces simbolicos: %d\n",
                values->data[i].indent, values->data[i].symbolic_links);

        fprintf(fp, "    %sNumero de directorios: %d\n",
                values->data[i].indent, values->data[i].directories);

        fprintf(fp, "    %sNumero de Bytes en disco: %d\n",
                values->data[i].indent, values->data[i].bytes);

        total_tree->regular_files += values->data[i].regular_files;
        total_tree->directories += values->data[i].directories;
        total_tree->symbolic_links += values->data[i].symbolic_links;
        total_tree->bytes += values->data[i].bytes;

        i++;
    }

    freeArray(values);
    
    fprintf(fp, "\n");
    fprintf(fp, "Los siguientes conjuntos de archivos son enlaces fuertes entre si:\n");

    do{
        if (temp->duplicated == 1) {
            fprintf(fp, "Inodo: %d\n", temp->data->inode_number);
            printListaChar(temp->data->dirnames, fp);
        }
        temp = temp->next;
    } while (temp->next != NULL);

    fprintf(fp, "\n");

    /* Liberar memoria de nodos de ambas listas y listas*/
    /* Liberar memoria de tupla y values */

    fprintf(fp, "Numero total de archivos regulares bajo %s: %d\n",
            root_tree, total_tree->regular_files);

    fprintf(fp, "Numero total de enlaces simbolicos bajo %s: %d\n",
            root_tree, total_tree->symbolic_links);

    fprintf(fp, "Numero total de directorios bajo %s: %d\n",
            root_tree, total_tree->directories);

    fprintf(fp, "Numero total de Bytes en disco: %d\n", total_tree->bytes);

     /*free(total_tree->dir_name);
    free(total_tree->indent);*/
}

/**
 * Lee el argumento de entrada y devuelve el nombre
 * del directorio donde se comenzará la búsqueda o
 * el nombre del directorio actual si no fue especificado
 * un directorio para buscar.
 * 
 * Entrada:
 * - argc: cantidad de argumentos de entrada.
 * - argv: argumentos de entrada.
 * 
 * Salida:
 * puntero hacia el nombre del directorio raiz.
*/
char* beggining(int argc, char** argv) {
    char* tree_beggining = malloc(sizeof(char) * (INIT + 1) + 1);
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
        tree_beggining = realloc(tree_beggining,
                sizeof(char) * (strlen(".") + 1));

        if (!tree_beggining) {
            printf("Error: No se pudo reservar más memoria.\n");
            exit(1);
        }

        strcpy(tree_beggining, ".");
    }

    return tree_beggining;
}

/**
 * Devuelve un file pointer hacia el archivo
 * donde se imprimirán los resultados finales o
 * hacia la salida estándar si no se especificó
 * un archivo de salida.
 * 
 * Entrada:
 * - argc: cantidad de argumentos de entrada.
 * - argv: argumentos de entrada.
 * 
 * Salida:
 * puntero hacia el archivo de salida.
*/
FILE* output(int argc, char** argv) {
    FILE *fp;
    int found_f = 0;
    int i = 0;

    if (argc == 1) { /* En caso de que no existan flags en la línea de comando */
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