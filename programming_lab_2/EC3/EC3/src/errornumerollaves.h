/**
* \file errornumerollaves.h
* \brief Declaracion de la clase ErrorPuerta
* \date 4-05-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#ifndef ERRORNUMEROLLAVES_H
#define ERRORNUMEROLLAVES_H
#include <iostream>
using namespace std;

class ErrorNumeroLlaves{
 public:
  ErrorNumeroLlaves(const int &id);
  string what(int &num) const;
  ~ErrorNumeroLlaves();
 private:
  int id_planta_; //!< Identificador de la planta que lanzo el throw
};

#endif
