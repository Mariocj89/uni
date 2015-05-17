/**
* \file errorpuerta.h
* \brief Declaracion de la clase ErrorPuerta
* \date 2-05-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#ifndef ERRORPUERTA_H
#define ERRORPUERTA_H


using namespace std;
#include <iostream>

/**
 * @class ErrorPuerta
 * @brief Clase para controlar las excepciones producidas al obtener una entrada o salida erronea.
**/
class ErrorPuerta{
 public:
  ErrorPuerta(const int &id);
  string what();
  ~ErrorPuerta();
 private:
  int id_planta_;
};

#endif
