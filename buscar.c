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

/*
* Dado un string alfanumérico, la función
* devuelve el último valor numérico que consigue.
* Entrada: String que contiene el campo
* "clave" de la tupla.
* Salida: Entero
*/
int becomeNumber(char *value) {
    int key;
    char *str = value, *p = str;

    while (*p) {
        if ( isdigit(*p) || ( (*p=='-'||*p=='+') && isdigit(*(p+1)) )) {
            key = strtol(p, &p, 10);
        } else {
            p++;
        }
    }

    return key;
}

/*
* Entrada: Pointer a tupla que estará contenida en el nodo.
* Retorno: Pointer a nodo que contiene la tupla de entrada,
* largo del tamaño de la primera cadena de caracteres
* de la tupla y con Pointeres nulos hacia el previo y
* siguiente nodo.
*/
Node* CrearNodo(struct Tupla* info) {
    Node *newNode = malloc(sizeof(struct Node));
    int key = becomeNumber(info->clave);

    if (!newNode) {
        return NULL;
    }

    newNode->data = info;
    newNode->data->clave = info->clave;
    newNode->data->nombre = info->nombre;
    newNode->data->edad = info->edad;

    newNode->value = key;

	newNode->prev = NULL;
	newNode->next = NULL;

    return newNode;
}

/*
* Entrada: Pointer a lista enlazada y a nodo a insertar en la misma.
* Los nodos son agregados utilizando ordenamiento lineal
* ascendente dependiendo del elemento "value" de cada uno.
*/
void InsertarNodo(struct Node* newNode, struct Lista* lista) {    

    if (lista->head->value == 0 || newNode->value <= lista->head->value) {
        lista->head->prev = newNode;
	    newNode->next = lista->head; 
	    lista->head = newNode;
    } else {
        if (newNode->value > lista->head->value) {
            struct Node *temp = lista->head;

            while (temp->next != NULL && temp->next->value <= newNode->value) {
                temp = temp->next;
            }

            newNode->next = temp->next;
            newNode->prev = temp;
            if (temp->next != NULL) {
                temp->next->prev = newNode;
            }
            temp->next = newNode;
        }
    }
}

/*
* Entrada: Apuntador a cadena de caracteres que
* representa el nombre del archivo a ser abierto.
* Retorno: Entero con la cantidad de "\n" que existen
* en el archivo abierto.
*/
int NumColon(const char *filename) {
    FILE *fp = fopen(filename, "r");
    int count = 1;
    int colon;

    if (!fp) {
        printf("El archivo no puede ser abierto.\n");
        return -1;
    }

    while ((colon = getc(fp)) != EOF) {
        if (colon == '\n') {
            count++;
        }
    }

    fclose(fp);

    return count;
}

/*
* Entrada: cadena de caracteres con el nombre del
* archivo a ser abierto.
* Retorno: Pointer a cadena de caracteres en la que
* está contenida el texto original del archivo
*/
char* ArchivoAString(char filename[]) {
    FILE *fp = fopen(filename, "r");

    char *buffer = 0;
    long length;

    if (!fp) {
        printf("El archivo no puede ser abierto.\n");
        exit(1);
    } else {
        /* Se ve la cantidad de caracteres
        * del archivo a través de*/
        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        /* Retonar un string vacio en
        * caso que el archivo esté vacío. */
        if (length == 0) {
            buffer = "";
            return buffer;
        }

        buffer = malloc(length);

        if (!buffer) {
            return NULL;
        }

        fread(buffer, 1, length, fp);

        fclose(fp);
    }
    return buffer;
}

/*
* Entrada: Pointer a dos cadenas de caracteres.
* Retorno: Pointer a nueva tupla.
*/
Tupla* nueva_tupla(char *key, char *name, char *age) {
    Tupla *newTuple = malloc(sizeof(struct Tupla));
    if (!newTuple) {
        return NULL;
    }

    newTuple->clave = key;
    newTuple->nombre = name;
    newTuple->edad = age;

    return newTuple;
}


char* cutLine(char *file, int i, int n) {
    char *str = malloc((n + 1) * sizeof(char));

    strncpy(str, &file[i], n);    
    str[n] = 0;

    if (!str) {
        exit(1);
    }
    
    return str;
}

/*
* Dado un archivo con tres campos, (clave, nombre, edad)
* la función traversa todas las
* líneas del archivo, crea tuplas con los datos
* encontrados y las agrega a una lista enlazada.
*
* Entrada: Cadena de caracteres que representa el
* nombre del archivo a ser abierto; apuntador a lista
* enlazada
*/
void CrearTuplas(char filename[], struct Lista* lista) {
    char *fp = ArchivoAString(filename);
    int count = NumColon(filename);

    int i = 0;

    char* linea = strtok(fp, "\n");

    Tupla *tuple;
    Node *nodo;

    /* En caso de tener un archivo vacio,
    * se crea un nodo sin valores ("", "", ""),
    * como nodo único de la lista. */
    if (count == 0) {
        tuple = nueva_tupla("", "", "");
        nodo = CrearNodo(tuple);
        InsertarNodo(nodo, lista);
        return;
    }

    while(i != count) {
        char* key = cutLine(linea, 0, 6);
        char* name = cutLine(linea, 6, 20);
        char* age = cutLine(linea, 26, 2);

        tuple = nueva_tupla(key, name, age);
        nodo = CrearNodo(tuple);
        InsertarNodo(nodo, lista);

        linea = strtok(NULL, "\n");

        i++;
    }
}

/*
* Entrada: Pointer a lista enlazada
*/
void ImprimirLista(struct Lista* lista) {
	Node *temp = lista->head;

	do {
		printf("<%s,%s,%s>\n",
            temp->data->clave,
            temp->data->nombre,
            temp->data->edad);
		temp = temp->next;
	}while(temp->next != NULL);

    /*while(temp->next != NULL) {
        printf("<%s,%s,%s>\n",
            temp->data->clave,
            temp->data->nombre,
            temp->data->edad);
		temp = temp->next;
    }*/

	printf("\n");
}

int main(int argc, char **argv) {
    Lista *lista = CrearLista();

    CrearTuplas(argv[1], lista);
    ImprimirLista(lista);

    return 0;
}