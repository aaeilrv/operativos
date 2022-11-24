/**
 * Valeria Vera
 * 16-11233
 * Sistemas de Operación I
 * 
 * Funciones para la creación, inserción e impresión
 * de listas de pares y listas de caracteres, así
 * como la creación de nodos de pares y nodos de caracteres.
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
#include "NodeChar.h"
#include "ListaChar.h"

/* Lista de caracteres */

/**
 * Nos permite crear una lista de caracteres,
 * esta se inicializa creando un nodo cabeza
 * el cual no contiene ningún elemento.
*/
ListaChar* CrearListaChar() {
    ListaChar *lista = malloc(sizeof(struct ListaChar));
    NodeChar *cabeza = malloc(sizeof(struct NodeChar));

    if (!lista) {
        return NULL;
    }
    if (!cabeza) {
        return NULL;
    }

    lista->head = cabeza;
    lista->head->next = NULL;

    return lista;
}

/**
 * Nos permite crear un NodoChar.
 * 
 * Entrada:
 *  - path: un arreglo de caracteres que
 * representa el nombre del archivo a guardar.
*/
NodeChar* CrearNodoChar(char* path) {
    NodeChar *newNode = malloc(sizeof(struct NodeChar));
    char* nombreStr = malloc(sizeof(char) * strlen(path) + 1);

    if (!newNode) {
        printf("Error: No se pudo reservar memoria\n");
        exit(1);
    }

    if (!nombreStr) {
        printf("Error: No se pudo reservar memoria\n");
        exit(1);
    }

    strcpy(nombreStr, path);

    newNode->data = nombreStr;

	newNode->prev = NULL;
	newNode->next = NULL;

    return newNode;
}

/**
 * Nos permite insertar un NodoChar en una ListaChar.
 * La inserción de los nodos se realiza a través de
 * la cabeza de la lista.
 * 
 * Entrada:
 * - newNode: nodo a insertar.
 * - lista: lista en la que se insertará el nodo.
*/
void InsertarNodoChar(NodeChar* newNode, ListaChar* lista) {
    lista->head->prev = newNode;
	newNode->next = lista->head;
	lista->head = newNode;
}

/**
 * Nos permite imprimir una lista de caracteres.
 * 
 * Entrada:
 * - lista: lista a imprimir.
 * - fp: archivo en el que se imprimirá la lista.
 * 
*/
void printListaChar(ListaChar* lista, FILE* fp) {
    NodeChar *temp = lista->head;

    if (temp != NULL) {
        do {
            fprintf(fp, "    %s\n",temp->data);
            temp = temp->next;
        }while(temp->next != NULL);
        printf("\n");
    }
}

/* Lista de pares */

/**
 * Nos permite crear una lista de pares,
 * esta se inicializa creando un nodo cabeza
 * el cual no contiene ningún elemento.
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
    lista->head->duplicated = 0;
    lista->head->next = NULL;

    return lista;
}

/**
 * Nos permite crear un nodo de pares.
 * 
 * Entrada:
 *  - info: par a guardar en el nodo.
*/
Node* CrearNodo(Pair* info) {
    Node *newNode = malloc(sizeof(struct Node));

    if (!newNode) {
        printf("Error: No se pudo reservar memoria\n");
        exit(1);
    }

    newNode->data = info;
    newNode->data->inode_number = info->inode_number;
    newNode->data->dirnames = info->dirnames;
    newNode->duplicated = 0;
	newNode->prev = NULL;
	newNode->next = NULL;

    return newNode;
}

/**
 * Nos permite insertar un nodo de pares
 * en una lista de pares. La inserción se
 * hace a través de la cabeza de la lista.
 * 
 * Entrada:
 * - newNode: nodo a insertar.
 * - lista: lista en la que se insertará el nodo.
*/
void InsertarNodo(Node* newNode, Lista* lista) {
    lista->head->prev = newNode;
	newNode->next = lista->head; 
	lista->head = newNode;
}

/**
 * Nos permite imprimir una lista de pares.
 * 
 * Entrada:
 * - lista: lista a imprimir.
 * - fp: archivo en el que se imprimirá la lista.
*/
void printList(Lista* lista, FILE* fp) {
	Node *temp = lista->head;

	do {
        fprintf(fp, "Inodo: %d\n",temp->data->inode_number);
        printListaChar(temp->data->dirnames, fp);
		temp = temp->next;
	}while(temp->next != NULL);
}