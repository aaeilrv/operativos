/**
 * Valeria Vera
 * 16-11233
 * Sistemas de Operación I
 * 
 * Pair: estructura contenida en l
 * estructura lista, formada por un entero
 * y una listaChar; representando cada uno
 * el número de inodo y los nombres de los archivos
 * en ese inodo respectivamente.
*/

typedef struct Pair {
    int inode_number;
    struct ListaChar *dirnames;
}
Pair;