/**
 * CI3825: Sistemas de Operación
 * Valeria Vera
 * 16-11233
 * 
 * - Array.h: Estructura de arreglo dinámico.
 * 
 * - Tuple.h: Estructura de tupla.
 * 
 * - arrayfunc.h: Funciones necesarias para el manejo de arreglos dinámicos.
 * 
 * - records.h: Funciones auxiliares para la lectura de datos,
 *   creación de tuplas y guardado de ellas en arreglos dinámicos.
 * 
 * - order.h: Funciones utilizadas para organizar
 *   ascendentemente el arreglo dinámico de claves y posiciones.
 * 
 * - searchalg.h: Algoritmos de búsqueda.
 * 
 * - results.h: Funciones utilizadas para captar y
 *   guardar los resultados de las búsquedas en un archivo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Array.h"
#include "Tuple.h"

#include "arrayfunc.h"
#include "records.h"
#include "order.h"
#include "searchalg.h"
#include "results.h"

/**
 * Crea dos arreglos dinámicos, los llena
 * y comienza la búsqueda de las claves.
 * Después de todo el proceso, libera el espacio
 * de memoria utilizado.
*/
int main(int argc, char **argv) {
    Array a;
    Array b;
    char* type = argv[1];

    initArray(&a, 5);
    initArray(&b, 5);

    createRecords(argv[2], &a, &b, type); 
    searchKeys(argv[3], argv[4], argv[5], &a, &b, type);

    freeArray(&a);

    return 0;
}