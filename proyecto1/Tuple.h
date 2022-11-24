/**
* CI3825: Sistemas de Operación
* Valeria Vera Herrera
* 16-11233
*
* Estructure "Tuple".
*/

typedef struct Tuple {
    char* dir_name;
    char* indent;
    int regular_files;
    int directories;
    int symbolic_links;
    int bytes;
    struct Pair* pair;
}
Tuple;