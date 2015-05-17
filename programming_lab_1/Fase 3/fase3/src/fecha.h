/**
@file fecha.h                                                                       x
@brief header de la clase fecha                                                     x
@author  Mario Corchero Jiménez                                                     x
@date   15/05/08                                                                    x
@par Descripción:                                                                   x
        Este archivo contiene la especificacion de la clase fecha, con sus atributos, los headers de todos sus metodos
	y la cabecera de un modulo de prueba.
@par Utilización:
	Para utilizar esta clase, solo hay que añadir este archivo con <#include "fecha.h"> al principio del fichero y definir
	cualquier variable con esta clase, y para usar el modulo de prueba basta con llamar a Prueba_Fecha()
@par Plataforma
        Linux.
@par Creado en KDevelop.
*/


#ifndef FECHA_H
#define FECHA_H


/**
 * Clase Fecha, permite tratar fechas reales. Sus atributos son:
 *    - dia:  Vector de elementos almacenados
 *    - mes: Numero de elementos actual
 *    - anio: Apuntador al elemento de interes
 */
class fecha
{
	int dia;
	int mes;
	int anio;
	// métodos privados de la clase
   /**
    * @brief comprueba los dias que tiene un mes, tiene en cuenta si el año es bisiesto.
    * @pre 
    * @param m: mes que se quiere comprobar.
    * @param a: año del mes que se quiere comprobar.
    * @return int: numero de dias que tiene el mes.
    */
	int dias_por_mes (int m, int a);
	/*
           Un año es bisiesto si es divisible por 4, excepto los principios de siglo(aquellos divisibles por 100)
	   que para ser bisiestos tambien deben ser divisibles por 400
         */
   /**
    * @brief comprueba si un año es bisiesto.
    * @pre 
    * @param a: año a comprobar.
    * @return int: numero de dias que tiene el mes.
    */
	bool bisiesto (int a);

   /**
    * @brief comprueba si una fecha es correcta.
    * @pre 
    * @param d: dia a comprovar.
    * @param m: mes a comprovar.
    * @param a: año a comprovar.
    * @return true si es correcta, false en caso contrario.
    */
	bool fecha_correcta(int d, int m, int a);

public:
   /**
    * @brief Constructor por defecto de la clase Fecha. Establece todos los elementos a 0 
    * @pre 
    * @param 
    * @return 
    */
	fecha();

   /**
    * @brief Constructor parametrizado de la clase Fecha. Establece el mes y el dia por parametro y pone el año a 2008. 
    * @pre 
    * @param d: el dia que se va a insertar en la fecha.
    * @param m: el mes que se va a insertar en la fecha.
    * @return 
    */
	fecha (int d,int m);

   /**
    * @brief Constructor parametrizado de la clase Fecha. Establece todos los elementos por parametro. 
    * @pre 
    * @param d: el dia que se va a insertar en la fecha.
    * @param m: el mes que se va a insertar en la fecha.
    * @param a: el año que se va a insertar en la fecha.
    * @return 
    */
	fecha(int d,int m,int a);

   /**
    * @brief Constructor por copia de la clase Fecha. Establece todos los elementos obteniendolos de F. 
    * @pre 
    * @param F: Fecha origen que se va a usar para establecer la fecha tratada.
    * @return 
    */
	fecha (const fecha&F);

   /**
    * @brief Copia la clase Fecha. Establece todos los elementos obteniendolos de F. 
    * @pre F debe estar inicializada.
    * @param F: Fecha origen que se va a usar para establecer la fecha tratada.
    * @return 
    */
	void Clonar (const fecha&F);

   /**
    * @brief Incrementa la fecha en un dia.
    * @pre La fecha debe estar inicializada.
    * @param
    * @return 
    */
	void incrementar_fecha();

   /**
    * @brief Decrementa la fecha en un dia.
    * @pre La fecha debe estar inicializada.
    * @param
    * @return 
    */
	void decrementar_fecha();

   /**
    * @brief Asigna una fecha. Establece todos los elementos por parametros. 
    * @pre 
    * @param d: el dia que se va a insertar en la fecha.
    * @param m: el mes que se va a insertar en la fecha.
    * @param a: el año que se va a insertar en la fecha.
    * @return 
    */
	void asignar_fecha(int d, int m,int a);

   /**
    * @brief Devuelve el dia.
    * @pre La fecha debe estar inicializada.
    * @param
    * @return un entero que indica el dia de la fecha.
    */
	int obtener_dia() const;

   /**
    * @brief Devuelve el mes.
    * @pre La fecha debe estar inicializada.
    * @param
    * @return un entero que indica el mes de la fecha.
    */
	int obtener_mes() const;

   /**
    * @brief Devuelve el año.
    * @pre La fecha debe estar inicializada.
    * @param
    * @return un entero que indica el año de la fecha.
    */	
	int obtener_anio() const;


   /**
    * @brief Muestra la fecha en pantalla.
    * @pre La fecha debe estar inicializada.
    * @param
    * @return
    */	
	void Mostrar_Fecha() const;
};


   /**
    * @brief Juego de pruebas para la clase fecha
    */
  void Prueba_Fecha();


#endif

