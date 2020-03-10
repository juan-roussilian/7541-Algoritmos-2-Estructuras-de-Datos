#include "cola.h"
#include <stdio.h>

#define ERROR -1
#define EXITO 0
#define PRUEBA_PASADA true
#define PRUEBA_FALLADA false
#define PRUEBAS_TOTALES 9


bool DadaUnaColaNula_CuandoSeIntentaEncolar_DevuelveERROR(cola_t* cola){
	int A = 2;
	return ( ((cola, &A) == ERROR)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaColaNula_CuandoSeIntentaDesencolar_DevuelveERROR(cola_t* cola){
	return ( (cola_desencolar(cola) == ERROR)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaColaNula_CuandoSePreguntaSiEstaVacia_DevuelveTrue(cola_t* cola){
	return ( cola_vacia(cola)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaColaNula_CuandoSePreguntaLaCantidadDeElementos_Devuelve_0(cola_t* cola){
	return ( (cola_cantidad(cola)== 0)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaColaNula_CuandoSePideElPrimerElemento_DevuelveNULL(cola_t* cola){
	return ( (cola_primero(cola) == NULL)? PRUEBA_PASADA: PRUEBA_FALLADA);
}

bool DadaUnaColaVacia_CuandoSeIntentaDesencolar_DevuelveERROR(cola_t* cola){
	return ( (cola_desencolar(cola) == ERROR)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaColaVacia_CuandoSePreguntaSiEstaVacia_DevuelveTrue(cola_t* cola){
	return ( cola_vacia(cola)? PRUEBA_PASADA : PRUEBA_FALLADA);
}

bool DadaUnaColaVacia_CuandoSePideElPrimerElemento_DevuelveNULL(cola_t* cola){
	return ( (cola_primero(cola) == NULL)? PRUEBA_PASADA: PRUEBA_FALLADA);
}

bool DadaUnaColaVacia_CuandoSeEncolanYdDesencolan10Elementos_DevuelveCantidad10YCantidad0_VaciaFalseYVaciaTrue_YlosElementos(cola_t* cola){
	printf("\nIniciando ultima prueba\n");
	int A=2, B=1, C=9, D=7,E=-1, F=0, G=11, H=5, I=8, J=6;

	cola_encolar(cola, (void*)&A);
	cola_encolar(cola, (void*)&B);
	cola_encolar(cola, (void*)&C);
	cola_encolar(cola, (void*)&D);
	cola_encolar(cola, (void*)&E);
	cola_encolar(cola, (void*)&F);
	cola_encolar(cola, (void*)&G);
	cola_encolar(cola, (void*)&H);
	cola_encolar(cola, (void*)&I);
	cola_encolar(cola, (void*)&J);

	if ( (cola_cantidad(cola) == 10) && (!cola_vacia(cola)) ){
		printf("La cola no esta Vacia\n");
		printf("Desencolando elementos...\n\n");
		
		while(!cola_vacia(cola)){
			printf(" %i\n", *(int*)cola_primero(cola) );
			cola_desencolar(cola);
		}

		if(cola_vacia(cola)){
			printf("\nLa cola esta Vacia\n");
			return PRUEBA_PASADA;
		}	
	}

	return PRUEBA_FALLADA;	
}

int main (){

	int contador = 0;
	cola_t* cola = NULL;

	if (DadaUnaColaNula_CuandoSeIntentaDesencolar_DevuelveERROR(cola)){
		printf("Pasaste la prueba 1\n");
		contador++;
	}
	if (DadaUnaColaNula_CuandoSeIntentaEncolar_DevuelveERROR(cola)){
		printf("Pasaste la prueba 2\n");
		contador++;
	}
	if (DadaUnaColaNula_CuandoSePideElPrimerElemento_DevuelveNULL(cola)){
		printf("Pasaste la prueba 3\n");
		contador++;
	}
	if (DadaUnaColaNula_CuandoSePreguntaSiEstaVacia_DevuelveTrue(cola)){
		printf("Pasaste la prueba 4\n");
		contador++;
	}
	if (DadaUnaColaNula_CuandoSePreguntaLaCantidadDeElementos_Devuelve_0(cola)){
		printf("Pasaste la prueba 5\n");
		contador++;
	}
	
	cola = cola_crear();

	if(DadaUnaColaVacia_CuandoSeIntentaDesencolar_DevuelveERROR(cola)){
		printf("Pasaste la prueba 6\n");
		contador++;
	}
	if (DadaUnaColaVacia_CuandoSePreguntaSiEstaVacia_DevuelveTrue(cola)){
		printf("Pasaste la prueba 7\n");
		contador++;
	}
	if (DadaUnaColaVacia_CuandoSePideElPrimerElemento_DevuelveNULL(cola)){
		printf("Pasaste la prueba 8\n");
		contador++;
	}
	
	if ( DadaUnaColaVacia_CuandoSeEncolanYdDesencolan10Elementos_DevuelveCantidad10YCantidad0_VaciaFalseYVaciaTrue_YlosElementos(cola)){
		printf("\nPasaste la prueba 9\n");
		contador++;
	}

	printf("Pruebas pasadas %i/%i \n\n\n", contador, PRUEBAS_TOTALES );

	cola_destruir(cola);
	return 0;
}	
