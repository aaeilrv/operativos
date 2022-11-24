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

void InsertarNodoChar(NodeChar* newNode, ListaChar* lista) {
    lista->head->prev = newNode;
	newNode->next = lista->head;
	lista->head = newNode;
}

void printListaChar(ListaChar* lista) {
    NodeChar *temp = lista->head;

    if (temp != NULL) {
        do {
            printf("    %s\n",temp->data);
            temp = temp->next;
        }while(temp->next != NULL);
        printf("\n");
    }
}

/* Lista de pares */
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

void InsertarNodo(Node* newNode, Lista* lista) {
    lista->head->prev = newNode;
	newNode->next = lista->head; 
	lista->head = newNode;
}

void printList(Lista* lista) {
	Node *temp = lista->head;

	do {
        printf("Inodo: %d\n",temp->data->inode_number);
        printListaChar(temp->data->dirnames);
		temp = temp->next;
	}while(temp->next != NULL);
}