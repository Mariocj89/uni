//Fichero auxiliar para el proyecto MOZART
//Este se encarga de producir el sonido, subir escala, establecer el tempo...

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Variable que contiene el tempo actual.
int tempo;

//Variable que contiene la escala actual
float escala;

//Cambia el valor de la escala actual
void setEscala(const int cambio){
	escala*= pow(2,cambio);
}

//Emite un pitido en funcion de la escala, el tempo y los parametros
void beep(const float nota, const float duracion){
	char comando[100];
	sprintf(comando,"sudo beep -f %f -l %d \n",escala*nota,(int)(tempo*duracion));
	system(comando);
}

//Cambia el tempo actual
void setTempo(const int newTempo){
	tempo = newTempo;
	//printf("El tempo se establece en: %d milisegundos\\negra.\n",tempo);
}

//Imprime una cadena por patanlla
void pintaCadena(const char* cadena){
     system("clear\n");
     printf("\n\n\n\n\n\n\n\n\n********************************************************************************\n");
     printf("%s\n", cadena);
     printf("********************************************************************************\n");
}
