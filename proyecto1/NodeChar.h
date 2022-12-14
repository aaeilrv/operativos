/**
 * Valeria Vera
 * 16-11233
 * Sistemas de Operación I
*/

/**
 * Estructura NodeChar, conformada por un apuntador a data, 
 * un apuntador al siguiente nodo de la lista y un entero
 * que expresa si el inodo guardado en este nodo
 * ya existe o no.
 * 
 * Se utiliza en la estructura de listas enlazadas de caracteres
 * (listChar).
*/
typedef struct NodeChar {
    char* data;
	struct NodeChar* next;
}
NodeChar;