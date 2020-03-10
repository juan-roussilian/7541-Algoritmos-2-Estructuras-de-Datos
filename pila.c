#include "pila.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR -1
#define EXITO 0
#define PORCENTAJE_MAXIMO 75
#define PORCENTAJE_MINIMO 25
#define PROPORCION_REDIMENSION 2
#define TAMANIO_INICIAL 1
#define VACIO 0

/*PRE: la funcion debe recibir dos enteros inicializados que representen el	
 * tope de elementos de la pila (o la cantidad) y el tamanio actual de la pila
 *POST: La funcion devolvera el porcentaje que esta lleno de la pila
 */
int pila_porcentaje (int tope, int tamanio){

	if (tamanio == VACIO){
		return ERROR;
	}

	int porcentaje = ((tope * 100)/tamanio);

	return porcentaje;
}

/*PRE: La funcion debe recibir una variable del tipo pila_t* (pila_t pointer)
 *POST: La funcion reducira el tamanio de la pila a la mitad si es que se dispone de la
 * suficiente memoria. En caso contrario, o en caso de que la pila sea NULL, se devolvera  
 * -1
 */

int reducir_pila (pila_t* pila){

	if (pila == NULL){
		return 	ERROR;
	}
	
	void* ptr_aux = realloc(pila->elementos,(sizeof(void*)  * (unsigned)(pila->tamanio)/PROPORCION_REDIMENSION ) ) ;
	
	if (ptr_aux == NULL){
		return ERROR;
	}			
	else {
		pila->elementos = ptr_aux;
		pila->tamanio = (int) (pila->tamanio/PROPORCION_REDIMENSION);
		return EXITO;
	}
}

/*PRE: La funcion debe recibir una variable del tipo pila_t* (pila_t pointer)
 *POST: La funcion ampliara el tamanio de la pila al doble si es que se dispone de la
 * suficiente memoria. En caso contrario, o en caso de que la pila sea NULL, se devolvera  
 * -1
 */

int ampliar_pila (pila_t* pila){
	
	void* ptr_aux = realloc(pila->elementos,(sizeof(void*)  * (unsigned)(pila->tamanio * PROPORCION_REDIMENSION)) ) ;
	
	if (ptr_aux == NULL){
		return ERROR;
	}			
	else {
		pila->elementos = ptr_aux;
		pila->tamanio = (int)(PROPORCION_REDIMENSION * pila->tamanio);
		return EXITO;
	}
}

pila_t* pila_crear(){
	
	
	pila_t* pila;

	pila = malloc(sizeof(pila_t));

	if (pila == NULL) {
		return NULL;
	}

	else {
		pila->tope = VACIO;
		pila->tamanio = TAMANIO_INICIAL;
		pila->elementos = NULL;
	}

	pila->elementos = malloc (sizeof(void*));

	if (pila->elementos == NULL){ 
		free(pila);
		return NULL;
	}
	return pila;	
}

int pila_apilar(pila_t* pila, void* elemento){
	
	int porcentaje_lleno;
	
	if (pila == NULL ){
		return ERROR;
	}

	pila->elementos[pila->tope] = elemento;
	pila->tope++;
	porcentaje_lleno = pila_porcentaje(pila->tope, pila->tamanio);

	if (porcentaje_lleno == ERROR){
		return ERROR;
	}
	
	else if  (porcentaje_lleno >= PORCENTAJE_MAXIMO){

		if (ampliar_pila(pila) == ERROR){
			return ERROR;
		}
	}
	return EXITO;
}

int pila_desapilar(pila_t* pila){
	
	int porcentaje_lleno;

	if (pila == NULL){
		return ERROR;
	}
	if (pila_vacia(pila)){
		return ERROR;
	}
 	
 	pila->tope--;
 	porcentaje_lleno = pila_porcentaje(pila->tope, pila->tamanio);
 	
 	if (porcentaje_lleno == ERROR){
		return ERROR;
	}
 	else if (porcentaje_lleno <= PORCENTAJE_MINIMO){

 		if (reducir_pila(pila) == ERROR){
			return ERROR;
		}
 	}
 	return EXITO;
}

bool pila_vacia(pila_t* pila){
	
	if (pila == NULL){
		return true;
	}
	if (pila->tope == VACIO){
		return true;
	}
	else{
		return false;
	}
}


int pila_cantidad(pila_t* pila){
	if (pila ==  NULL){
		return EXITO;
	}

	else{
		return(pila->tope);
	}
}

void* pila_tope(pila_t* pila){
	
	if (pila == NULL){
		return NULL;
	}
	if (pila_vacia(pila)){
		return NULL;
	}
	else{
		return pila->elementos[pila->tope-1];
	}
}

void pila_destruir(pila_t* pila){
	
	if (pila == NULL){
		return;
	}	
	
	free (pila->elementos);
	free (pila); 
}

