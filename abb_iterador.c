#include "lista.h"
#include "abb_iterador.h"
#include "pila.h"



struct abb_iterador{
    abb_t* arbol;
    pila_t* pila_nodos;
    lista_t* nodos_visitados;
    nodo_abb_t* nodo_actual;
};


abb_iterador_t* abb_iterador_crear(abb_t* arbol){

	abb_iterador_t* iterador = NULL;

	if(arbol){

		iterador = calloc(1, sizeof(abb_iterador_t));
		
		if(iterador){
			iterador->arbol = arbol;
			iterador->pila_nodos = pila_crear();

			if(!iterador->pila_nodos){
				free(iterador);
				iterador = NULL;
			}
			else{
				iterador->nodos_visitados = lista_crear();
				if(!iterador->nodos_visitados){
					pila_destruir(iterador->pila_nodos);
					free(iterador);
					iterador = NULL;
				}
			}
		}	
	}
	return iterador;
}

/*PRE: La funciond debe recibir dos punteros no nulos a dos TDAs Pilas.
 *POST: Si ningun puntero es nulo, apilara los elementos de la primer pila
 *		dentro de la segunda.
 */
void intercambiar_pilas(pila_t* pila_1, pila_t* pila_2){
	
	if((pila_1) && (pila_2)){
		
		while(!pila_vacia(pila_1)){
	     	pila_apilar(pila_2, pila_tope(pila_1));
			pila_desapilar(pila_1);
		}
	}
}

/*PRE: La funcion debe recibir un puntero a un tipo de dato nodo_abb_t que puede ser
 *	   nulo y un puntero a una lista, no nulos.
 *POST: La funcion retornara true en caso de que el nodo sea nulo o este dentro de 
 *		la lista de nodos visitados, o false en caso contrario o en caso de que la 
 *      lista sea nula.
 */
bool nodo_fue_visitado(nodo_abb_t* nodo, lista_t* nodos_visitados){
	
	bool fue_visitado = false;

	if(!nodo){
		fue_visitado = true;
	}

	else if(nodos_visitados){
		
		lista_iterador_t* iter = lista_iterador_crear(nodos_visitados);
		
		while( (lista_iterador_tiene_siguiente(iter)) && (!fue_visitado) ){
			
			if(lista_iterador_siguiente(iter) == nodo){
				fue_visitado = true;
			}
		}
		lista_iterador_destruir(iter);
	}
	return fue_visitado;
}

/*PRE: La funcion debe recibir un puntero a un tipo de dato nodo_abb_t y un puntero
 *	  a una lista no nula.
 *POST: Se retornara true en caso de que el nodo posea nodos hijos que no esten en la
 *		la lista de nodos visitados, o false en caso de que haya al menos uno dentro de
 *		la lista, o el nodo o la lista sean nulos.
 */
bool nodo_tiene_hijos_no_visitados(nodo_abb_t* nodo, lista_t* nodos_visitados){
	bool tiene_no_visitados = false;
	if( (nodo) && (nodos_visitados)){
		if( (!nodo_fue_visitado(nodo->izquierda, nodos_visitados)) || (!nodo_fue_visitado(nodo->derecha, nodos_visitados)) ){
			tiene_no_visitados = true;
		}
	}
	return tiene_no_visitados;
}

/*PRE: La funcion debe recibir un puntero a un nodo_abb_t no nulo, un puntero a dos estructuras pilas no nulas
 *	   y un puntero a una lista, la cual tampoco puede ser nula.
 *POST:	Se buscara recursivamente dentro del arbol si algun nodo ya visitado antes que el nodo recibido tiene
 *		hijos por visitar, y se retornara true en caso de que asi sea. Caso contrario se retornara false.
 */
bool tiene_siguiente_rec(nodo_abb_t* nodo, pila_t* pila_nodos, pila_t* pila_aux, lista_t* nodos_visitados){

	bool resultado = false;

	pila_apilar(pila_aux, pila_tope(pila_nodos));
	pila_desapilar(pila_nodos);

	if(pila_vacia(pila_nodos)){
		resultado = false;
	}
	else{
		nodo_abb_t* nodo_anterior = pila_tope(pila_nodos);
		if(nodo_tiene_hijos_no_visitados(nodo_anterior, nodos_visitados)){
			resultado = true;
		}
		else{
			resultado = tiene_siguiente_rec(nodo_anterior, pila_nodos, pila_aux, nodos_visitados);
		}
	}
	return resultado;
}

bool abb_iterador_tiene_siguiente(abb_iterador_t* iterador){

	bool tiene_siguiente = false;

	if(iterador){
		
		if(!iterador->nodo_actual){
			if(!arbol_vacio(iterador->arbol)){
				tiene_siguiente = true;
			}
		}	
		else{

			if(iterador->nodo_actual->izquierda || iterador->nodo_actual->derecha){
				tiene_siguiente = true;
			}
			else{
				pila_t* pila_aux = pila_crear();
				if(pila_aux){
					tiene_siguiente = tiene_siguiente_rec(iterador->nodo_actual,iterador->pila_nodos, pila_aux, iterador->nodos_visitados);
					intercambiar_pilas(pila_aux, iterador->pila_nodos);
				}
				pila_destruir(pila_aux);
			}		
		}
	}
	return tiene_siguiente;
}

/*PRE: La funcion debe recibir un puntero a un nodo_abb_t no nulo, un puntero a una estructura pila no nula
 *	   y un puntero a una lista, la cual tampoco puede ser nula.
 *POST:	Se buscara recursivamente dentro del arbol el nodo siguiente al recibido siguiendo el recorrido preorden
 *		y se retornara el nodo en caso de encontrarlo. Caso contrario se retornara NULL.
 */
nodo_abb_t* siguiente_nodo_rec(nodo_abb_t* nodo, pila_t* pila_nodos, lista_t* nodos_visitados){
	
	nodo_abb_t* nodo_sig = NULL;
	if(!nodo_fue_visitado(nodo->izquierda, nodos_visitados)){
		nodo_sig = nodo->izquierda;
	}

	else if(!nodo_fue_visitado(nodo->derecha, nodos_visitados)){
		nodo_sig = nodo->derecha;
	}
	else{
		pila_desapilar(pila_nodos);
		if(pila_vacia(pila_nodos)){
			return NULL;
		}
		else{
			nodo_sig = siguiente_nodo_rec((nodo_abb_t*)pila_tope(pila_nodos), pila_nodos, nodos_visitados);
		}
	}	
	return nodo_sig;
}

void* abb_iterador_siguiente_preorden(abb_iterador_t* iterador){
	
	void* elemento = NULL;
	
	if(abb_iterador_tiene_siguiente(iterador)){
		
		if(iterador->nodo_actual == NULL){
			
			iterador->nodo_actual = iterador->arbol->nodo_raiz;
			pila_apilar(iterador->pila_nodos, iterador->nodo_actual);
			lista_insertar(iterador->nodos_visitados, iterador->nodo_actual);
			elemento = iterador->nodo_actual->elemento;		
		}
		else{
			
			nodo_abb_t* nodo_siguiente = siguiente_nodo_rec(pila_tope(iterador->pila_nodos),iterador->pila_nodos, iterador->nodos_visitados);
			
			if(nodo_siguiente){
				iterador->nodo_actual = nodo_siguiente;
				elemento = nodo_siguiente->elemento;
				pila_apilar(iterador->pila_nodos, nodo_siguiente);
				lista_insertar(iterador->nodos_visitados, nodo_siguiente);
			}	
		}
	}	
	return elemento;	
}

void abb_iterador_destruir(abb_iterador_t* iterador){
	
	if(iterador){
		pila_destruir(iterador->pila_nodos);
		lista_destruir(iterador->nodos_visitados);
		free(iterador);
	}
}