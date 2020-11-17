#include "pila.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define EXITO 0
#define PRUEBA_PASADA true
#define PRUEBA_FALLADA false
#define PRUEBAS_TOTALES 5

bool DadaUnaPilaVacia_CuandoSePideElElementoTope_DevuelveNULL(pila_t* pila){
	if (pila_tope(pila) == NULL )
		return PRUEBA_PASADA;
	else 
		return PRUEBA_FALLADA;
}

bool DadaUnaPilaNula_CuandoSeIntentaApilarYDesapilar_DevuelveERROR(pila_t* pila){
	int elemento = 200;
	if ( (pila_apilar(pila, &elemento) == ERROR) && (pila_desapilar(pila) == ERROR) )
		return PRUEBA_PASADA;
	else 
		return PRUEBA_FALLADA;	
}

bool DadaUnaPilaNula_CuandoSePideTopeYCantidad_DevuelveERROR(pila_t* pila){
	if ( (pila_tope(pila) == NULL) &&  (pila_cantidad(pila) == EXITO ) )
		return PRUEBA_PASADA;
	else 
		return PRUEBA_FALLADA;
}

bool DadaUnaPilaVacia_CuandoSeApilan15Elementos_DevuelveCantidad15(pila_t* pila){
	
	if (pila == NULL)
		return PRUEBA_FALLADA;

	int elemento1 = 23;
	pila_apilar(pila, &elemento1); 
	int elemento2 = 4;
	pila_apilar(pila, &elemento2);
	int elemento3 = 35;
	pila_apilar(pila, &elemento3);
	int elemento4 = 17;
	pila_apilar(pila, &elemento4);
	int elemento5 = -1;
	pila_apilar(pila, &elemento5);
	char elemento6 = 'a';
	pila_apilar(pila, &elemento6);  
	char elemento7 = 'B';
	pila_apilar(pila, &elemento7);
	char elemento8 = '0';
	pila_apilar(pila, &elemento8);
	char elemento9 = 'p';
	pila_apilar(pila,&elemento9);
	char elemento10 = 'r';
	pila_apilar(pila,&elemento10);
	double elemento11 = 2.0;
	pila_apilar(pila,&elemento11);
	double elemento12 = 1.92;
	pila_apilar(pila,&elemento12);
	double elemento13 = 1.87;
	pila_apilar(pila,&elemento13);
	double elemento14 = 1.478;
	pila_apilar(pila,&elemento14);
	double elemento15 = 123.2;
	pila_apilar(pila,&elemento15);

	if(pila->tope == 15)
		return PRUEBA_PASADA;
	else 
		return PRUEBA_FALLADA;

}

bool DadaUnaPilaCon15Elementos_CuandoSeDesapilan15Elementos_Devuelve0(pila_t* pila){

	if (pila == NULL)
		return PRUEBA_FALLADA;

	bool pudo_desapilar = true;

	while(!pila_vacia(pila) && (pudo_desapilar)){
		
		if(pila_desapilar(pila)!=0){
			pudo_desapilar = false;
		}
	}
	
	if(pila_cantidad(pila) == 0)
		return PRUEBA_PASADA;
	else
		return PRUEBA_FALLADA;
}


int main(){
	
	pila_t* pila = NULL;
	int pruebas_pasadas = 0;

	if (DadaUnaPilaNula_CuandoSePideTopeYCantidad_DevuelveERROR(pila)){
		pruebas_pasadas++;
		printf("Pasaste la prueba 1\n");
	}
	if (DadaUnaPilaNula_CuandoSeIntentaApilarYDesapilar_DevuelveERROR(pila)){
		pruebas_pasadas++;
		printf("Pasaste la prueba 2\n");
	
	}
	pila = pila_crear ();

	if (DadaUnaPilaVacia_CuandoSePideElElementoTope_DevuelveNULL(pila)){
		pruebas_pasadas++;
		printf("Pasaste la prueba 3\n");
	
	}
	if (DadaUnaPilaVacia_CuandoSeApilan15Elementos_DevuelveCantidad15(pila)){
		pruebas_pasadas++;
		printf("Pasaste la prueba 4\n");
	
	}

	if (DadaUnaPilaCon15Elementos_CuandoSeDesapilan15Elementos_Devuelve0(pila)){
		pruebas_pasadas++;
		printf("Pasaste la prueba 5\n");
	
	}
	printf ("Pruebas pasadas: %i/%i\n", pruebas_pasadas, PRUEBAS_TOTALES);

	pila_destruir(pila);
}

