/**
 * Valeria Vera
 * 16-11233
 * Sistemas de Operación I
 * 
 * Estructura Tuple, conformada por el nombre
 * de un directorio, el valor de su indentación
 * al momento de imprimir, su número de bytes y
 * los tipos de archivo que tiene.
 * 
 * Se utiliza dentro de las estructuras de arreglos
 * de tuplas.
*/

typedef struct Tuple {
    char* dir_name;
    int indent;
    int regular_files;
    int directories;
    int symbolic_links;
    int bytes;
}
Tuple;