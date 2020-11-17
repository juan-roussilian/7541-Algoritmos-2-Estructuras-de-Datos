#include "pruebas_hash.h"
#define EXITO 0
#define ERROR -1
#define PRUEBA_PASADA true
#define PRUEBA_FALLADA false


bool DadoUnHashNulo_CuandoSeIntentaInsertar_DevuelveERROR(hash_t* hash){

	bool resultado = PRUEBA_FALLADA;
	
	if(hash_insertar(hash,"0", NULL) == ERROR){
		resultado = PRUEBA_PASADA;
	}

	return resultado;
}

bool DadoUnHashNulo_CuandoSeIntentaQuitar_DevuelveERROR(hash_t* hash){

	bool resultado = PRUEBA_FALLADA;

	if(hash_quitar(hash, "0") == ERROR){
		resultado = PRUEBA_PASADA;
	}

	return resultado;
}

bool DadoUnHashNulo_CuandoSeIntentaObtener_DevuelveNULL(hash_t* hash){

	bool resultado = PRUEBA_FALLADA;

	if(hash_obtener(hash,"0") == NULL){

		resultado = PRUEBA_PASADA;
	}

	return resultado;
}

bool DadoUnHashNulo_CuandoSePreguntaCantidad_Devuelve0(hash_t* hash){

	bool resultado = PRUEBA_FALLADA;

	if(hash_cantidad(hash) == 0){
		resultado = PRUEBA_PASADA;
	}

	return resultado;
}

bool DadoUnHashNulo_CuandoSePreguntaSiContieneUnElemento_DevuelveFalse(hash_t* hash){

	bool resultado = PRUEBA_FALLADA;

	if(hash_contiene(hash, "0") == false){
		resultado = PRUEBA_PASADA;
	}

	return resultado;
}

bool DadoUnIteradorNulo_CuandoSePideSiguiente_DevuelveNULL(hash_iterador_t* iterador){

	bool resultado = PRUEBA_FALLADA;

	if(hash_iterador_siguiente(iterador) == NULL){
		resultado = PRUEBA_PASADA;
	}

	return resultado;
}

bool DadoUnIteradorNulo_CuandoSePreguntaSiTieneSiguiente_DevuelveFalse(hash_iterador_t* iterador){

	bool resultado = PRUEBA_FALLADA;

	if(hash_iterador_tiene_siguiente(iterador) == false){
		resultado = PRUEBA_PASADA;
	}

	return resultado;
}

bool DadoUnHashVacio_CuandoSeIntentaQuitar_DevuelveERROR(hash_t* hash){

	bool resultado = PRUEBA_FALLADA;

	if(hash_quitar(hash, "0") == ERROR){
		resultado = PRUEBA_PASADA;
	}

	return resultado;
}

bool DadoUnHashVacio_CuandoSeIntentaObtener_DevuelveNULL(hash_t* hash){

	bool resultado = PRUEBA_FALLADA;

	if(hash_obtener(hash,"0") == NULL){

		resultado = PRUEBA_PASADA;
	}

	return resultado;
}

bool DadoUnHashVacio_CuandoSePreguntaCantidad_Devuelve0(hash_t* hash){

	bool resultado = PRUEBA_FALLADA;

	if(hash_cantidad(hash) == 0){
		resultado = PRUEBA_PASADA;
	}

	return resultado;
}

bool DadoUnHashVacio_CuandoSePreguntaSiContieneUnElemento_DevuelveFalse(hash_t* hash){

	bool resultado = PRUEBA_FALLADA;

	if(hash_contiene(hash, "0") == false){
		resultado = PRUEBA_PASADA;
	}

	return resultado;
}

bool DadoUnHashVacio_CuandoSePideIteradorSiguiente_DevuelveNULL(hash_iterador_t* iterador){

	bool resultado = PRUEBA_FALLADA;

	if(hash_iterador_siguiente(iterador) == NULL){
		resultado = PRUEBA_PASADA;
	}

	return resultado;
}

bool DadoUnHashVacio_CuandoSePreguntaSiIteradorTieneSiguiente_DevuelveFalse(hash_iterador_t* iterador){

	bool resultado = PRUEBA_FALLADA;

	if(hash_iterador_tiene_siguiente(iterador) == false){
		resultado = PRUEBA_PASADA;
	}

	return resultado;
}
