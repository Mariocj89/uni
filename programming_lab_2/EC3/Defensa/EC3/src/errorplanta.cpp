/**
* \file errorplanta.cpp
* \brief Implementacion de los metodos de la clase ErrorPlanta
* \date 4-06-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/
#include "errorplanta.h"
#include "prision.h"



/**
 * Constructor de la clase error planta
 * @param id identificador de la planta que lanzo el throw
 */
ErrorPlanta::ErrorPlanta(const int & id)
{
  id_planta_ = id;
}

/**
 * Destructor de la clase planta
 */
ErrorPlanta::~ ErrorPlanta()
{
}

/**
 * Metodo que trata la excepcion
 * @param id identifidador de la ultima planta 
 * @return cadena con el mensaje a mostrar
 */
string ErrorPlanta::what(int & id) const
{
  char aux[100];
  sprintf(aux, "Se ha intentado acceder a la planta: %d la cual no existe, se usara la ultima planta de la prision.",id_planta_);
  string error(aux);
  id = Prision::get_instancia()->get_numero_plantas()-1;
  return error;
}



