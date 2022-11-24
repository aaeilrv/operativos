/**
* CI3825: Sistemas de Operación
* Valeria Vera Herrera
* 16-11233
*
* EDITAR 
*/

#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdio.h>

ListaChar* CrearListaChar();
NodeChar* CrearNodoChar(char* info);
void InsertarNodoChar(NodeChar* newNode, ListaChar* lista);
void printListaChar(ListaChar* lista);

Lista* CrearLista();
Node* CrearNodo(Pair* info);
void InsertarNodo(Node* newNode, Lista* lista);
void printList(Lista* lista);

#endif