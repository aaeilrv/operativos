/**
* CI3825: Sistemas de Operación
* Valeria Vera Herrera
* 16-11233
*
* Estructura "Array" utilizada para la creación de un arreglo dinámico.
*/

typedef struct Array {
    int size;
    int used;
    struct Tuple* data;
}
Array;