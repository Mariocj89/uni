/**
* \file genaleatorios.cpp
* \brief Implementación de la clase GenAleatorios
* \author
*   \b Profesores LPII \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#include "genaleatorios.h"

// Inicialización de la única instancia de la clase que existe
GenAleatorios* GenAleatorios::instancia = NULL;

/**
* Constructor por defecto. Inicializa un objeto de tipo GenAleatorio
* \return Devuelve un objeto de tipo GenAleatorio inicializado
*/
GenAleatorios::GenAleatorios(){
	// Inicialización de la semilla para generar los números aleatorios
  	srand(this->SEMILLA);
	// Inicialización del atributo que cuenta cuántos números aleatorios se han generado
	numGenerados = 0;
}

/**
* Metodo generarNumero. Genera un número aleatorio entre 0 y (limiteRango-1)
* \param "limiteRango" Límite del rango entre el que se genera el número aleatorio
* \return Devuelve el número aleatorio generado
*/
int GenAleatorios::generarNumero(int limiteRango){
	if (instancia == NULL) instancia = new GenAleatorios;
	instancia->numGenerados++;
  	return (rand() % limiteRango);
}

/**
* Metodo numerosGenearados. Devuelve el número de números aleatorios que se han generado
* \param "" No recibe parámetros
* \return Devuelve el contador de números aleatorios generados
*/
int GenAleatorios::numerosGenerados(){
	if (instancia == NULL) instancia = new GenAleatorios;
	return instancia->numGenerados;
}

/**
* Metodo destruir. Detruye la única instancia de tipo GenAleatorios que existe
* \param "" No recibe parámetros
* \return No devuelve nada
*/
void GenAleatorios::destruir(){
	if (instancia != NULL) delete instancia;
// 	cout << "- Destruyendo instancia generador aleatorios -" << endl;
	instancia = NULL;
}

/**
* Destructor. Destructor de la clase
* \param "" No recibe parámetros
* \return No devuelve nada
*/
GenAleatorios::~GenAleatorios()
{
}


