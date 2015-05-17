/**
* \file errortamanio.cpp
* \brief Implementacion de los metodos de la clase ErrorTamanio
* \date 4-05-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#include "errortamanio.h"

/**
 * Constructor de la clase ErrorTamanio
 * @param id valor con el que inicializar el id_planta_
 */
ErrorTamanio::ErrorTamanio(const int &id)
{
  id_planta_=id;
}


/**
 * Destructor de la clase ErrorTamanio
 */
ErrorTamanio::~ErrorTamanio()
{
}

/**
 * Metodo para procesar la excepcion, devuelve el ancho y el alto que debera tener la planta ademas de un mensaje
 * @param ancho nuevo ancho de la planta
 * @param alto nuevo alto de la planta
 * @return string con un aviso de la excepcion
 */
string ErrorTamanio::what(int & ancho, int &alto) const
{
  char aux[100];
  sprintf(aux, "El tamaño de la planta con identificador %d es incorrecto\n Se procede a crear una nueva planta:\n\t Tamaño:6x6",id_planta_);
  string error(aux);
  ancho=6;
  alto=6;
  return error;
}


