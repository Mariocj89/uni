/**
* \file presooptimo.cpp
* \brief Implementación de los metodos de la clase PresoOptimo
* \author
*   \b Profesores LPII \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#include "presooptimo.h"
#include "prision.h"

/**
 * Interactua con la puerta hasta que la habre
 */
void PresoOptimo::UsarPuerta()
{
  if(celda_ == Prision::get_instancia()->get_salida_planta(planta_)) {
    int id=1;
    llaves_.push(new Llave(id));
    while(!ProbarLlaves()){
      id+=2;
      llaves_.push(new Llave(id));
    }
  }
}

/**
 * Constructor parametrizado de la clase PresoOptimo
 * @param nombre nombre del preso
 * @param marca marca del preso
 * @param espera turnos que el preso debe esperar antes de actuar
 * @param orientacion[] orientacion para calcular la ruta del preso
 * @param p planta en la que inicia el preso
 * @param c celda en la que inicia el preso
 */
PresoOptimo::PresoOptimo(const string & nombre, const char & marca, const int & espera, const Posicion orientacion[], const int & p, const int & c):Preso(nombre,marca,espera,orientacion,p,c)
{
}

string PresoOptimo::P2String()
{
  string cadena = "(preso:";
  cadena+= Persona::P2String();
  return cadena;
}



