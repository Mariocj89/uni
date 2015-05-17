/**
@file meses.h                                                                       x
@brief header de la clase Meses                                                     x
@author  Mario Corchero Jiménez                                                     x
@date   15/05/08                                                                    x
@par Descripción:                                                                   x
        Este archivo contiene la especificacion de la clase Meses, con sus atributos, los headers de todos sus metodos
	y la cabecera de un modulo de prueba.
@par Utilización:
	Para utilizar esta clase, solo hay que añadir este archivo con <#include "meses.h"> al principio del fichero y definir
	cualquier variable con esta clase, y para usar el modulo de prueba basta con llamar a PruebaMeses()
@par Plataforma
        Linux.
@par Creado en KDevelop.
*/


#ifndef MESES_H
#define MESES_H

#include <iostream>
#include <fstream>

using namespace std;

const int MAXCAD=15;//Tamaño maximo ke puede tener un mes.

typedef char TipoIdioma[MAXCAD];

typedef struct TipoDato{
	int Numero;//El numero del mes
	TipoIdioma Idioma[2];//En el 0 guardaremos el nombre en castellano y en el 1 en ingles.
};

typedef struct TNodo {
	TipoDato dato;
	TNodo *suce;//Apuntador al siguiente nodo
};

typedef TNodo *PtrNodo;

/**
 * Clase DatosPersonales, almacena la informacion relativa a los meses en una lista enlazada. Sus atributos son:
 *    - l:  puntero que apunta a un TNodo, el comienzo de la lista.
 */
class Meses {
		PtrNodo l; // apuntador al primer elemento de la lista
		
	public:

   /**
    * @brief Constructor por defecto de la clase DatosPersonales.
    */
	Meses();


   /**
    * @brief Copia la clase meses
    * @pre dat debe estar correctamente inicializado, con 12 meses, siendo el primer mes 1 y el ultimo el 12.
    * @param dat: Tipo meses de donde se copiara la configuracion
    */
	void Clonar(const Meses &dat);

   /**
    * @brief Inserta un elemento al principio
    * @pre La clase debe estar inicializada.
    * @param dat: TipoDato que se insertara en la lista
    */
	void InsertarPrincipio(const TipoDato &dat);

   /**
    * @brief Inserta un elemento al final
    * @pre La clase debe estar inicializada.
    * @param dat: TipoDato que se insertara en la lista.
    */
	void InsertarFinal(const TipoDato &dat);

   /**
    * @brief Inserta un elemento de forma ordenada
    * @pre La clase debe estar inicializada y ordenada.
    * @param dat: TipoDato que se insertara en la lista.
    */
	void InsertarOrden(const TipoDato &dat);

   /**
    * @brief Muestra toda la lista
    * @pre La clase debe estar inicializada.
    */
	void Mostrar() const;

   /**
    * @brief Borra un elemento de la lista
    * @pre La clase debe estar inicializada.
    * @param i: Entero que indica el elemento que se borrara de la lista.
    * @return true si lo ha borrado correctamente, false en caso contrario.
    */
	bool Borrar(const int &i);

   /**
    * @brief Busca un elemento en la lista
    * @pre La clase debe estar inicializada.
    * @param dat: TipoDato donde se copiara el elemento encontrado.
    * @param i: Entero usado para buscar el elemento.
    * @return true si lo ha encontrado, false en caso contrario.
    */
	bool Buscar(const int i, TipoDato &dat) const;

   /**
    * @brief Carga la lista de un archivo ("meses.txt")
    * @pre Debe existir el archivo y tener el formato esperado
    */
	void Cargar();

   /**
    * @brief Vacia la lista
    */
	void Eliminar();

   /**
    * @brief Destructor de la clase
    */
	~Meses();
};


   /**
    * @brief Juego de pruebas para la clase Meses
    */
void PruebaMeses();









#endif

