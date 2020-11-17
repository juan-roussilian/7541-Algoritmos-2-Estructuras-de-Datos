#include "abb.h"
#include <stdio.h>

#define EXITO 0
#define ERROR -1


/*Pre: Debe recibir un tipo de dato void*, pudiendo recibir un puntero a cualquier tipo de dato.
 *Post: Creara y retornara un puntero a un tipo de dato nodo_abb_t, e inicializara sus campos
 *		en NULL, exceptuando el campo elemento, el cual sera igualado al puntero recibido
 *		en caso de error por falta de memoria retornara NULL.
 */

nodo_abb_t* nodo_crear(void* elemento){
	
	nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
	
	if(nodo != NULL){
		
		nodo->elemento = elemento;
		nodo->izquierda = NULL;
		nodo->derecha = NULL;
	}
	return nodo;
}

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){ 
	
	abb_t* arbol = malloc(sizeof(abb_t));
	
	if (arbol != NULL){
		
		arbol->nodo_raiz = NULL;
		arbol->comparador = comparador;
		arbol->destructor = destructor;
	}
	return arbol;
}

/*Pre: Debe recibir un tipo de dato abb_comparador no nulo, un puntero a cualquier tipo de dato,
 *	   que sera el elemento a insertar dentro del arbol, un puntero a un nodo_abb_t el cual representa
 *	   el nodo actual, y un puntero a un entero el cual permitira devolver el resultado de la busqueda
 *
 *Post:	Retornara un puntero a un nodo_abb_t el cual sera el nodo ya insertado en el arbol, en caso de
 *		no cumplirse las pre condiciones, se retornara como referencia -1 como resultado representado el
 *		el error que se dio en la insercion recursiva.
 */
nodo_abb_t* arbol_insertar_rec(abb_comparador comparador, void* elemento, nodo_abb_t* nodo_actual, int* resultado){
	
	if(nodo_actual == NULL){
		
		nodo_abb_t* nodo_nuevo = nodo_crear(elemento);
		
		if(nodo_nuevo == NULL){
			(*resultado) = ERROR;
		}
		else{ 
			nodo_actual = nodo_nuevo;
		}	
	}
	else if(comparador(elemento,nodo_actual->elemento) >= 0){
		nodo_actual->derecha = arbol_insertar_rec(comparador, elemento, nodo_actual->derecha, resultado);
	}
	else{
		nodo_actual->izquierda = arbol_insertar_rec(comparador, elemento, nodo_actual->izquierda, resultado);
	}
	return nodo_actual;
}

int arbol_insertar(abb_t* arbol, void* elemento){
	
	int resultado = EXITO;
	
	if(arbol == NULL){
		resultado = ERROR;
	}
	else if (arbol->nodo_raiz == NULL){
		arbol->nodo_raiz = arbol_insertar_rec(arbol->comparador, elemento, arbol->nodo_raiz, &resultado);																			
	}
	else{
		arbol_insertar_rec(arbol->comparador, elemento, arbol->nodo_raiz, &resultado);
	}
	return resultado;
}	

/*Pre: La funcion debe recibir un tipo de dato abb_comparador no nulo, un puntero a 
 * 	   un nodo_abb_t representando el nodo sobre el cual se encuentra la funcion, un puntero
 * 	   a cualquier tipo de dato representando el elemento que se quiere buscar dentro del arbol
 *     y un doble puntero a un nodo_abb_t el cual representara el padre del nodo que contiene al
 *     elemento buscado
 *
 *Post: La funcion retornara un puntero a al nodo que contiene el elemento buscado, asignara a
 *		la variable padre el nodo padre del buscado, o null si el buscado es la raiz del arbol, si es que 
 *		se cumplen las pre condiciones. De no cumplirse o no hallarse el elemento el el arbol la funcion
 *		devolvera NULL
 */
nodo_abb_t* buscar_abb_rec(abb_comparador comparador, nodo_abb_t* actual, void* elemento, nodo_abb_t** padre){

	nodo_abb_t* auxiliar;

	if( (actual == NULL) || (comparador(elemento,actual->elemento) == 0) ){
		return actual;
	}
		
	else if(comparador(elemento, actual->elemento) >= 0){
	
		if ( (actual->derecha != NULL) && (comparador(elemento, actual->derecha->elemento) == 0 ) ) {
			*(padre) = actual;
		}	
		auxiliar = buscar_abb_rec(comparador, actual->derecha, elemento, padre);
	}	
	else{

		if ( (actual->izquierda != NULL) && (comparador(elemento, actual->izquierda->elemento) == 0 ) ) {
			*(padre) = actual;
		}
		auxiliar = buscar_abb_rec(comparador, actual->izquierda, elemento, padre);
	}
	return auxiliar;	

}

void* arbol_buscar(abb_t* arbol, void* elemento){ 
	void* buscado = NULL;
	nodo_abb_t* nodo;

	if(arbol != NULL){
		
		nodo_abb_t* nodo_aux = buscar_abb_rec(arbol->comparador, arbol->nodo_raiz, elemento, &nodo);

	 	if(nodo_aux != NULL){
			buscado = nodo_aux->elemento;
		}	
	}
	return buscado;		
}
/*Pre: La funcion debe recibir un puntero a un nodo no nulo representando el nodo sobre el cual 
 *	   se esta ejecutando la funcion recursiva, y un doble puntero a un nodo 
 *
 *Post: La funcion retornara un puntero a un nodo representando el hijo mayor de un subarbol,
 *		y asignara a la variable padre el nodo padre del dicho hijo buscado.
 *		Si no se cumplen las precondicones se retornara NULL.
 */

nodo_abb_t* buscar_hijo_mayor(nodo_abb_t* nodo, nodo_abb_t** padre){
	
	if(nodo == NULL){  
		return NULL; 
	}	
	if(nodo->derecha == NULL){
		return nodo;
	}
	if(nodo->derecha->derecha == NULL){
		*(padre) = nodo;
		return nodo->derecha;
	}
	return (buscar_hijo_mayor(nodo->derecha, padre));
}

/*Pre: La funcion debe recibir un puntero a un nodo no nulo el cual debe tener dos hijos,
 *	   y un tipo de dato  abb_liberar_elemento (Puede ser Nulo representando que no se
 *	   necesita liberar de manera particular el elemento dentro del nodo). 

 *Post: Si se cumplen las precondiciones la funcion eliminara exitosamente un nodo con dos hijos
 *		del arbol y retornara 0 representado el resultado exitoso, sino retornara -1 representado
 *		el resultado fallido.
 */
int borrar_nodo_dos_hijos(nodo_abb_t* nodo, abb_liberar_elemento destructor){
	
	int resultado = ERROR;
	if(nodo != NULL){
		
		nodo_abb_t* reemplazante;
		nodo_abb_t* padre_reemplazante = nodo;
		reemplazante = buscar_hijo_mayor(nodo->izquierda, &padre_reemplazante);

		if(destructor != NULL){
			destructor(nodo->elemento);
		}	
		nodo->elemento = reemplazante->elemento;

		if(padre_reemplazante->izquierda == reemplazante){
		
			if(reemplazante->izquierda != NULL){
				padre_reemplazante->izquierda = reemplazante->izquierda;
			}
			else{
				padre_reemplazante->izquierda = NULL;
			}
			resultado = EXITO;
		}	
		else if (padre_reemplazante->derecha == reemplazante){

			if(reemplazante->izquierda != NULL){
				padre_reemplazante->derecha = reemplazante->izquierda;
			}
			else{
				padre_reemplazante->derecha = NULL;
			}
			resultado = EXITO;
		}

		free(reemplazante);
	}	
	return resultado;
}

/*Pre: La funcion debe recibir un puntero a un nodo raiz del arbol con un hijo,representando 
 *	   el nodo que se desea borrar, un tipo de dato abb_liberar_elemento (el cual puede ser 
 *	   nulo indicando que no es necesario liberar de manera particular el elemento dentro del nodo)
 *	   e un puntero a un entero no nulo en el cual se devolvera por referencia el resultado del borrado,
 *
 *Post: Si se cumplen las precondiciones la funcion eliminara a un nodo raiz del arbol, y devolvera a
 *		a su unico nodo hijo. Si no se incumplen las precondiciones, resultado sera devuelto con un valor
 *      de 0 representando el exito de la funcion, o -1 en caso de error.
 */
nodo_abb_t* borrar_nodo_raiz_con_hijo(nodo_abb_t* nodo, abb_liberar_elemento destructor, int* resultado){
	
	nodo_abb_t* nodo_aux = NULL;

	if(nodo != NULL){
		if(nodo->derecha == NULL){
			nodo_aux = nodo->izquierda;
		}
		else if(nodo->izquierda == NULL){
			nodo_aux = nodo->derecha;
		}
		if(destructor != NULL){
			destructor(nodo->elemento);
		}
		free(nodo);
		*(resultado) = EXITO;
	}
	return nodo_aux;
}
 
/*Pre: La funcion debe recibir un puntero a un del arbol con un hijo,representando 
 *	   el nodo que se desea borrar, un tipo de dato abb_liberar_elemento (el cual puede ser 
 *	   nulo indicando que no es necesario liberar de manera particular el elemento dentro del nodo)
 *	   e un puntero a un nodo el cual representara el padre del nodo a borrar
 *
 *Post: Si se cumplen las precondiciones la funcion eliminara a un nodo  del arbol, y un entero
 *		 sera devuelto con un valor de 0 representando el exito de la funcion, o -1 en caso de error.
 */ 
int borrar_nodo_un_hijo(nodo_abb_t* nodo, nodo_abb_t* padre, abb_liberar_elemento destructor){

	int resultado = ERROR;

	if(nodo != NULL && padre != NULL){

		if(padre->derecha == nodo){
			
			if(nodo->izquierda == NULL){ //caso 1
				padre->derecha = nodo->derecha;
			}
			else if(nodo->derecha == NULL){ //caso 2
				padre->derecha = nodo->izquierda;
			}
			resultado = EXITO;
		}
		else if(padre->izquierda == nodo){
			
			if(nodo->izquierda == NULL){ //caso 3
				padre->izquierda = nodo->derecha;
			}
			else if(nodo->derecha == NULL){ //caso 4
				padre->izquierda = nodo->izquierda;
			}
			resultado = EXITO;
		}
		if(destructor != NULL){
			destructor(nodo->elemento);
		}
		free(nodo);
	}
	return resultado;	
}

/*Pre: La funcion debe recibir un puntero a un del arbol sin hijos,representando 
 *	   el nodo que se desea borrar, un tipo de dato abb_liberar_elemento (el cual puede ser 
 *	   nulo indicando que no es necesario liberar de manera particular el elemento dentro del nodo)
 *	   e un puntero a un nodo el cual representara el padre del nodo a borrar
 *
 *Post: Si se cumplen las precondiciones la funcion eliminara a un nodo  del arbol, y un entero
 *		 sera devuelto con un valor de 0 representando el exito de la funcion, o -1 en caso de error.
 */ 
int borrar_nodo_hoja(nodo_abb_t* nodo, nodo_abb_t* padre, abb_liberar_elemento destructor){
	
	int resultado = ERROR;

	if(nodo != NULL){

		if(padre->derecha == nodo){
			
			padre->derecha = NULL;
			resultado = EXITO;
		}
		else if(padre->izquierda == nodo){

			padre->izquierda = NULL;
			resultado = EXITO;
		}		
		if(destructor != NULL){
				
			destructor(nodo->elemento);
		}
		free(nodo);
	}
	return resultado;	
}

int arbol_borrar(abb_t* arbol, void* elemento){

	int resultado = ERROR;
	bool nodo_es_raiz = false;

	if(arbol != NULL){
		
		nodo_abb_t* nodo_padre_aux = NULL;
		nodo_abb_t* nodo_aux = buscar_abb_rec(arbol->comparador, arbol->nodo_raiz, elemento, &nodo_padre_aux);
	 	
		if(nodo_aux != NULL){
			
			if(nodo_padre_aux == NULL){
			 	nodo_es_raiz = true;	
			}
			if( (nodo_aux->derecha != NULL) && (nodo_aux->izquierda != NULL) ){
					
				resultado = borrar_nodo_dos_hijos(nodo_aux, arbol->destructor);
			}	

			else if( (nodo_aux->derecha == NULL) && (nodo_aux->izquierda == NULL) ){
				
				if(!nodo_es_raiz){	
					resultado = borrar_nodo_hoja(nodo_aux, nodo_padre_aux, arbol->destructor);
				}
				else{
					arbol->nodo_raiz = NULL;
					if(arbol->destructor !=NULL){
						arbol->destructor(nodo_aux->elemento);
					}
					free(nodo_aux);
					resultado = EXITO;
				}
			}
			else{
				if(!nodo_es_raiz){
					resultado = borrar_nodo_un_hijo(nodo_aux, nodo_padre_aux, arbol->destructor);
				}
				else{
				 	arbol->nodo_raiz = borrar_nodo_raiz_con_hijo(nodo_aux, arbol->destructor, &resultado);
				}
			}	
		}				
	}
	return resultado;
}	 	

void* arbol_raiz(abb_t* arbol){
	return (arbol_vacio(arbol)? NULL : arbol->nodo_raiz->elemento);
}	 

bool arbol_vacio(abb_t* arbol){
	
	bool esta_vacio = false;
	
	if ( (arbol == NULL) || (arbol->nodo_raiz == NULL) ){
		esta_vacio = true;
	}	
	return esta_vacio;	
}	

/*Pre: La funcion debe recibir un puntero a un nodo el cual no debe ser NULL, un puntero
 *     a un vector que tampoco puede ser NULL, un entero representando el tamano de dicho
 *	   arreglo, y un puntero a un entero el cual indica la cantidad de elementos llenados 
 *	   por la funcion.
 *		
 *Post: La funcion pondra el vector todos los elementos del arbol recursivamente utilizando 
 *		el criterio "in-orden" hasta que este se llene o no halla mas elementos. Ademas devolvera
 *	    por referencia  el numero de elementos ubicados exitosamente en el vector.
 */
void inorden_rec(nodo_abb_t* nodo_actual, void** array, int tamanio, int* llenados){
	
	if ( (nodo_actual != NULL) && ((*llenados) < tamanio) && (array != NULL) ){
		
		inorden_rec(nodo_actual->izquierda, array, tamanio, llenados);
		
		if((*llenados) < tamanio){
			array[(*llenados)] = nodo_actual->elemento;
			(*llenados)++;	
		}	
		inorden_rec(nodo_actual->derecha, array, tamanio, llenados);	
	}
	return;
}
 
int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){ 
	int llenados = 0;
	
	if ( (arbol == NULL) || (array == NULL) ){
		return 0;
	}
	inorden_rec(arbol->nodo_raiz, array, tamanio_array, &llenados);
	return llenados;
}


/*Pre: La funcion debe recibir un puntero a un nodo el cual no debe ser NULL, un puntero
 *     a un vector que tampoco puede ser NULL, un entero representando el tamano de dicho
 *	   arreglo, y un puntero a un entero el cual indica la cantidad de elementos llenados 
 *	   por la funcion.
 *		
 *Post: La funcion pondra el vector todos los elementos del arbol recursivamente utilizando 
 *		el criterio "pre-orden" hasta que este se llene o no halla mas elementos. Ademas devolvera
 *	    por referencia  el numero de elementos ubicados exitosamente en el vector.
 */
void preorden_rec(nodo_abb_t* nodo_actual, void** array, int tamanio, int* llenados){
	
	if ( (nodo_actual != NULL) && ((*llenados) < tamanio) && (array != NULL) ){
		
		array[(*llenados)] = nodo_actual->elemento;
		(*llenados)++;		
		preorden_rec(nodo_actual->izquierda, array, tamanio, llenados);
		preorden_rec(nodo_actual->derecha, array, tamanio, llenados);	
	}
	return;
}	

int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){ // NO pre y post

	int llenados = 0;
	
	if ( (arbol == NULL) || (array == NULL) ){
		return 0;
	}
	preorden_rec(arbol->nodo_raiz, array, tamanio_array, &llenados);
	return llenados;
}


/*Pre: La funcion debe recibir un puntero a un nodo el cual no debe ser NULL, un puntero
 *     a un vector que tampoco puede ser NULL, un entero representando el tamano de dicho
 *	   arreglo, y un puntero a un entero el cual indica la cantidad de elementos llenados 
 *	   por la funcion.
 *		
 *Post: La funcion pondra el vector todos los elementos del arbol recursivamente utilizando 
 *		el criterio "post-orden" hasta que este se llene o no halla mas elementos. Ademas devolvera
 *	    por referencia  el numero de elementos ubicados exitosamente en el vector.
 */
void postorden_rec(nodo_abb_t* nodo_actual, void** array, int tamanio, int* llenados){
	
	if ( (nodo_actual != NULL) && ((*llenados) < tamanio) && (array != NULL) ){
		
		postorden_rec(nodo_actual->izquierda, array, tamanio, llenados);
		postorden_rec(nodo_actual->derecha, array, tamanio, llenados);
		
		if((*llenados) < tamanio){
			array[(*llenados)] = nodo_actual->elemento;
			(*llenados)++;		
		}
	}	
	return;
}
 
int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){ 
	
	int llenados = 0;

	if (arbol == NULL || array == NULL){
		return 0;
	}
	postorden_rec(arbol->nodo_raiz, array, tamanio_array, &llenados);
	return llenados; 
} 

/*Pre: La funcion debe recibir un tipo de dato abb_liberar_elemento, y un puntero a un
 *	   nodo el cual debe ser la raiz del arbol
 *
 *Post:	La funcion recorrera la funcion recursivamente utilizando el critero "post-orden"
 *		aplicando el destructor a cada elemento del arbol (Puede ser NULL indicando que 
 *		no es necesario liberar los elementos con una funcion particular) y liberando 
 *		cada nodo
 *
 */
void destruir_elementos_arbol(abb_liberar_elemento destructor, nodo_abb_t* nodo_actual){
	
	if(nodo_actual != NULL){

		destruir_elementos_arbol(destructor, nodo_actual->izquierda);
		destruir_elementos_arbol(destructor, nodo_actual->derecha);
		
		if(destructor != NULL){
			destructor(nodo_actual->elemento);
		}
		free(nodo_actual);
	}
	return;
}

void arbol_destruir(abb_t* arbol){ 
	if(arbol != NULL){
		destruir_elementos_arbol(arbol->destructor, arbol->nodo_raiz);
		free(arbol);
	}
} 

/*Pre: La funcion debe recibir un puntero  a un nodo el cual no debe ser nulo, un puntero a una funcion
 *	   del tipo bool que recibe a su vez dos punteros a cualquier tipo de dato, y un puntero
 *	   booleano que indica si se debe abortar el recorrido del arbol.	
 *		
 *Post:	La funcion recorrera recursivamente el arbol, utilizando el critero "in-orden" y aplicara a cada
 *		elemento la funcion recibida como parametro, hasta que esta devuelva true.
 *
 */
void inorden_con_cada_elemento(nodo_abb_t* actual, bool (*funcion)(void*, void*), void* extra, bool* terminar_recorrido){
	
	if( (actual == NULL) || ((*terminar_recorrido) == true) || (funcion == NULL) ){
		return; 											
	}
	else {
		inorden_con_cada_elemento(actual->izquierda, funcion, extra, terminar_recorrido);
		 
		if (!(*terminar_recorrido)){
			(*terminar_recorrido) = funcion(actual->elemento, extra); 
		}

		inorden_con_cada_elemento(actual->derecha, funcion, extra, terminar_recorrido);	
	}
	return;
}
/*Pre: La funcion debe recibir un puntero  a un nodo el cual no debe ser nulo, un puntero a una funcion
 *	   del tipo bool que recibe a su vez dos punteros a cualquier tipo de dato, y un puntero
 *	   booleano que indica si se debe abortar el recorrido del arbol.	
 *		
 *Post:	La funcion recorrera recursivamente el arbol, utilizando el critero "pre-orden" y aplicara a cada
 *		elemento la funcion recibida como parametro, hasta que esta devuelva true.
 *
 */
void preorden_con_cada_elemento(nodo_abb_t* actual, bool (*funcion)(void*, void*), void* extra, bool* terminar_recorrido){
	
	if( (actual == NULL) || ((*terminar_recorrido) == true) || (funcion == NULL) ){
		return; 
	}
	else{	
		if (!(*terminar_recorrido)){
			(*terminar_recorrido) = funcion(actual->elemento, extra); 
		}

		preorden_con_cada_elemento(actual->izquierda, funcion, extra, terminar_recorrido); 

		preorden_con_cada_elemento(actual->derecha, funcion, extra, terminar_recorrido);	
	}
	return;
}

/*Pre: La funcion debe recibir un puntero  a un nodo el cual no debe ser nulo, un puntero a una funcion
 *	   del tipo bool que recibe a su vez dos punteros a cualquier tipo de dato, y un puntero
 *	   booleano que indica si se debe abortar el recorrido del arbol.	
 *		
 *Post:	La funcion recorrera recursivamente el arbol, utilizando el critero "post-orden" y aplicara a cada
 *		elemento la funcion recibida como parametro, hasta que esta devuelva true.
 *
 */
void postorden_con_cada_elemento(nodo_abb_t* actual, bool (*funcion)(void*, void*), void* extra, bool* terminar_recorrido){
	
	if( (actual == NULL) || ((*terminar_recorrido) == true) || (funcion == NULL) ){
		return; 
	}
	else{
		postorden_con_cada_elemento(actual->izquierda, funcion, extra, terminar_recorrido); 

		postorden_con_cada_elemento(actual->derecha, funcion, extra, terminar_recorrido);

		if (!(*terminar_recorrido)){
			(*terminar_recorrido) = funcion(actual->elemento, extra);	
		}
	}
}

void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){ 
	
	bool inicio = false;

	if ( (arbol != NULL) && (funcion != NULL) ){

		switch(recorrido){

			case ABB_RECORRER_INORDEN:
				
				inorden_con_cada_elemento(arbol->nodo_raiz, funcion, extra, &inicio);
				break;

			case ABB_RECORRER_PREORDEN:
				
				preorden_con_cada_elemento(arbol->nodo_raiz, funcion, extra, &inicio);
				break;

			case ABB_RECORRER_POSTORDEN:
				
				postorden_con_cada_elemento(arbol->nodo_raiz, funcion, extra, &inicio);
				break; 
		}
	}
	return;
}