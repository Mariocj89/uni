/**
* \file persona.h
* \brief Declaracion de la clase abstracta Persona
* \date 12-05-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <queue>
#include <stack>

#include "llave.h"

#ifndef ENUM_POSICION
#define ENUM_POSICION
/*!
   \enum Posicion
   Tipo que representa los puntos cardinales
 */
typedef enum Posicion{NORTE, SUR, OESTE, ESTE};
#endif// ENUM_POSICION

using namespace std;

/**
* \class Persona
* \brief clase abstracta que define los atributos y metodos generales de una persona de la prision
*/
class Persona{
 public:
  Persona(const string &nombre, const char &marca, const int &espera, const int &p, const int &c);
  virtual ~Persona();
  inline string get_nombre() {return nombre_;} //!< Metodo que devuelve el nombre de la persona
  inline char get_marca() {return marca_;}  //!< Metodo que devuelve la marca de la persona
  inline void set_celda(const int &celda) {celda_=celda;} //!< Cambia el atributo celda por el que entra por parametro
  inline int get_turno() {return turno_;}
  Llave* sacar_llave();
  void put_llave(Llave* l);
  bool Actuar();
  virtual string P2String();
  void MostrarRuta();
 protected:
  std::string nombre_; //!< Nombre de la persona (tomaremos -1 como no inicializado)
  char marca_; //!< Marca de la persona, (tomaremos 0 como no inicializado)
  queue <Posicion> *ruta_; //!< Ruta que debe seguir la persona.
  stack <Llave*> llaves_; //!< Llaves que tiene la persona.
  int planta_; //!< Planta en la que se encuentra la persona.
  int celda_; //!< Celda en la que se encuentra la persona.
  int turno_; //!< Atributo que indica el ultimo turno en el que se han actuado (comienza con el primer turno en el que se puede mover)

 private:
  int Destino() const;
  virtual void UsarPuerta() = 0; //!<Metodo virtual puro - Destino: Interactua con una persona
  virtual void Interactuar() = 0; //!<Metodo virtual puro - Destino: Interactua con otra persona
  virtual void TratarLlave() = 0; //!<Metodo virtual puro - Destino: Coge o deja una llave
  virtual void CalcularRuta() = 0; //!<Metodo virtual puto - Destino: Calcular la ruta de la persona
  virtual bool Mover() = 0; //!<Metodo virtual puto - Destino: Mover a la siguiente celda
};


#endif  //PERSONA_H
