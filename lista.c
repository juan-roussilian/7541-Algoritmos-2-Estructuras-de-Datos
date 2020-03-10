#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define EXITO 0
#define LISTA_INICIAL 1

typedef struct nodo{
	void* elemento;
	struct nodo* siguiente;
} nodo_t;

struct lista{
	nodo_t* nodo_inicio;
	nodo_t* nodo_fin;
	size_t cantidad;
};

struct lista_iterador{
	lista_t* lista;
	nodo_t* nodo_actual;
};

/*PRE: La funcion debe recibir un puntero a un elemento de cualquier tipo de dato posible
 *	   (El puntero NULL tambien es aceptado)
 *POST: La funcion retornara un puntero a una variable del tipo de dato nodo_t, su campo "elemento"
 *     inicializado con el puntero recibido, y su campo "siguiente" en NULL, y lo retornara
 */
nodo_t* crear_nodo (void* elemento);
	
/*PRE: La funcion debe recibir un puntero a un tipo de dato lista_t y un puntero a un tipo de 
 *	   dato nodo_t, ambos inicializados y no nulos	
 *POST: Se insertara el puntero a nodo recibido al final de la lista recibida
 */
void insertar_nodo(lista_t* lista, nodo_t* nodo);

/*PRE: La funcion recibe un puntero a un tipo de dato lista_t, el cual debe no ser nulo
 *	   y un size_t representando una posicion en la lista, siendo 0 la primer posicion	
 *POST: La funcion retornara un puntero a la vairable nodo_t que se encuentre en la posicion de la lista
 *		recibida como parametro.
 */
nodo_t* obtener_nodo_posicion(lista_t* lista, size_t posicion);


lista_t* lista_crear(){
		
	lista_t* lista = calloc(LISTA_INICIAL, sizeof(lista_t));
	return lista;
}

int lista_insertar(lista_t* lista, void* elemento){
	
	if(!lista)
		return ERROR;
	
	nodo_t* nodo = crear_nodo(elemento);

	if(!nodo)
		return ERROR;
	
	insertar_nodo(lista, nodo);
	
	lista->cantidad++;
	return EXITO;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	
	if (!lista)
		return ERROR;

	if(posicion > lista->cantidad-1)
		return (lista_insertar(lista, elemento));
	else{

		nodo_t* nodo_insertar = crear_nodo(elemento);
	
		if(!nodo_insertar)
			return ERROR;

		if(lista_vacia(lista))
			insertar_nodo(lista,nodo_insertar);
		else{
			if(posicion >0){
				nodo_t* nodo_aux = obtener_nodo_posicion(lista,(posicion-1));
				nodo_insertar->siguiente = nodo_aux->siguiente;
				nodo_aux->siguiente = nodo_insertar;
			}
			else{
				nodo_insertar->siguiente = lista->nodo_inicio;
				lista->nodo_inicio = nodo_insertar;
			}
		}
		lista->cantidad++;
		return EXITO;
	}	
}

int lista_borrar(lista_t* lista){
	
	if (!lista)
		return ERROR;
	if(lista_vacia(lista))
		return ERROR;
	
	nodo_t* nodo_aux = lista->nodo_fin;
	lista->cantidad--;
	
	if (lista->cantidad > 0){
		nodo_t* nodo_aux = obtener_nodo_posicion(lista, (lista->cantidad-1));
		nodo_aux->siguiente = NULL;
		lista->nodo_fin = nodo_aux;
	}
	else{
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
	}
	free(nodo_aux);
	return EXITO;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	
	if (!lista)
		return ERROR;
	if(lista_vacia(lista))
		return ERROR;
	else if( (posicion >= lista->cantidad-1 ) || (lista->cantidad == 1))
		lista_borrar(lista);
	else{
		if (posicion > 0){
			nodo_t* nodo_aux_A = obtener_nodo_posicion(lista, (posicion-1));     
			nodo_t* nodo_aux_B;
			nodo_aux_B = nodo_aux_A->siguiente;
			nodo_aux_A->siguiente = nodo_aux_B->siguiente;
			free (nodo_aux_B);
		}
		else{
			nodo_t* nodo_aux = lista->nodo_inicio;
			lista->nodo_inicio = lista->nodo_inicio->siguiente;
			free(nodo_aux);
		}
		lista->cantidad--;	
	}
	return EXITO;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	
	if (!lista)
		return NULL;
	
	if( (posicion > (lista->cantidad-1) ) || (lista->cantidad == 0))
		return NULL;

	else{
	
		nodo_t* nodo_aux = obtener_nodo_posicion(lista, posicion);
		return nodo_aux->elemento;
	}		
}

void* lista_ultimo(lista_t* lista){
	void* ultimo_elemento = NULL;
	
	if(lista){
		if(lista->cantidad > 0)
			ultimo_elemento = lista->nodo_fin->elemento;	
	}
	return ultimo_elemento;
}

bool lista_vacia(lista_t* lista){
	
	bool esta_vacia = false;
	
	if (!lista)
		esta_vacia = true;
	else if (lista->cantidad == 0)
		esta_vacia = true; 
	
	return esta_vacia;  
}

size_t lista_elementos(lista_t* lista){
		return (lista? lista->cantidad : 0);
}

void lista_destruir(lista_t* lista){
	
	if(!lista)
		return;

	while(!lista_vacia(lista))
		lista_borrar(lista);
	free(lista); 
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
	
	if (!lista)
		return NULL;
	
	lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
	
	if (!iterador)
		return NULL;
	else{
		iterador->lista = lista;
		iterador->nodo_actual =  NULL;
	}	
	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	bool tiene_siguiente = true;

	if (!iterador)
		tiene_siguiente = false;
	
	else if(iterador->nodo_actual == NULL){
			if (iterador->lista->nodo_inicio == NULL)
				tiene_siguiente = false;
	}
	else if(iterador->nodo_actual->siguiente == NULL)
		tiene_siguiente =  false;

	return tiene_siguiente;
}

void* lista_iterador_siguiente(lista_iterador_t* iterador){
	
	if (!iterador)
		return NULL;
	
	if(iterador->lista->nodo_inicio == NULL)
		return NULL;

	if(iterador->nodo_actual == NULL){
		iterador->nodo_actual = iterador->lista->nodo_inicio;
		return (iterador->nodo_actual->elemento);
	}

	else if(lista_iterador_tiene_siguiente(iterador)){
		iterador->nodo_actual = iterador->nodo_actual->siguiente;
		return(iterador->nodo_actual->elemento);
	}
	return NULL;	
}

void lista_iterador_destruir(lista_iterador_t* iterador){
	if (!iterador)
		return;
	free(iterador);
}

void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*)){
	if (!lista)
		return;
	if(!funcion)
		return;

	nodo_t* nodo_aux = lista->nodo_inicio;

	if(!lista_vacia(lista)){

		for (int i=0; i<lista->cantidad;i++){
			funcion(nodo_aux->elemento);
			nodo_aux =nodo_aux->siguiente;
		}
	}
}

nodo_t* crear_nodo (void* elemento){
	
	nodo_t* nodo = malloc(sizeof(nodo_t));
	
	if(!nodo)
		return NULL;
	else{
		nodo->elemento = elemento;
		nodo->siguiente = NULL;
		return nodo;
	}
}

void insertar_nodo(lista_t* lista, nodo_t* nodo){
	
	if (lista->cantidad == 0){
		lista->nodo_inicio = nodo;
		lista->nodo_fin = nodo;
		nodo->siguiente = NULL;
	}
	else{
		lista->nodo_fin->siguiente = nodo;
		lista->nodo_fin = nodo;
		nodo->siguiente = NULL;
	}	
}

nodo_t* obtener_nodo_posicion(lista_t* lista, size_t posicion){
	int i = 0;
	nodo_t* nodo_aux = lista->nodo_inicio;

	while(nodo_aux != NULL && i<posicion){
		nodo_aux = nodo_aux->siguiente;
		i++;
	}
	return nodo_aux;		
}