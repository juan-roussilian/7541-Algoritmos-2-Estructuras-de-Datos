#include "lista.h"
#include <stdio.h>

#define ERROR -1
#define EXITO 0
#define PRUEBAS_TOTALES 18
#define PRUEBA_PASADA true
#define PRUEBA_FALLADA false

void mostrar_elementos_enteros(void* elemento){
  if(elemento)
    printf("%i ", *(int*)elemento);
}


bool DadaUnaListaNula_CuandoSeIntentaInsertar_DevuelveERROR(lista_t* lista){
	int A = 2;
	return ( (lista_insertar(lista, &A) == ERROR)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaListaNula_CuandoSeIntentaInsertarEnPosicion_DevuelveERROR(lista_t* lista){
	int A = 2;
	return ( (lista_insertar_en_posicion(lista, &A, 0) == ERROR)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaListaNula_CuandoSeIntentaBorrar_DevuelveERROR(lista_t* lista){
	return( (lista_borrar(lista) == ERROR)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaListaNula_CuandoSeIntentaBorrarDePosicion_DevuelveERROR(lista_t* lista){
	return( (lista_borrar_de_posicion(lista, 0) == ERROR)? PRUEBA_PASADA: PRUEBA_FALLADA);
}

bool DadaUnaListaNula_CuandoSePreguntaSiEstaVacia_DevuelveTrue(lista_t* lista){
	return ( lista_vacia(lista)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaListaNula_CuandoSePreguntaLaCantidadDeElementos_Devuelve_0(lista_t* lista){
	return ( (lista_elementos(lista)== 0)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaListaNula_CuandoSePideElUltimoElemento_DevuelveNULL(lista_t* lista){
	return ( (lista_ultimo(lista) == NULL)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaListaNula_CuandoSePideElElementoEnPosicion_DevuelveNULL(lista_t* lista){
	return ( (lista_elemento_en_posicion(lista, 0) == NULL)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaListaVacia_CuandoSeIntentaBorrar_DevuelveERROR(lista_t* lista){
	return ( (lista_borrar(lista) == ERROR)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaListaVacia_CuandoSeIntentaBorrarDePosicion_DevuelveERROR(lista_t* lista){
	return ( (lista_borrar_de_posicion(lista, 25) == ERROR)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaListaVacia_CuandoSePideUnElementoEnPosicion_DevuelveNULL(lista_t* lista){
	return ( (lista_elemento_en_posicion(lista, 0) == NULL)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaListaVacia_CuandoSePreguntaSiEstaVacia_DevuelveTrue(lista_t* lista){
	return ( lista_vacia(lista)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaListaVacia_CuandoSePideElUltimoElemento_DevuelveNULL(lista_t* lista){
	return ( (lista_ultimo(lista) == NULL)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaListaVacia_CuandoInsertoUnElemento_ElementosDevuelve1YUltimoDevuelveElElemento(lista_t* lista, void* elemento){
	bool resultado;
	lista_insertar(lista, elemento);
	resultado = ((lista_elementos(lista) == 1)? PRUEBA_PASADA : PRUEBA_FALLADA);
	resultado = ((lista_ultimo(lista) == elemento)? PRUEBA_PASADA : PRUEBA_FALLADA);
	return resultado;
}

bool DadaUnaListaConUnElemento_CuandoBorroEseElemento_ElementosDevuelve0(lista_t* lista){
	bool resultado;
	lista_borrar(lista);
	resultado = ((lista_elementos(lista) == 0)? PRUEBA_PASADA : PRUEBA_FALLADA);
	return resultado;
}

bool DadoUnIteradorNulo_CuandoSePreguntaSiTieneSiguiente_DevuelveFalse(lista_iterador_t* iterador){
	return ( (lista_iterador_tiene_siguiente(iterador) == false)? PRUEBA_PASADA : PRUEBA_FALLADA);
} 

bool DadoUnIteradorNulo_CuandoSePideQueAvance_DevuelveNULL(lista_iterador_t* iterador){
	return ( (lista_iterador_siguiente(iterador) == NULL)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaListaConUnElemento_CuandoLlamoIteradorSiguiente2VecesSeguidas_DevuelveElElementoYNULL(lista_iterador_t* iterador, void* elemento){
	bool resultado;
	resultado = ((lista_iterador_siguiente(iterador) == elemento)? PRUEBA_PASADA : PRUEBA_FALLADA);
	resultado = ((lista_iterador_siguiente(iterador) == NULL)? PRUEBA_PASADA: PRUEBA_FALLADA);
	return resultado;
} 

void DadaUnaListaVacia_CuandoAgrego5Enteros_SeImprimenTodosConIteradorExterno(lista_t* lista, lista_iterador_t* iterador){
	int A = 15, B = 23, C = 999, D = 15000, E = 0;

	lista_insertar(lista, &E);
	lista_insertar(lista, &A);
	lista_insertar_en_posicion(lista, &D, 80 );
	lista_insertar_en_posicion(lista, &B, 2);
	lista_insertar_en_posicion(lista, &C, 3);

	printf("\nPruebas de caso standard con iterador externo\n");
	printf("\nSe deben imprimir los numeros 0, 15, 23, 99 y 15000 en orden ascendente\n");
	printf("\nElementos en la lista : \n");

	while(lista_iterador_tiene_siguiente(iterador))
    printf("%i ", *(int*)lista_iterador_siguiente(iterador));
  	printf("\n");
  	while (!lista_vacia(lista)){
  		lista_borrar(lista);
  	}
}

void DadaUnaListaVacia_CuandoAgrego5Enteros_SeImprimenTodosConIteradorInterno(lista_t* lista,  void (*funcion)(void*)){
	int A = 15, B = 23, C = 999, D = 15000, E = 0;

	lista_insertar(lista, &E);
	lista_insertar(lista, &A);
	lista_insertar_en_posicion(lista, &D, 80 );
	lista_insertar_en_posicion(lista, &B, 2);
	lista_insertar_en_posicion(lista, &C, 3);
	
	printf("\nPruebas de caso standard con iterador interno\n");
	printf("\nSe deben imprimir los mismos numeros de la prueba anterior en el mismo orden:\n");
	printf("\nElementos en la lista : \n");
    lista_con_cada_elemento(lista, funcion);
    printf("\n\n"); 
}

bool DadaUnaListaCon5Enteros_CuandoBorroTodosLosElementos_LaCantidadDeElementosEs0(lista_t* lista){
	while(!lista_vacia(lista))
		lista_borrar(lista);
	return (lista_vacia(lista));
}


int main (){
	int contador = 0;
	char elemento = 'X';
	lista_t* lista = NULL;
	lista_iterador_t* iterador = NULL;

	if(DadaUnaListaNula_CuandoSeIntentaInsertar_DevuelveERROR(lista)){
		printf("Pasaste la prueba 1\n");
		contador++;
	}

	if(DadaUnaListaNula_CuandoSeIntentaInsertarEnPosicion_DevuelveERROR(lista)){
		printf("Pasaste la prueba 2\n");
		contador++;
	}

	if(DadaUnaListaNula_CuandoSeIntentaBorrar_DevuelveERROR(lista)){
		printf("Pasaste la prueba 3\n");
		contador++;
	}

	if(DadaUnaListaNula_CuandoSeIntentaBorrarDePosicion_DevuelveERROR(lista)){
		printf("Pasaste la prueba 4\n");
		contador++;
	}
	if(DadaUnaListaNula_CuandoSePreguntaSiEstaVacia_DevuelveTrue(lista)){
		printf("Pasaste la prueba 5\n");
		contador++;
	}
	if(DadaUnaListaNula_CuandoSePreguntaLaCantidadDeElementos_Devuelve_0(lista)){
		printf("Pasaste la prueba 6\n");
		contador++;
	}
	if(DadaUnaListaNula_CuandoSePideElUltimoElemento_DevuelveNULL(lista)){
		printf("Pasaste la prueba 7\n");
		contador++;
	}
	if(DadaUnaListaNula_CuandoSePideElElementoEnPosicion_DevuelveNULL(lista)){
		printf("Pasaste la prueba 8\n");
		contador++;
	}

	if(DadoUnIteradorNulo_CuandoSePreguntaSiTieneSiguiente_DevuelveFalse(iterador)){
		printf("Pasaste la prueba 9\n");
		contador++;
	}

	if(DadoUnIteradorNulo_CuandoSePideQueAvance_DevuelveNULL(iterador)){
		printf("Pasaste la prueba 10\n");
		contador++;
	}

	lista = lista_crear();

	if(DadaUnaListaVacia_CuandoSePreguntaSiEstaVacia_DevuelveTrue(lista)){
		printf("Pasaste la prueba 11\n");
		contador++;
	}

	if(DadaUnaListaVacia_CuandoSeIntentaBorrarDePosicion_DevuelveERROR(lista)){
		printf("Pasaste la prueba 12\n");
		contador++;
	}

	if(DadaUnaListaVacia_CuandoSeIntentaBorrar_DevuelveERROR(lista)){
		printf("Pasaste la prueba 13\n");
		contador++;
	}

	if(DadaUnaListaVacia_CuandoSePideUnElementoEnPosicion_DevuelveNULL(lista)){
		printf("Pasaste la prueba 14\n");
		contador++;
	}

	if(DadaUnaListaVacia_CuandoSePideElUltimoElemento_DevuelveNULL(lista)){
		printf("Pasaste la prueba 15\n");
		contador++;
	}

	if(DadaUnaListaVacia_CuandoInsertoUnElemento_ElementosDevuelve1YUltimoDevuelveElElemento(lista, &elemento)){
		printf("Pasaste la prueba 16\n");
		contador++;
	}
	
	iterador = lista_iterador_crear(lista);
	
	if(DadaUnaListaConUnElemento_CuandoLlamoIteradorSiguiente2VecesSeguidas_DevuelveElElementoYNULL(iterador, &elemento)){
		printf("Pasaste la prueba 17\n");
		contador++;
	}

	if(DadaUnaListaConUnElemento_CuandoBorroEseElemento_ElementosDevuelve0(lista)){
		printf("Pasaste la prueba 18\n");
		contador++;
	}

	printf("\nPruebas de casos bordes pasadas: %i/%i \n\n", contador, PRUEBAS_TOTALES );

	lista_iterador_t* it = lista_iterador_crear(lista);

	DadaUnaListaVacia_CuandoAgrego5Enteros_SeImprimenTodosConIteradorExterno(lista, it);
	DadaUnaListaVacia_CuandoAgrego5Enteros_SeImprimenTodosConIteradorInterno(lista, mostrar_elementos_enteros);
	
	lista_iterador_destruir(it);
	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}