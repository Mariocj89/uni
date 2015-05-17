/**
@file gestor.h                                                                      x
@brief header de la clase gestor                                                    x
@author  Mario Corchero Jiménez                                                     x
@date   15/05/08                                                                    x
@par Descripción:                                                                   x
        Este archivo contiene la especificacion de la clase Gestor, con sus atributos y los headers de todos sus metodos.
@par Utilización:
	Para utilizar esta clase, solo hay que añadir este archivo con <#include "gestor.h"> al principio del fichero y definir
	cualquier variable con esta clase.
@par Plataforma
        Linux.
@par Creado en KDevelop.
*/


#ifndef GESTOR_H
#define GESTOR_H
#include "listaenlazada.h"


typedef char TLinea[50];//tipo de variable que usaremos para leer.
typedef enum TIdioma{Castellano,Ingles};

/**
 * Clase Gestor, gestiona los datos a traves de una lista enlazada y un "selector de idioma". Sus atributos son:
 *    - lista:  listaenlazada que almacena los datospersonales.
 *    - idioma:  TipoEnum que servira para elegir idioma(0-Castellano, 1-Ingles), 0 por defecto
 */
class Gestor {

	ListaEnlazada lista;
	TIdioma Idioma; //0-Castellano, 1-Ingles

   /**
    * @brief Inserta un elemento de forma ordenada en la lista
    * @pre La clase debe estar inicializada
    * @param dat: DatosPersonales que se insertara.
    */
	void InsertarDato(const DatosPersonales &dat);

   /**
    * @brief Borra un elemento
    * @pre La clase debe estar inicializada.
    * @param dat: telefono para buscar el elemento a borrar de la lista.
    * @return true si lo ha borrado correctamente, false en caso contrario.
    */
	bool EliminarDato( const TCadena1 dat);	

   /**
    * @brief Muestra la informacion en castellano
    * @pre La clase debe estar inicializada.
    */
	void MostrarES() const;

   /**
    * @brief Muestra la informacion en ingles
    * @pre La clase debe estar inicializada.
    */
	void MostrarEN() const;


   /**
    * @brief Busca un elemento en la lista
    * @pre La clase debe estar inicializada
    * @param dat: DatosPersonales buscado.
    * @param tfn: Numero con el que buscar.
    * @return true si se encuentra, false en caso contrario
    */
	bool BuscarDato(const TCadena1 tfn,DatosPersonales &dat) const;

    public:

   /**
    * @brief Constructor por defecto de la clase Gestor. Pone Idioma a 0(castellano)
    */
	Gestor();


   /**
    * @brief Muestra toda la informacion.
    * @pre La clase debe estar inicializada.
    */
	void Mostrar() const;


   /**
    * @brief Muestra la informacion de las personas que cumplan años en un mes pedido internamente
    * @pre La clase debe estar inicializada.
    */
	void MostrarMes();

   /**
    * @brief Muestra la informacion de las personas que superen una edad indicada por el usuario
    * @pre La clase debe estar inicializada.
    */
	void MostrarEdad();

   /**
    * @brief Pide la informacion necesaria para insertar un dato
    * @pre La clase debe estar inicializada
    */
	void Insertar();

   /**
    * @brief Solicita informacion para eliminar un elemento
    * @pre La clase debe estar inicializada.
    * @return true si lo ha borrado correctamente, false en caso contrario.
    */
	bool Eliminar( );	



   /**
    * @brief Carga de datos_per.txt
    * @Pre Debe existir datos_per.txt y debe estar correctamente formateado.
    * @return false si se ha encontrado algun error de apertura
    */
	bool Cargar();

   /**
    * @brief Guarda todos los datos en datos_per.txt
    * @Pre Debe poderse sobrescribir datos_per.txt.
    * @return false si se ha encontrado algun error de apertura
    */
	bool Guardar() const;

   /**
    * @brief Pide un numero con el que buscar un dato
    * @Pre La clase debe estar inicializada
    * @return devuelve true si se ha encontrado
    */
	bool Buscar() const;

   /**
    * @brief Alterna entre los 2 idiomas
    * @par en caso de añadir un nuevo idoma habria que modificar este metodo
    */
	void CambiarIdioma();

   /**
    * @brief Devuelve el idioma actual
    * @pre el idoma debe ser "Castellano"(0) o "Ingles"(1)
    * @Param l: TipoIdioma con la informacion respectiva al idoma actual
    */
	void ObtenerIdioma(TIdioma &l);
};




#endif
