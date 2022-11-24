/**
 * Valeria Vera
 * 16-11233
 * Sistemas de Operación I
*/

/**
 * Estructura Node, conformada por un par, 
 * un apuntador al siguiente nodo de la lista y al previo,
 * y un entero que expresa si el inodo guardado en este nodo
 * ya existe o no.
 * 
 * Se utiliza en la estructura de listas doblemente enlazadas.
*/
typedef struct Node  {
    struct Pair* data;
	int duplicated;
	struct Node* next;
	struct Node* prev;
}
Node;