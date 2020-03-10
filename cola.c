#include "cola.h"
#include <stdio.h>
#include <stdlib.h>

#define EXITO 0
#define ERROR -1

cola_t* cola_crear(){
	
	cola_t* cola = malloc (sizeof(cola_t));

	if (cola == NULL)
		return NULL;
	
	
	else{
		cola->nodo_fin = NULL;
		cola->nodo_inicio = NULL;
		cola->cantidad = 0;
		return cola;
	}
}

/*PRE: La funcion debe recibir un puntero al tipo de dato cola_t, no nulo y otro puntero
 *	al tipo de dato nodo_t, tampoco nulo.
 *
 *POST: La funcion insertara dicho nodo, el cual es el primero en la estructura cola, posicionandolo 
 *	tanto al final como al inicio de la misma.
 */

void insertar_primer_nodo(cola_t* cola, nodo_t* nodo){

	cola->nodo_inicio = nodo;
	cola->nodo_fin = nodo;
	nodo->siguiente = NULL;
}

/*PRE: La funcion debe recibir un puntero al tipo de dato cola_t, no nulo y otro puntero
 *	al tipo de dato nodo_t, tampoco nulo.
 *
 *POST: La funcion encolara al nodo posicionandolo al final de la cola.
 *
 */

void insertar_nodo(cola_t* cola, nodo_t* nodo){
	cola->nodo_fin->siguiente = nodo;
	cola->nodo_fin = nodo;
	nodo->siguiente = NULL;
}

int cola_encolar(cola_t* cola, void* elemento){
	
	if (cola == NULL)
		return ERROR;

	nodo_t* nodo = malloc(sizeof(nodo_t));

	if (nodo == NULL)
		return ERROR;
	
	nodo->elemento = elemento;
		
	if (cola->cantidad == 0)
		insertar_primer_nodo (cola, nodo);
	else
		insertar_nodo (cola, nodo);

	cola->cantidad++;
	return EXITO;
}

/*PRE: La funcion debe recibir un puntero al tipo de dato cola_t.
 *
 *POST: Se desencolara un elemento/ nodo de la cola, eliminando
 *	el primero en la estructura, y posicionando la referencia del primero en
 *  el nodo que le sigue.
 */

int desencolar_nodo (cola_t* cola){
	
	if (cola->nodo_inicio == NULL)
		return ERROR;

	void* ptr_aux;

	ptr_aux = cola->nodo_inicio;
	cola->nodo_inicio = cola->nodo_inicio->siguiente;
	free(ptr_aux);
	return EXITO;
}

 int cola_desencolar(cola_t* cola){
 	
 	if(cola == NULL)
		return ERROR;
	
	if(cola_cantidad(cola) == 0)
		return ERROR;
	
	else if(desencolar_nodo (cola) == 0 ){
		cola->cantidad--;
		return EXITO;
	}
	else 
		return ERROR; 	
}

bool cola_vacia(cola_t* cola){
	
	if (cola == NULL)
		return true;
	
	if (cola->cantidad == 0)
		return true;
	
	else 
		return false;
    
}

int cola_cantidad(cola_t* cola){
	
	return (cola? cola->cantidad : 0 );
}


void* cola_primero(cola_t* cola){

	if (cola == NULL)
		return cola;
	if (cola_vacia (cola))
		return NULL;
	
	return cola->nodo_inicio->elemento;
} 

void cola_destruir(cola_t* cola){
	
	if (cola == NULL)
		return;	

	while(!cola_vacia(cola)) {
		cola_desencolar(cola);
	}
	free (cola);
} 