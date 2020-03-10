#include "hash.h"
#include "hash_iterador.h"
#include <stdio.h>
#include <stdbool.h>


//Pruebas con hash e iterador nulos.

bool DadoUnHashNulo_CuandoSeIntentaInsertar_DevuelveERROR(hash_t* hash);

bool DadoUnHashNulo_CuandoSeIntentaQuitar_DevuelveERROR(hash_t* hash);

bool DadoUnHashNulo_CuandoSeIntentaObtener_DevuelveNULL(hash_t* hash);

bool DadoUnHashNulo_CuandoSePreguntaCantidad_Devuelve0(hash_t* hash);

bool DadoUnHashNulo_CuandoSePreguntaSiContieneUnElemento_DevuelveFalse(hash_t* hash);

bool DadoUnIteradorNulo_CuandoSePideSiguiente_DevuelveNULL(hash_iterador_t* iterador);

bool DadoUnIteradorNulo_CuandoSePreguntaSiTieneSiguiente_DevuelveFalse(hash_iterador_t* iterador);


//Pruebas con hash vacio

bool DadoUnHashVacio_CuandoSeIntentaQuitar_DevuelveERROR(hash_t* hash);

bool DadoUnHashVacio_CuandoSeIntentaObtener_DevuelveNULL(hash_t* hash);

bool DadoUnHashVacio_CuandoSePreguntaCantidad_Devuelve0(hash_t* hash);

bool DadoUnHashVacio_CuandoSePreguntaSiContieneUnElemento_DevuelveFalse(hash_t* hash);

bool DadoUnHashVacio_CuandoSePideIteradorSiguiente_DevuelveNULL(hash_iterador_t* iterador);

bool DadoUnHashVacio_CuandoSePreguntaSiIteradorTieneSiguiente_DevuelveFalse(hash_iterador_t* iterador);
