/**
* \file presooptimo.h
* \brief Declaracion de la clase presooptimo
* \date 11-06-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/
#ifndef PRESOOPTIMO_H
#define PRESOOPTIMO_H

#include <queue>
#include "preso.h"

/**
* \class PresoOptimo
* \brief clase que define los atributos y metodos de un PresoOptimo de la prision
*/
class PresoOptimo: public Preso{
 public:
  PresoOptimo(const string &nombre, const char &marca, const int &espera, const Posicion orientacion[4], const int &p, const int &c);
  string P2String();
 private:
  void UsarPuerta();
};

#endif //de PRESOOPTIMO
