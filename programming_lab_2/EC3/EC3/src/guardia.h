/**
* \file guardia.h
* \brief Declaracion de la clase guardia
* \date 14-05-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#include <iterator>
#include "persona.h"
#ifndef GUARDIA_H
#define GUARDIA_H

/**
* \class guardia
* \brief clase que define los atributos y metodos de un guardia de la prision
*/
class Guardia: public Persona{
 public:
  string P2String();
  Guardia(const string &nombre, const char &marca, const int &espera, const int &p, const int &c);
  ~Guardia();
 private:
  void UsarPuerta();
  void Interactuar();
  void TratarLlave();
  void CalcularRuta();
  bool Mover();
  int DestinoRuta() const;


};

#endif //GUARDIA_H

