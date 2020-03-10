#include "hash_iterador.h"
#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>


#define EXITO 0
#define ERROR -1

struct hash{
	lista_t** indices;
	size_t capacidad;
	size_t elementos;
	hash_destruir_dato_t destructor;
};

typedef struct nodo_hash{
	const char* clave;
	void* valor;
}nodo_hash_t;

struct hash_iter{
	hash_t* hash;
	lista_iterador_t* lista_iter;
	size_t lista_iterada;
	nodo_hash_t* nodo_actual;
};

hash_iterador_t* hash_iterador_crear(hash_t* hash){

	hash_iterador_t* iter = NULL; 
	
	if(hash){
		
		iter = calloc(1, sizeof(hash_iterador_t));

		if(iter){
			iter->hash = hash;
			
			if(hash->indices){

				if(hash->indices[0]){
					iter->lista_iter = lista_iterador_crear(hash->indices[0]);
				}
			}	
		}
	}
	return iter;	
}

/*PRE: La funcion debe recibir un puntero a una variable hash_iterador_t no nulo.
 *POST: Se retornara el numero de indice que representa la proxima lista no vacia dentro de las listas
 *		del hash iterado. En caso de error o de no haber un indice no vacio, se retornara -1.	
 *
 */
int buscar_proximo_indice_no_vacio(hash_iterador_t* iterador){
	
	int retorno = ERROR;
	bool encontre_indice = false;
	int i = (int)((iterador->lista_iterada) +1);

	if(iterador){

		while( (i < iterador->hash->capacidad) && (!encontre_indice) ){
			
			if(!lista_vacia(iterador->hash->indices[i])){
				retorno = i;
				encontre_indice = true;
			}
			i++;	
		}
	}
	return retorno;
}

bool hash_iterador_tiene_siguiente(hash_iterador_t* iterador){
	
	bool tiene_siguiente = false;
	
	if(iterador){

		if(!lista_iterador_tiene_siguiente(iterador->lista_iter)){
			
			if(buscar_proximo_indice_no_vacio(iterador) > ERROR){
				tiene_siguiente = true;			
			}
		}
		else{

			tiene_siguiente = true;
		}
	
	}
	return tiene_siguiente;
} 

void* hash_iterador_siguiente(hash_iterador_t* iterador){
	
	const char* elemento = NULL;
	
	if(iterador){
		
		if(hash_iterador_tiene_siguiente(iterador)){

			if(lista_iterador_tiene_siguiente(iterador->lista_iter)){
				
				iterador->nodo_actual = lista_iterador_siguiente(iterador->lista_iter);
				elemento = iterador->nodo_actual->clave;
			}
			else{
				
				int indice_no_vacio = buscar_proximo_indice_no_vacio(iterador);
				
				if(indice_no_vacio > ERROR){
					
					lista_iterador_destruir(iterador->lista_iter);
					iterador->lista_iter = lista_iterador_crear(iterador->hash->indices[indice_no_vacio]);
					iterador->nodo_actual = lista_iterador_siguiente(iterador->lista_iter);
					elemento = iterador->nodo_actual->clave;
					iterador->lista_iterada = (size_t)indice_no_vacio;
				}
			}	
		}
	}
	return (void*)elemento;	
}

void hash_iterador_destruir(hash_iterador_t* iterador){

	if(iterador){
		
		lista_iterador_destruir(iterador->lista_iter);
		free(iterador);
	}
}