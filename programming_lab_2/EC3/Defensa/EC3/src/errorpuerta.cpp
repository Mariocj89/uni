/**
* \file errorpuerta.cpp
* \brief Implementacion de los metodos de la clase ErrorPuerta
* \date 2-05-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#include "errorpuerta.h"
/**
 * Constructor parametrizado de la clase ErrorPuerta
 * @param id identificador de la planta en la que ha saltado la excepcion
 */
ErrorPuerta::ErrorPuerta(const int &id)
{
  id_planta_=id;
}


/**
 * Destructor de la clase ErrorPuerta
 */
ErrorPuerta::~ErrorPuerta()
{
}

/**
 * Metodo que informa de la excepcion ocurrida
 * @return string con la informacion a mostrar
 */
string ErrorPuerta::what()
{
  char aux[100];
  sprintf(aux, "La salida o la entrada estan mal colocadas en la planta: %d",id_planta_);
  string error(aux);
  return error;
}


