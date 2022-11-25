/**
 * Valeria Vera
 * 16-11233
 * Sistemas de Operación I
 * 
 * Funciones para la creación, inserción e impresión
 * de listas de pares y listas de caracteres, así
 * como la creación de nodos de pares y nodos de caracteres.
*/

#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdio.h>

ListaChar* CrearListaChar();
NodeChar* CrearNodoChar(char* info);
void InsertarNodoChar(NodeChar* newNode, ListaChar* lista);
void printListaChar(ListaChar* lista, FILE* fp);
void freeCharList(ListaChar* list);

Lista* CrearLista();
Node* CrearNodo(Pair* info);
void InsertarNodo(Node* newNode, Lista* lista);
void printList(Lista* lista, FILE* fp);
void freeList(Lista* list);

#endif