#include "pruebas_abb.h"
#include "abb.h"
#include <stdlib.h>

#define ERROR -1
#define EXITO 0
#define PRUEBA_PASADA true
#define PRUEBA_FALLADA false


bool DadoUnArbolNulo_CuandoSeIntentaInsertar_DevuelveERROR(abb_t* arbol){
	
	bool resultado = PRUEBA_FALLADA;
	
	if(!arbol){
		
		if (arbol_insertar(arbol, NULL) == ERROR){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}

bool DadoUnArbolNulo_CuandoSeIntentaBorrar_DevuelveERROR(abb_t* arbol){
		
	bool resultado = PRUEBA_FALLADA;
	
	if(!arbol){
		
		if (arbol_borrar(arbol, NULL) == ERROR){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}

bool DadoUnArbolNulo_CuandoSeIntentaBuscar_DevuelveNULL(abb_t* arbol){

	bool resultado = PRUEBA_FALLADA;
	
	if(!arbol){
		
		if(arbol_buscar(arbol, NULL) == NULL){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}

bool DadoUnArbolNulo_CuandoSePreguntaSiEstaVacio_DevuelveTrue(abb_t* arbol){

	bool resultado = PRUEBA_FALLADA;
	
	if(!arbol){
		
		if(arbol_vacio(arbol) == true){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}

bool DadoUnArbolNulo_CuandoSePideLaRaiz_DevuelveNULL(abb_t* arbol){
	
	bool resultado = PRUEBA_FALLADA;
	
	if(!arbol){
		
		if(arbol_raiz(arbol) == NULL){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}

bool DadoUnArbolNulo_CuandoRecorroPreorden_Devuelve0ElementosLlenadosEnElVector(abb_t* arbol){

	bool resultado = PRUEBA_FALLADA;
	void* array[10];
	int tamanio = 10;
	
	if(!arbol){
		
		if(arbol_recorrido_preorden(arbol, array, tamanio) == 0){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}

bool DadoUnArbolNulo_CuandoRecorroInorden_Devuelve0ElementosLlenadosEnElVector(abb_t* arbol){

	bool resultado = PRUEBA_FALLADA;
	void* array[10];
	int tamanio = 10;
	
	if(!arbol){
		
		if(arbol_recorrido_inorden(arbol, array, tamanio) == 0){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;

}

bool DadoUnArbolNulo_CuandoRecorroPostordenDevuelve0ElementosLlenadosEnElVector(abb_t* arbol){

	bool resultado = PRUEBA_FALLADA;
	void* array[10];
	int tamanio = 10;
	
	if(!arbol){
		
		if(arbol_recorrido_postorden(arbol, array, tamanio) == 0){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}

//Pruebas con arbol vacio

bool DadoUnArbolVacio_CuandoSeIntentaBorrar_DevuelveERROR(abb_t* arbol){

	bool resultado = PRUEBA_FALLADA;
	
	if(arbol ){	
		if (arbol_borrar(arbol, NULL) == ERROR){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}

bool DadoUnArbolVacio_CuandoSeIntentaBuscar_DevuelveNULL(abb_t* arbol){
	
	bool resultado = PRUEBA_FALLADA;
	
	if(arbol){
		
		if(arbol_buscar(arbol, NULL) == NULL){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}

bool DadoUnArbolVacio_CuandoSePreguntaSiEstaVacio_DevuelveTrue(abb_t* arbol){

	bool resultado = PRUEBA_FALLADA;
	
	if(arbol){
		
		if(arbol_vacio(arbol) == true){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}

bool DadoUnArbolVacio_CuandoSePideLaRaiz_DevuelveNULL(abb_t* arbol){

	bool resultado = PRUEBA_FALLADA;
	
	if(arbol){
		
		if(arbol_raiz(arbol) == NULL){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}

bool DadoUnArbolVacio_CuandoRecorroPreorden_Devuelve0ElementosLlenadosEnElVector(abb_t* arbol){

	bool resultado = PRUEBA_FALLADA;
	void* array[10];
	int tamanio = 10;
	
	if(arbol){
		
		if(arbol_recorrido_preorden(arbol, array, tamanio) == 0){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}

bool DadoUnArbolVacio_CuandoRecorroInorden_Devuelve0ElementosLlenadosEnElVector(abb_t* arbol){

	bool resultado = PRUEBA_FALLADA;
	void* array[10];
	int tamanio = 10;
	
	if(arbol){
		
		if(arbol_recorrido_inorden(arbol, array, tamanio) == 0){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}

bool DadoUnArbolVacio_CuandoRecorroPostordenDevuelve0ElementosLlenadosEnElVector(abb_t* arbol){

	bool resultado = PRUEBA_FALLADA;
	void* array[10];
	int tamanio = 10;
	
	if(arbol){
		
		if(arbol_recorrido_postorden(arbol, array, tamanio) == 0){
			resultado = PRUEBA_PASADA;
		}
	}
	return resultado;
}