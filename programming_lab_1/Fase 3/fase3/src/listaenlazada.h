/**
@file listaenlazada.h                                                                 x
@brief header de la clase ListaEnlazada                                             x
@author  Mario Corchero Jiménez                                                     x
@date   15/05/08                                                                    x
@par Descripción:                                                                   x
        Este archivo contiene la especificacion de la clase ListaEnlazada, con sus atributos, los headers de todos sus metodos
	y la cabecera de un modulo de prueba.
@par Utilización:
	Para utilizar esta clase, solo hay que añadir este archivo con <#include "listaenlazada.h"> al principio del fichero y
	definir cualquier variable con esta clase, y para usar el modulo de prueba basta con llamar a Prueba_ListaEnlazada()
@par Plataforma
        Linux.
@par Creado en KDevelop.
*/


#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H


#include "datospersonales.h"

typedef struct TipoNodo {
	DatosPersonales dato;
	TipoNodo *suce;//Apuntador al siguiente nodo
};

typedef TipoNodo *PNodo;

/**
 * Clase DatosPersonales, almacena la informacion relativa a los meses en una lista enlazada. Sus atributos son:
 *    - l:  puntero que apunta a un TipoNodo, el comienzo de la lista.
 *    - M:  Tipo Meses, contiene la informacion relativa a los meses.
 */
class ListaEnlazada {
		PNodo l; // apuntador al primer elemento de la lista
		Meses M; // Almacena la informacion relativa a los meses
		
	public:

   /**
    * @brief Constructor por defecto de la clase DatosPersonales. Apunta l a NULL y carga M.
    */
	ListaEnlazada();

   /**
    * @brief Copia la clase a dat
    * @par ATENCION: SE COPIARA A dat, Y NO AL CONTRARIO, se ha elegido esta impementacion por ser mas sencilla.
    * @pre la clase debe estar correctamente inicializado.
    * @param dat: Tipo ListaEnlazada a donde se copiara la configuracion
    */
	void Clonar(ListaEnlazada &dat);

   /**
    * @brief Devuelve por parametro la configuracion de los Meses
    * @pre La clase debe estar inicializada
    * @param mes: Parametro que se usara para guardar y devolver la configuracion de los meses
    */
	void ObtenerMeses(Meses &mes) const;

   /**
    * @brief Elimina todos los elementos que no sean del mes i
    * @pre La clase debe estar inicializada
    * @param i: mes que permanecera
    */
	void FiltrarPorMes(const int i);

   /**
    * @brief Elimina todos los elementos menores(o =) que i
    * @pre La clase debe estar inicializada
    * @param i: edad que debe superar para permanecer el dato
    */
	void FiltrarPorEdad(const int i);

   /**
    * @brief Inserta un elemento al principio
    * @pre La clase debe estar inicializada.
    * @param dat: DatosPersonales que se insertara en la lista
    */
	void InsertarPrincipio(const DatosPersonales &dat);

   /**
    * @brief Inserta un elemento al final
    * @pre La clase debe estar inicializada.
    * @param dat: DatosPersonales que se insertara en la lista.
    */
	void InsertarFinal(const DatosPersonales &dat);

   /**
    * @brief Inserta un elemento de forma ordenada
    * @pre La clase debe estar inicializada y ordenada.
    * @param dat: DatosPersonales que se insertara en la lista.
    */
	void InsertarOrden(const DatosPersonales &dat);

   /**
    * @brief Halla el numero de elementos
    * @pre La clase debe estar inicializada.
    * @return entero con en numero de elementos de la lista.
    */
	int  Ocupacion() const;

   /**
    * @brief Borra un elemento de la lista
    * @pre La clase debe estar inicializada.
    * @param dat: telefono para buscar el elemento a borrar de la lista.
    * @return true si lo ha borrado correctamente, false en caso contrario.
    */
	bool Borrar( const TCadena1 dat);

   /**
    * @brief Muestra toda la lista en castellano
    * @pre La clase debe estar inicializada.
    */
	void MostrarES() const;

   /**
    * @brief Muestra toda la lista en ingles
    * @pre La clase debe estar inicializada.
    */
	void MostrarEN() const;

   /**
    * @brief Busca un elemento en la lista
    * @pre La clase debe estar inicializada.
    * @param dat: DatosPersonales donde se copiara el elemento encontrado.
    * @param i: telefono para buscar el elemento a borrar de la lista.
    * @return true si lo ha encontrado, false en caso contrario.
    */
	bool Buscar( const TCadena1 i, DatosPersonales &dat) const;

   /**
    * @brief Carga de datos_per.txt
    * @Pre Debe existir nombre y debe estar correctamente formateado.
    * @Param nombre: Nombre del fichero del que se volcara la informacion a la lista
    * @return false si se ha encontrado algun error de apertura
    */
	bool Cargar(const char nombre[20]);

   /**
    * @brief Guarda todos los datos en nombre
    * @Pre Debe poderse sobrescribir nombre.
    * @Param nombre: Nombre del fichero en el que se volcara la informacion de la lista
    * @return false si se ha encontrado algun error de apertura
    */
	bool Guardar(const char nombre[20]) const;

   /**
    * @brief Vacia toda la lista
    */
	void Eliminar();

   /**
    * @brief Destructor de la clase
    */
	~ListaEnlazada();

};


   /**
    * @brief Juego de pruebas para la clase ListaEnlazada
    */
void PruebaListaEnlazada();

#endif
