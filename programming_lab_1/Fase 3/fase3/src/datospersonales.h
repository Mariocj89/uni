/**
@file datospersonales.h                                                             x
@brief header de la clase DatosPersonales                                           x
@author  Mario Corchero Jiménez                                                     x
@date   15/05/08                                                                    x
@par Descripción:                                                                   x
        Este archivo contiene la especificacion de la clase DatosPersonales, con sus atributos, los headers de todos sus
	metodos y la cabecera de un modulo de prueba.
@par Utilización:
	Para utilizar esta clase, solo hay que añadir este archivo con <#include "datospersonales.h"> al principio del fichero
	y definir cualquier variable con esta clase, y para usar el modulo de prueba basta con llamar a PruebaDatosPersonales()
@par Plataforma
        Linux.
@par Creado en KDevelop.
*/


#ifndef DATOSPERSONALES_H
#define DATOSPERSONALES_H

#include "fecha.h"
#include "meses.h"

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

const int MAXCAD1=10;
const int MAXCAD2=20;

typedef char TCadena1[MAXCAD1];
typedef char TCadena2[MAXCAD2];

/**
 * Clase DatosPersonales, almacena cierta informacion sobre una persona y permite trabajar con esta. Sus atributos son:
 *    - Nombre:  cadena de caracteres que guarda el nombre.
 *    - Apellido1: cadena de caracteres que guarda el primer apellido.
 *    - Apellido2: cadena de caracteres que guarda el segundo apellido.
 *    - Fecha: Tipo fecha que almacena la fecha de cumpleaños.
 *    - Telefono: cadena de caracteres que guarda el telefono.
 */
class DatosPersonales{

	TCadena2 Nombre;
	TCadena2 Apellido1;
	TCadena2 Apellido2;
	fecha FechaNacimiento;
	TCadena1 Telefono;

    public:

		/** Modulos Auxiliares	*/
   /**
    * @brief Modulo privado que devuelve la edad teniendo encuenta la fecha de nacimiento y la fecha actual.
    * @pre FechaNacimiento debe estar inicializado correctamente.
    */
	int CalcularEdad() const;



		/** Constructores	*/

   /**
    * @brief Constructor por defecto de la clase DatosPersonales.
    */
	DatosPersonales();

   /**
    * @brief Constructor por copia de la clase DatosPersonales.
    * @pre dat debe estar previamente inicializado correctamente.
    * @param dat: DatosPersonales, parametro con la que se va a iniciar la clase.
    */
	DatosPersonales(const DatosPersonales &dat);

   /**
    * @brief Constructor parametrizado de la clase DatosPersonales.
    * @pre 
    * @param Name: TCadena2, Nombre.
    * @param Surname1: TCadena2, Apellido1.
    * @param Surname2: TCadena2, Apellido2.
    * @param Date: fecha, FechaNacimiento.
    * @param Number: TCadena1, Telefono.
    */
	DatosPersonales(const TCadena2 Name, const TCadena2 Surname1, const TCadena2 Surname2, const fecha &Date, const TCadena1 Number);

		/** Modulos Poner	*/

   /**
    * @brief Establece nombre de la clase.
    * @pre La clase debe estar inicializada.
    * @param Name: TCadena2 que se copiara a Nombre.
    */
	void PonerNombre(const TCadena2 Name);

   /**
    * @brief Establece Apellido1 de la clase.
    * @pre La clase debe estar inicializada.
    * @param Surname1: TCadena2 que se copiara a Apellido1.
    */
	void PonerApellido1(const TCadena2 Surname1);

   /**
    * @brief Establece Apellido2 de la clase.
    * @pre La clase debe estar inicializada.
    * @param Surname2: TCadena2 que se copiara a Apellido2.
    */
	void PonerApellido2(const TCadena2 Surname2);

   /**
    * @brief Establece FechaNacimiento de la clase.(sobrecargado)
    * @pre La clase debe estar inicializada.
    * @param Date: Tipo fecha que se copiara a FechaNacimiento.
    */
	void PonerFecha(const fecha &Date);

   /**
    * @brief Establece FechaNacimiento de la clase.(sobrecargado)
    * @pre La clase debe estar inicializada.
    * @param d: Entero que sera el dia de FechaNacimiento.
    * @param m: Entero que sera el mes de FechaNacimiento.
    * @param a: Entero que sera el año de FechaNacimiento.
    */
	void PonerFecha(const int &d, const int &m, const int &a);

   /**
    * @brief Establece Telefono de la clase.
    * @pre La clase debe estar inicializada.
    * @param Number: TCadena1 que se copiara a Number.
    */
	void PonerTelefono(const TCadena1 Number);

   /**
    * @brief Establece todos los atributos de la clase a traves de los parametros de entrada.
    * @pre La clase debe estar correctamente inicializada.
    * @param Name: TCadena2, Nombre.
    * @param Surname1: TCadena2, Apellido1.
    * @param Surname2: TCadena2, Apellido2.
    * @param Date: fecha, FechaNacimiento.
    * @param Number: TCadena1, Telefono.
    */
	void PonerTodo(const TCadena2 Name, const TCadena2 Surname1, const TCadena2 Surname2, const fecha &Date, const TCadena1 Number);

		/** Modulos Obtener	*/

   /**
    * @brief Obtiene por parametro de salida el atributo Nombre.
    * @pre La clase debe estar correctamente inicializada.
    * @param Name: TCadena1 donde se copiara el atributo.
    */
	void ObtenerNombre(TCadena2 &Name) const;

   /**
    * @brief Obtiene por parametro de salida el atributo Apellido1.
    * @pre La clase debe estar correctamente inicializada.
    * @param Surname1: TCadena1 donde se copiara el atributo.
    */
	void ObtenerApellido1(TCadena2 &Surname1) const;

   /**
    * @brief Obtiene por parametro de salida el atributo Apellido2.
    * @pre La clase debe estar correctamente inicializada.
    * @param Surname2: TCadena1 donde se copiara el atributo.
    */
	void ObtenerApellido2(TCadena2 &Surname2) const;

   /**
    * @brief Obtiene por parametro de salida el atributo FechaNacimiento.(Sobrecargado)
    * @pre La clase debe estar correctamente inicializada.
    * @param Date: TCadena1 donde se copiara el atributo.
    */
	void ObtenerFecha(fecha &Date) const;

   /**
    * @brief Obtiene por parametro de salida el atributo FechaNacimiento.(Sobrecargado)
    * @pre La clase debe estar correctamente inicializada.
    * @param d: Entero donde se copiara el dia de FechaNacimiento.
    * @param m: Entero donde se copiara el mes de FechaNacimiento.
    * @param a: Entero donde se copiara el año de FechaNacimiento.
    */
	void ObtenerFecha(int &d,int &m,int &a) const;

   /**
    * @brief Obtiene por parametro de salida el atributo Numero.
    * @pre La clase debe estar correctamente inicializada.
    * @param Number: TCadena1 donde se copiara el atributo.
    */
	void ObtenerTelefono(TCadena1 &Number) const;

   /**
    * @brief Obtiene por parametro de salida todos los atributos.
    * @pre La clase debe estar correctamente inicializada.
    * @param Name: TCadena2, Nombre.
    * @param Surname1: TCadena2, Apellido1.
    * @param Surname2: TCadena2, Apellido2.
    * @param Date: fecha, FechaNacimiento.
    * @param Number: TCadena1, Telefono.
    */
	void ObtenerTodo(TCadena2 &Name, TCadena2 &Surname1, TCadena2 &Surname2, fecha &Date, TCadena1 &Number) const;


		/** Resto de Modulos	*/

   /**
    * @brief Copia dat a la clase actual.
    * @pre dat debe estar previamente inicializado correctamente.
    * @param dat: DatosPersonales, parametro que se va a copiar a la clase actual.
    */
	void Clonar(const DatosPersonales &dat);

   /**
    * @brief Compara las dos clases a traves del numero de telefono.
    * @pre dat y la clase actual deben estar previamente inicializadas correctamente.
    * @param dat: DatosPersonales, clase que se va a comparar
    * @return 1 si la clase actual es mayor, -1 si es menor y 0 si es igual.
    */
	int CompararA(const DatosPersonales &dat) const;

   /**
    * @brief Muestra la clase actual en castellano.
    * @pre debe estar correctamenete inicializada
    */
	void MostrarES(const Meses &M) const;

   /**
    * @brief Muestra la clase actual en ingles.
    * @pre debe estar correctamenete inicializada
    */
	void MostrarEN(const Meses &M) const;

   /**
    * @brief Pide la informacion para rellenar la clase en castellano.
    * @pre el usuario debe introducir la informacion de manera correcta.
    */
	void PedirES();

   /**
    * @brief Pide la informacion para rellenar la clase en ingles.
    * @pre el usuario debe introducir la informacion de manera correcta.
    */
	void PedirEN();

   /**
    * @brief Carga la informacion de un dato personal, usando un flujo dado
    * @pre debe estar abierto correctamente el flujo.
    */
	void Cargar(ifstream &entrada);

   /**
    * @brief Guarda la informacion de un dato personal, usando un flujo dado
    * @pre debe estar abierto correctamente el flujo.
    */
	void Guardar(ofstream &salida) const;

   /**
    * @brief Destructor de la clase DatosPersonales
    */
	~DatosPersonales();

};


   /**
    * @brief Juego de pruebas para la clase DatosPersonales
    */
  void PruebaDatosPersonales();

#endif
