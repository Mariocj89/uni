/**
* \file errornumerollaves.cpp
* \brief Implementacion de los metodos de la clase ErrorNumeroLlaves
* \date 4-05-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#include "errornumerollaves.h"

/**
 * Constructor parametrizado de la clase ErrorNumeroLlaves
 * @param id identificador de la planta
 */
ErrorNumeroLlaves::ErrorNumeroLlaves(const int &id)
{
  id_planta_=id;
}

/**
 * Destructor de la clase ErrorNumeroLlaves
 */
ErrorNumeroLlaves::~ErrorNumeroLlaves()
{
}


/**
 * Metodo que procesa la excepcion
 * @param  num numero de llaves que se deben generar
 * @return aviso de la excepcion
 */
string ErrorNumeroLlaves::what(int &num) const
{
  char aux[100];
  sprintf(aux, "Hay demasiadas llaves en la planta: %d , solo se insertaran 10.",id_planta_);
  string error(aux);
  num=10;
  return error;
}
