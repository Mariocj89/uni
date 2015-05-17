/**
* \file preso.h
* \brief Declaracion de la clase preso
* \date 14-05-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/
#ifndef PRESO_H
#define PRESO_H

#include <queue>
#include "persona.h"


/**
* \class Preso
* \brief clase que define los atributos y metodos de un preso de la prision
*/
class Preso: public Persona{
 public:
  Preso(const string &nombre, const char &marca, const int &espera, const Posicion orientacion[4], const int &p, const int &c);
  string P2String();
  ~Preso();
 private:
  queue<Posicion> *orientacion_; //!< Orden de eleccion a la hora de elegir la ruta de escape
  bool Mover();
  void UsarPuerta();
  void Interactuar();
  void TratarLlave();
  void CalcularRuta();
  bool CalcularRutaRecursivo(const int & posicion,stack<Posicion>* pilaux,  bool visitados[300]);
  bool ProbarLlaves();
};

#endif //PRESO_H
