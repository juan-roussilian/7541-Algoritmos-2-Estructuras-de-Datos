#include "pruebas_hash.h"
#include "lista.h"
#include <string.h>
#include <stdlib.h>

#define EXITO 0
#define ERROR -1
#define PRUEBA_PASADA true
#define PRUEBA_FALLADA false


struct hash{
	lista_t** indices;
	size_t capacidad;
	size_t elementos;
	hash_destruir_dato_t destructor;
};

extern char* strdup(const char*);

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


void destruir_strings(void* string){
	free(string);
}

void verificar_persona(hash_t* hash, const char* dni, bool deberia_existir){
  printf("Verifico la persona empadronada %s: ", dni);
  bool retorno = hash_contiene(hash, dni);
  printf("%s\n", (retorno==deberia_existir)?"SI":"NO");
}

void insertar_persona(hash_t* hash, const char* dni, const char* persona){
	hash_insertar(hash, dni, strdup(persona));
}


void quitar_persona(hash_t* hash, const char* dni){
	hash_quitar(hash, dni);
} 

int main(){

	hash_t* hash = NULL;
	hash_iterador_t* iterador = NULL;

	printf("\nPruebas de casos borde con hash e iterador externo nulos \n\n");

	printf("Insertar devuelve error: %s\n", DadoUnHashNulo_CuandoSeIntentaInsertar_DevuelveERROR(hash)? "SI":"NO");

	printf("Quitar devulve error: %s\n", DadoUnHashNulo_CuandoSeIntentaQuitar_DevuelveERROR(hash)? "SI":"NO");

	printf("Obtener devulve error: %s\n", DadoUnHashNulo_CuandoSeIntentaObtener_DevuelveNULL(hash)? "SI":"NO");

	printf("Cantidad devuelve 0: %s\n", DadoUnHashNulo_CuandoSePreguntaCantidad_Devuelve0(hash)? "SI":"NO");

	printf("Contiene elemento devuelve false: %s\n", DadoUnHashNulo_CuandoSePreguntaSiContieneUnElemento_DevuelveFalse(hash)? "SI":"NO");

	printf("Iterador siguiente devuelve NULL: %s\n", DadoUnIteradorNulo_CuandoSePideSiguiente_DevuelveNULL(iterador)? "SI":"NO");

	printf("Iterador tiene siguiente devuelve false: %s\n", DadoUnIteradorNulo_CuandoSePreguntaSiTieneSiguiente_DevuelveFalse( iterador)? "SI":"NO");

	printf("\nPruebas de casos borde con hash vacio\n\n");

	hash = hash_crear(destruir_strings,4);
	iterador = hash_iterador_crear(hash);

	printf("Quitar devulve error: %s\n", DadoUnHashVacio_CuandoSeIntentaQuitar_DevuelveERROR(hash)? "SI":"NO");

	printf("Obtener devulve error: %s\n", DadoUnHashVacio_CuandoSeIntentaObtener_DevuelveNULL(hash)? "SI":"NO");

	printf("Cantidad devuelve 0: %s\n", DadoUnHashVacio_CuandoSePreguntaCantidad_Devuelve0(hash)? "SI":"NO");

	printf("Contiene elemento devuelve false: %s\n", DadoUnHashVacio_CuandoSePreguntaSiContieneUnElemento_DevuelveFalse(hash)? "SI":"NO");

	printf("Iterador siguiente devuelve NULL: %s\n", DadoUnHashVacio_CuandoSePideIteradorSiguiente_DevuelveNULL(iterador)? "SI":"NO");

	printf("Iterador tiene siguiente devuelve false: %s\n", DadoUnHashVacio_CuandoSePreguntaSiIteradorTieneSiguiente_DevuelveFalse(iterador)? "SI":"NO");

	hash_iterador_destruir(iterador);

	printf("\nInserto 8 personas en hash de capacidad 4\n\n");

	insertar_persona(hash, "42195780", "Persona 1");
	insertar_persona(hash, "42195781", "Persona 2");
	insertar_persona(hash, "42195782", "Persona 3");
	insertar_persona(hash, "42195783", "Persona 4");
	insertar_persona(hash, "42195784", "Persona 5");
	insertar_persona(hash, "42195785", "Persona 6");
	insertar_persona(hash, "42195786", "Persona 7");
	insertar_persona(hash, "42195787", "Persona 8");
	verificar_persona(hash, "42195780", true);
	verificar_persona(hash, "42195781", true);
	verificar_persona(hash, "42195782", true);
	verificar_persona(hash, "42195783", true);
	verificar_persona(hash, "42195784", true);
	verificar_persona(hash, "42195785", true);
	verificar_persona(hash, "42195786", true);
	verificar_persona(hash, "42195787", true);
	
	printf("\nElementos del hash deberia ser 8: %s\n", (hash_cantidad(hash) == 8)? "SI":"NO");
	printf("Capacidad del hash deberia ser  11: %s\n", (hash->capacidad == 11 )? "SI":"NO");
	
	printf("\nVerifico que obtener me devuelve los elementos indicados\n\n");
	printf("Obtener persona 1 : %s\n", (strcmp(hash_obtener(hash,"42195780"), "Persona 1") == 0)? "SI":"NO");
	printf("Obtener persona 2 : %s\n", (strcmp(hash_obtener(hash,"42195781"), "Persona 2") == 0)? "SI":"NO");
	printf("Obtener persona 3 : %s\n", (strcmp(hash_obtener(hash,"42195782"), "Persona 3") == 0)? "SI":"NO");
	printf("Obtener persona 4 : %s\n", (strcmp(hash_obtener(hash,"42195783"), "Persona 4") == 0)? "SI":"NO");
	printf("Obtener persona 5 : %s\n", (strcmp(hash_obtener(hash,"42195784"), "Persona 5") == 0)? "SI":"NO");

	printf("\nImprimo todos los elementos dentro del hash utilizando el iterador\n\n");
	
	iterador = hash_iterador_crear(hash);
	
	while(hash_iterador_tiene_siguiente(iterador)){
    	const char* clave = hash_iterador_siguiente(iterador);
    	if(clave){
      	printf("DNI: %s  PERSONA: %s\n", clave, (char*)hash_obtener(hash, clave));
    	}
  	}
  	hash_iterador_destruir(iterador); 


	printf("\nElimino 7 personas y verifico que no esten en el hash\n\n");
	
	quitar_persona(hash, "42195780");
	quitar_persona(hash, "42195781");
	quitar_persona(hash, "42195782");
	quitar_persona(hash, "42195783");
	quitar_persona(hash, "42195784");
	quitar_persona(hash, "42195785");
	quitar_persona(hash, "42195786");

	verificar_persona(hash, "42195780", false);
	verificar_persona(hash, "42195781", false);
	verificar_persona(hash, "42195782", false);
	verificar_persona(hash, "42195783", false);
	verificar_persona(hash, "42195784", false);
	verificar_persona(hash, "42195785", false);
	verificar_persona(hash, "42195786", false);

	printf("\nElementos del hash deberia ser 1: %s\n", (hash_cantidad(hash) == 1)? "SI":"NO");
	printf("Capacidad del hash deberia ser  7: %s\n", (hash->capacidad == 7 )? "SI":"NO");



	hash_destruir(hash);
	return 0;	
}