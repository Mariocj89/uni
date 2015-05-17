/**
* \file genaleatorios.h
* \brief Implementación de la clase GenAleatorios
* \author
*   \b Profesores LPII \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/


#ifndef GENALEATORIOS_H
#define GENALEATORIOS_H

#include <iostream>

using namespace std; 


/**
* \class GenAleatorios
* \brief Permite generar números aleatorios dentro de un rango determinado
*
*/
class GenAleatorios{
	static const int SEMILLA=1976;		//!< Semilla para inicializar la generación de números aleatorios
	int numGenerados;					//!< Contador de números aleatorios generados
	static GenAleatorios* instancia;	//!< Instancia de la propia clase (sólo habrá una en el sistema)
    GenAleatorios();					
    ~GenAleatorios();
public:
	static int generarNumero(int limiteRango);
	static int numerosGenerados();
	static void destruir();
};

#endif
