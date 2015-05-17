/**
* \file errorplanta.h
* \brief Declaracion de la clase ErrorPlanta
* \date 4-06-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#ifndef ERRORPLANTA_H
#define ERRORPLANTA_H
#include <iostream>
using namespace std;

class ErrorPlanta{
 public:
  ErrorPlanta(const int &id);
  ~ErrorPlanta();
  string what(int &id) const;
 private:
  int id_planta_;  //!< Identificador de la planta que lanzo el throw
};

#endif
