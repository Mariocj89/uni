/**
* \file registro.h
* \brief Declaracion de la clase Registro
* \date 2-05-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/
#ifndef REGISTRO_H
#define REGISTRO_H

#include <iostream>
#include <fstream>
using namespace std;

/**
* \class Registro
* \brief Permite mandar datos a un fichero de texto ("registro.log")
*/
class Registro{
 public:
  static Registro* get_instancia();
  ~Registro();
  void Escribir(char* mensaje);
  void Escribir(const string mensaje);
  void Escribir(const int mensaje);
  ostream& Flujo();
  void Destruir();
 private:
  Registro();
  ofstream f_out_; //!< flujo a traves del cual se mandan los datos
  char* nombre_fichero_; //!< Nombre de fichero en el que se guardan los datos (por defecto "registro.log")
  static Registro* instancia_; //!< Instancia de la propia clase (solo habra una en el sistema)
};

#endif
