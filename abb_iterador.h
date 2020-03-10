#include "abb.h"

typedef struct abb_iterador abb_iterador_t;

/*PRE: La funcion debe recibir un puntero a un TDA abb no nulo con sus campos correctamente
 *	   inicializados
 *POST: Se retornara un puntero a un iterador externo de abb, y en caso de error
 *		por falta de memoria o recibir un abb nulo, se retornara NULL.
 */
abb_iterador_t* abb_iterador_crear(abb_t* arbol);

/*PRE: La funcion debe recibir un puntero a un iterador externo de abb no nulo.
 *POST:	Retorna true en caso de que el elemento sobre el cual este parado el iterador tenga 
 *		siguiente, o false en caso contrario. Si se recibe un iterador nulo se retornara false.
 */
bool abb_iterador_tiene_siguiente(abb_iterador_t* iterador);

/*PRE: La funcion debe recibir un puntero a un iterador externo de abb no nulo.
 *POST:	Se retornara un puntero al elemento siguiente al cual este parado el iterador,
 *      y este se avanzara hacia dicho elemento. En caso de no haber siguiente o recibir
 * 		un puntero nulo, se retornara NULL.
 */
void* abb_iterador_siguiente_preorden(abb_iterador_t* iterador);

/*PRE: Debe recibir un puntero a un iterador externo de abb no nulo
 *POST: Se liberara la memoria reservada por el iterador.
 */
void abb_iterador_destruir(abb_iterador_t* iterador);