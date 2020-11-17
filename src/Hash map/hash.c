#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash_iterador.h"

#define EXITO 0
#define ERROR -1
#define COEFICIENTE_REHASH_AGRANDAR 2
#define COEFICIENTE_REHASH_ACHICAR 8

extern char* strdup(const char*);

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

/*PRE: La funcion recibe un numero entero positivo o 0.
 *POST: Retornara un tipo de dato Booleano cuyo valor sera true si el numero
 * 		recibido es primo, o false en caso contrario.
 */
bool es_numero_primo(size_t numero){
	
	bool es_primo = true;

	for(size_t i = 2; i < ((numero/2)+1); i++){
		
		if(i < numero){	
			if((numero % i) == 0){
				es_primo = false;
			}
		}	
	}
	return es_primo;
}

/*PRE: La funcion debe recibir un numero entero positivo o 0.
 *POST: La funcion retornara el siguiente numero entero positivo primo mas proximo al recibido.
 */
size_t obtener_siguiente_primo(size_t numero){

	size_t siguiente_primo = numero + 1;
	while(!es_numero_primo(siguiente_primo)){
		
		siguiente_primo++;
	}
	return siguiente_primo;
}

/*PRE: La funcion debe recibir un tipo de dato string no nulo.
 *
 *
 *POST: Se retornara la suma de los valores ascii de los caracteres dentro 
 *		del string recibido.
 */
int contar_string(const char* string){
	
	int acumulador = 0;
   	if(string){

   		size_t largo = strlen(string);
    
    	for (int i = 0; i < largo; i++){
        
        	acumulador += string[i];
    	}
    }	
	return acumulador;
}  

/*PRE: La funcion debe recibir un string no nulo representado la clave a hashear
 *	   y un entero positivo o 0 que representa la cantidad de indices del hash	
 *	   disponibles para guardar elementos.	
 *POST: La funcion retornara un entero el cual representara el indice en el cual
 *		el elemento asociado a la clave recibida se guardara, o -1 en caso de error.
 *
 */
int funcion_hasheo(const char* clave, size_t capacidad){
	int posicion = ERROR;
	
	if(clave){
		int valor_ascii = contar_string(clave);
		posicion = ( (valor_ascii + 10000) % (int)capacidad); 
	}
	return posicion;
}

/*PRE: La funcion debe recibir un puntero a una variable dato nodo_hash_t no nulo y un puntero a una
 *	   funcion hash_destruir_dato_t el cual puede ser NULL indicando que no se debe usar dicha funcion. 	
 *
 *POST:	Se destruira el elemento recibido de la lista liberando la memoria usada por este.
 */
void destruir_elemento_hash(nodo_hash_t* nodo, hash_destruir_dato_t destructor){
	
	if(nodo){
		
		if(destructor){
			destructor(nodo->valor);
		}
		free((char*)nodo->clave);
		free(nodo);
	}
}

/*PRE: La funcion debe recibir un string no nulo, y un puntero a cualquier tipo de dato.
 *POST: Se retornara un puntero a una variable del tipo nodo_hash_t, el cual guardara 
 *		dentro de si la clave y el elemento recibidos como parametros.
 */
nodo_hash_t* crear_nodo_hash(const char* clave, void* elemento){
	
	nodo_hash_t* nodo = NULL; 
	
	if(clave){
		
		nodo = malloc(sizeof(nodo_hash_t));
		
		if(nodo){

			nodo->clave = strdup(clave); 
			nodo->valor = elemento;
		}	
	}
	return nodo;
}

/*PRE: La funcion debe recibir un puntero a un vector de listas no nulo ,un entero positivo representando
 *	   hasta que indice se debe eliminar, y un puntero a una funcion del tipo hash_destruir_dato_t.
 *POST:	Se destruiran todos los indices anteriores al numero de indice recibido, liberando la memoria
 *		reservada para estos.
 */
void destruir_indices_hash(lista_t** indices, size_t numero_indice, hash_destruir_dato_t destructor){
	
	if(indices){
		
		nodo_hash_t* elemento = NULL;
		
		for(int i = 0; i < numero_indice; i++){
			
			lista_iterador_t* iter = lista_iterador_crear(indices[i]);	
			
			while(lista_iterador_tiene_siguiente(iter)){
				
				elemento = lista_iterador_siguiente(iter);
				destruir_elemento_hash(elemento, destructor);
			}
			lista_iterador_destruir(iter);
			lista_destruir(indices[i]);
		}
		free(indices);
	} 
}

/*PRE: La funcion debe recibir un numero entero positivo o 0 representando la cantidad de indices o 
 *	   listas que se quieren crear para el hash, y un puntero a una funcion del tipo hash_destruir_dato_t.
 *POST: La funcion reservara la memoria necesaria para la cantidad de indices requeridas por el parametro
 *		capacidad. En caso de no tener memoria suficiente, se retornara NULL.
 */
lista_t** crear_indices_hash(size_t capacidad, hash_destruir_dato_t destructor){

	lista_t** indices =  calloc (capacidad, sizeof(lista_t*));
	size_t i = 0;
	
	if(indices){	
		
		while (i < capacidad) {
			
			indices[i] = lista_crear();
			
			if(indices[i] == NULL){
				
				destruir_indices_hash(indices, i, destructor);
				indices = NULL;
			}
			i++;
		}
	}
	return indices;	
}

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad){

	hash_t* hash = 	calloc(1, sizeof(hash_t));
	
	if(hash){
		
		hash->destructor = destruir_elemento;
		hash->indices = crear_indices_hash(capacidad, destruir_elemento);
		hash->capacidad = capacidad;
		
		if(hash->indices == NULL){
			free(hash);
			hash = NULL;
		}

	}		
	return hash;	
}

/*PRE: La funcion debe recibir un puntero a una variable del tipo hash_t y otro puntero a una variable
 *     del tipo nodo_hash_t no nulos. 		 
 *POST: Se insertara el nodo recibido dentro del hash en su indice asignado por la funcion de hasheo.
 *		En caso de error se retornara -1, y en caso contrario 0. 
 */
int insertar_nodo_hash(hash_t* hash, nodo_hash_t* nodo){
	
	int resultado = ERROR;
	
	if((hash) && (nodo) ){	
		
		int posicion = funcion_hasheo(nodo->clave, hash->capacidad);
					
		if(posicion != ERROR){
			resultado = lista_insertar(hash->indices[posicion], nodo);
			
			if(resultado == EXITO){
				hash->elementos++;
			}
		}		
	}
	return resultado;
}

/*PRE: La funcion debe recibir un puntero a una variable hash_t y un string no nulos, y un puntero
 *	   a cualquier tipo de dato.	
 *POST: La funcion reemplazara el valor original asociado a la clave recibida dentro del hash, por 
 *		el nuevo valor tambien reicibido como parametro. En caso de ERROR se retornara -1, y en caso 
 *		contrario se retornara 0.
 */
int hash_actualizar_valor(hash_t* hash, const char* clave, void* elemento){
	
	int retorno = ERROR;
	
	if((hash) && (clave)){
		
		nodo_hash_t* nodo_aux = NULL;
		int posicion = funcion_hasheo(clave, hash->capacidad);
		lista_iterador_t* iterador = lista_iterador_crear(hash->indices[posicion]);
		
		while(lista_iterador_tiene_siguiente(iterador)){	
			
			nodo_aux = lista_iterador_siguiente(iterador);
			
			if(strcmp(clave, nodo_aux->clave) == 0){
				
				if(hash->destructor != NULL){
					hash->destructor(nodo_aux->valor);
				}
				nodo_aux->valor = elemento;
				retorno = EXITO;
			}
		}
		lista_iterador_destruir(iterador);
	}
	return retorno;
}

/*PRE: La funcion debe recibir un puntero a una variable hash_t no nulo.
 *POST: Se retornara un vector dinamico que contendra todos los elementos almacenados en el hash.
 *		En caso de error, se retornara NULL.
 */
nodo_hash_t** obtener_elementos_hash(hash_t* hash){
	
	nodo_hash_t** elementos = NULL;
	int elementos_insertados = 0;
	nodo_hash_t* nodo_aux = NULL;
	
	if(hash){
		elementos = calloc(hash->elementos, sizeof(nodo_hash_t*));

		for(int i = 0; i < hash->capacidad; i++){
			
			lista_iterador_t* iter = lista_iterador_crear(hash->indices[i]);	
			
			while( (lista_iterador_tiene_siguiente(iter)) && (elementos_insertados < hash->elementos) ){
				
				nodo_aux = lista_iterador_siguiente(iter);
				elementos[elementos_insertados] = nodo_aux;
				elementos_insertados++;				
			}
			lista_iterador_destruir(iter);	
		}
		if(elementos_insertados != hash->elementos){
			free(elementos);
			elementos = NULL;
		}
	}
	return elementos;	
}

/*PRE: La funcion debe recibir: un puntero a una variable hash_t, un vector de punteros a listas, y un vector
 *	   a punteros a variables nodo_hash_t no nulos, y un entero positivo o 0 representado la capacidad a la que 	
 *	   se quiere ampliar o reducir las listas del hash.	
 *POST: Se insertaran en los nuevos indices los elementos  del vector de variables nodo_hash_t, y se retornara 0.
 *		en caso de error o falta de memoria se retornara -1.
 */
int insertar_en_nuevos_indices(hash_t* hash, lista_t** nuevos_indices, size_t nueva_capacidad, nodo_hash_t** elementos){

	size_t tamanio = hash->elementos, vieja_capacidad = hash->capacidad;
	lista_t** viejos_indices = hash->indices;
	int i = 0, resultado = ERROR;

	if( (hash) && (nuevos_indices) ){
		hash->indices = nuevos_indices;
		hash->capacidad = nueva_capacidad;
		hash->elementos = 0;
		nodo_hash_t* nodo = NULL;
		
		while(i<tamanio){
			nodo = crear_nodo_hash(elementos[i]->clave, elementos[i]->valor);
			if(nodo){
				insertar_nodo_hash(hash, nodo);
				}
			i++;
		}
		if(hash->elementos == tamanio){
			resultado = EXITO;
			destruir_indices_hash(viejos_indices, vieja_capacidad, NULL);	
		}
		else{
			hash->indices = viejos_indices;
			hash->capacidad = vieja_capacidad;
			hash->elementos = tamanio;
			destruir_indices_hash(nuevos_indices, nueva_capacidad, NULL);
		}
	}
	return resultado;		
}
/*PRE: La funcion debe recibir un puntero a una variable hash_t no nula.
 *POST:	Se ampliara la capacidad del hash ampliando las listas hasta proximo numero primo del doble
 *		de la capacidad actual del hash y se retornara 0. En caso de error por falta de memoria se retornara
 *		-1.
 */
int rehash(hash_t* hash, bool agrandar_hash){

	int resultado = ERROR;
	lista_t** nuevos_indices = NULL;

	if(hash){		
		
		nodo_hash_t** elementos = obtener_elementos_hash(hash);
		size_t nueva_capacidad_hash = (agrandar_hash? obtener_siguiente_primo(hash->capacidad * 2): obtener_siguiente_primo((size_t)(hash->capacidad/2)));
		
		if(elementos){
			
			nuevos_indices = crear_indices_hash(nueva_capacidad_hash, hash->destructor); 		
			resultado = insertar_en_nuevos_indices(hash, nuevos_indices, nueva_capacidad_hash, elementos);
			free(elementos);
		}	
	}	
	return resultado;
}	

int hash_insertar(hash_t* hash, const char* clave, void* elemento){
	
	int retorno = ERROR;
	int resultado_rehash = EXITO;
	
	if( (hash) && (clave) ){
 		
 		if( ((hash->elementos) + 1) >= (hash->capacidad * COEFICIENTE_REHASH_AGRANDAR) ){ 

			resultado_rehash = rehash(hash, true);
		} 
		if( (resultado_rehash == EXITO)  && (hash->indices) ){
			
			if(hash_obtener(hash, clave) == NULL){
				nodo_hash_t* nodo = crear_nodo_hash(clave, elemento);
				if(nodo){
					if(insertar_nodo_hash(hash, nodo) == EXITO){
						retorno = EXITO;
					}	
				}	
			}
			else{
				if(hash_actualizar_valor(hash, clave, elemento) == EXITO){
					retorno = EXITO;
				}
			}	
		}
	}	
	return retorno;
}	 

/*PRE: La funcion debe recibir un puntero a una variable hash_t y un string no nulos.
 *POST: Se retornara el valor asociado a la clave recibida dentro del hash. En caso de que no se halle
 *		un elemento asociado a la clave, o ocurra algun error se retornara NULL.
 *
 */
void* hash_buscar(hash_t* hash, const char* clave){
	
	nodo_hash_t* elemento_aux = NULL;
	void* retorno = NULL;
	bool elemento_encontrado = false; 
	
	if( (hash) && (clave) && (hash->elementos > 0) ){
		
		int posicion = funcion_hasheo(clave, hash->capacidad);

		if(posicion > ERROR){
			
			if(!lista_vacia(hash->indices[posicion])){
				
				lista_iterador_t* iterador_lista = lista_iterador_crear(hash->indices[posicion]);

				while( (lista_iterador_tiene_siguiente(iterador_lista)) && (!elemento_encontrado) ){

					elemento_aux = lista_iterador_siguiente(iterador_lista);
					
					if(strcmp(elemento_aux->clave, clave) == 0){
						retorno = elemento_aux->valor;
						elemento_encontrado = true;
					}
				}
				lista_iterador_destruir(iterador_lista);
			}	
		}	
	}
	return retorno;	
}

void* hash_obtener(hash_t* hash, const char* clave){

	void* valor_elemento  = NULL;

	if((hash) && (clave)){

		valor_elemento = hash_buscar(hash, clave);			
	}
	return valor_elemento;
}

bool hash_contiene(hash_t* hash, const char* clave){
	
	bool contiene = false;

	if( hash_buscar(hash, clave) != NULL){

		contiene = true;
	}   
	return contiene;
}

int hash_quitar(hash_t* hash, const char* clave){

	int resultado = ERROR, resultado_rehash = EXITO;
	
	if( (hash) && (clave) && (hash->elementos > 0) ){
		if( (hash->elementos > 0) && ( ((hash->elementos-1)  * COEFICIENTE_REHASH_ACHICAR) <= hash->capacidad)){
			resultado_rehash = rehash(hash, false);
		}
		int posicion = funcion_hasheo(clave, hash->capacidad);
		if( (posicion > ERROR) && (resultado_rehash == EXITO)){
			lista_iterador_t* iter = lista_iterador_crear(hash->indices[posicion]);
				
				if(iter){
				int posicion_elemento = -1;
				bool elemento_encontrado = false;
				nodo_hash_t* nodo_aux = NULL;

				while( (lista_iterador_tiene_siguiente(iter)) && (!elemento_encontrado) ){

					nodo_aux = lista_iterador_siguiente(iter);
					if(strcmp(nodo_aux->clave, clave) == 0){
						
						elemento_encontrado = true;	
					}
					posicion_elemento++;
				}
				if( (elemento_encontrado) && (nodo_aux) ){
					destruir_elemento_hash(nodo_aux, hash->destructor);
					lista_borrar_de_posicion(hash->indices[posicion], (size_t)posicion_elemento);
					hash->elementos--;
					resultado = EXITO;
				}
			}
			lista_iterador_destruir(iter);		
		}
	}
	return resultado;
}

size_t hash_cantidad(hash_t* hash){

	return ( hash? hash->elementos : 0);
}

void hash_destruir(hash_t* hash){

	if(hash){
		destruir_indices_hash(hash->indices, hash->capacidad, hash->destructor);
		free(hash);		
	}
}
