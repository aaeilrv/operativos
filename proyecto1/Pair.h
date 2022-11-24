/**
* CI3825: Sistemas de Operación
* Valeria Vera Herrera
* 16-11233
*
* Estructure "Pair". Es el tipo de estructura del cual
* están hechos los arreglos dinámicos.
*/

#define MAX 500

typedef struct Pair {
    int inode_number;
    struct ListaChar *dirnames;
    /*char dirname[MAX];*/
}
Pair;