#include "abb.h"
#include <stdio.h>
#include <stdbool.h>

//Pruebas con arbol nulo.

bool DadoUnArbolNulo_CuandoSeIntentaInsertar_DevuelveERROR(abb_t* arbol);

bool DadoUnArbolNulo_CuandoSeIntentaBorrar_DevuelveERROR(abb_t* arbol);

bool DadoUnArbolNulo_CuandoSeIntentaBuscar_DevuelveNULL(abb_t* arbol);

bool DadoUnArbolNulo_CuandoSePreguntaSiEstaVacio_DevuelveTrue(abb_t* arbol);

bool DadoUnArbolNulo_CuandoSePideLaRaiz_DevuelveNULL(abb_t* arbol);

bool DadoUnArbolNulo_CuandoRecorroPreorden_Devuelve0ElementosLlenadosEnElVector(abb_t* arbol);

bool DadoUnArbolNulo_CuandoRecorroInorden_Devuelve0ElementosLlenadosEnElVector(abb_t* arbol);

bool DadoUnArbolNulo_CuandoRecorroPostordenDevuelve0ElementosLlenadosEnElVector(abb_t* arbol);

//Pruebas con arbol vacio

bool DadoUnArbolVacio_CuandoSeIntentaBorrar_DevuelveERROR(abb_t* arbol);

bool DadoUnArbolVacio_CuandoSeIntentaBuscar_DevuelveNULL(abb_t* arbol);

bool DadoUnArbolVacio_CuandoSePreguntaSiEstaVacio_DevuelveTrue(abb_t* arbol);

bool DadoUnArbolVacio_CuandoSePideLaRaiz_DevuelveNULL(abb_t* arbol);

bool DadoUnArbolVacio_CuandoRecorroPreorden_Devuelve0ElementosLlenadosEnElVector(abb_t* arbol);

bool DadoUnArbolVacio_CuandoRecorroInorden_Devuelve0ElementosLlenadosEnElVector(abb_t* arbol);

bool DadoUnArbolVacio_CuandoRecorroPostordenDevuelve0ElementosLlenadosEnElVector(abb_t* arbol);