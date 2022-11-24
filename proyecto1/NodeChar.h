/*
* CI3825: Sistemas de Operación
* Valeria Vera Herrera
* 16-11233
*/

/*
* Estructura de Nodo la cual contiene una estructura Par,
* un entero "length" que representa el largo de la primera
* cadena de caracteres del par, y dos structuras Node para
* el nodo previo y el siguiente de la lista enlazada.
*/

#define MAX 500

typedef struct NodeChar  {
    char* data;
    int length;
	struct NodeChar* next;
	struct NodeChar* prev;
}
NodeChar;