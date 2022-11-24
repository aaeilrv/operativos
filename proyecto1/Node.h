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
typedef struct Node  {
    struct Pair* data;
	int duplicated;
	struct Node* next;
	struct Node* prev;
}
Node;