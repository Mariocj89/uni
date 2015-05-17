/**
* \file errortamanio.h
* \brief Declaracion de la clase ErrorTamanio
* \date 4-05-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#ifndef ERRORTAMANIO_H
#define ERRORTAMANIO_H
#include <iostream>
using namespace std;

class ErrorTamanio{
 public:
  ErrorTamanio(const int &id);
  ~ErrorTamanio();
  string what(int &ancho, int &alto) const;
 private:
  int id_planta_;  //!< Identificador de la planta que lanzo el throw
};

#endif
